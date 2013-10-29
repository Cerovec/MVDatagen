/*
 * GpuGenerator.cpp
 *
 *  Created on: Sep 24, 2012
 *      Author: dodo
 */

#include "GpuGenerator.hpp"
#include "Utils/IO.hpp"
#include "MatrixModifier.hpp"

#ifdef USE_GPU_DEWARP
#include "RenderingContext/RenderingContext.hpp"
#include "RenderingSurface/RenderingSurface.hpp"
#include "CameraFrameProvider.hpp"
#include "GpuImageFilters/ImageGeneratorFilter.hpp"
#endif

namespace mv {

#ifdef USE_GPU_DEWARP
struct GpuGeneratorImpl {
    gpumv::RenderingContext *context_;
    std::string folder_;
    mv::Dataset ds_;
    gpumv::CameraFrameProvider frameProvider_;
    gpumv::ImageGeneratorFilter genFilter_;

    void generateVariations();

    GpuGeneratorImpl(const std::string& folder, ErrorStatus& status) :
        context_(gpumv::RenderingContext::getContext(640, 480)),
            folder_(folder),
            frameProvider_(context_),
            genFilter_(context_, status) {}
};
#endif

GpuGenerator::GpuGenerator(const std::string& folder, ErrorStatus &status) {
#ifdef USE_GPU_DEWARP
    impl_ = new GpuGeneratorImpl(folder, status);
    if(status==ERROR_STATUS_SUCCESS) {
        LOGD("Loading dataset...");
        impl_->ds_.deserialize(IO::appendFilenameToFolderPath(impl_->folder_,"dataset.txt"));
    } else {
        LOGE("There were errors in member initialization");
    }
#else
    status = ERROR_STATUS_NOT_SUPPORTED;
    impl_ = NULL;
#endif

}

GpuGenerator::~GpuGenerator() {
#ifdef USE_GPU_DEWARP
    delete impl_;
	gpumv::RenderingContext::terminateContext();
#endif
}

#ifdef USE_GPU_DEWARP
inline void GpuGeneratorImpl::generateVariations() {
	// perform this in loop
	for(float bFact = 0.7; bFact<1.4; bFact+=0.1) { // for loop modifies blue balance factor
		for(float zDist = 0.f; zDist<2.5f; zDist+=0.5f) { // for loop modifies rectangle's z position
			for(float yRot = 0.f; yRot<1.0; yRot+=0.2f) { // for loop modifies rotation around y axis
				float awbFactors[3] = {bFact, 1.f, 1.f}; // White balance modification factors in BGR order
				cv::Mat transform = gpumv::MatrixModifier().rotateAroundX(0.3*yRot).rotateAroundZ(0.3*zDist).
						rotateAroundY(yRot).translate(0,0,zDist).getTransformMatrix();
				// perform image modification
				genFilter_.setAwbFactors(awbFactors);
				genFilter_.setTransformMatrix(transform);
				// render the image
				ErrorStatus status;
				genFilter_.render(status);
				if(status!=ERROR_STATUS_SUCCESS) {
					LOGE("Error in rendering!");
					continue;
				}
				// download rendered frame from GPU
				cv::Mat output;
				context_->getRenderingSurface()->readPixels(output, status);

				// either save it to file or show it
				cv::imshow("rendered", output);
				cv::waitKey(0);
			}
		}
	}
}
#endif

void GpuGenerator::generateImages(std::string outFolder) {
#ifdef USE_GPU_DEWARP
	for(std::vector<mv::ImageData>::iterator it=impl_->ds_.dataset_.begin(); it!=impl_->ds_.dataset_.end(); ++it) {
//		LOGD("Image %d/%u: %s", imIndex++, ds_.dataset_.size(), it->filename_.c_str());
		cv::Mat inputImage = cv::imread(IO::appendFilenameToFolderPath(impl_->folder_, it->filename_));
		impl_->frameProvider_.setNewFrame(inputImage);
		// adjust marker positions coordinates to texture coordinate system
		cv::Size imSize(inputImage.cols, inputImage.rows);
		gpumv::Point points[4];
		if(it->points_.size()!=4)
			continue;
		for(int i=0; i<4; ++i) {
			points[i].x = (float)it->points_[i].x/(float)imSize.width;
			points[i].y = (float)it->points_[i].y/(float)imSize.height;
		}
		// render frame
		impl_->genFilter_.setInputTexture(impl_->frameProvider_.getFrameTexture());
		// set background texture
		impl_->genFilter_.setBackgroundTexture(impl_->frameProvider_.getFrameTexture());
		impl_->genFilter_.setTexCoordinates(points[0], points[1], points[3], points[2]); // positions of invoice corner points
		impl_->generateVariations();
	}
#endif
}

} /* namespace mv */
