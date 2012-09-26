/*
 * GpuGenerator.cpp
 *
 *  Created on: Sep 24, 2012
 *      Author: dodo
 */

#include "GpuGenerator.hpp"
#include "Utils/IO.h"
#include "RenderingContext/IRenderingContext.hpp"
#include "RenderingSurface/IRenderingSurface.hpp"
#include "MatrixModifier.hpp"

namespace mv {

GpuGenerator::GpuGenerator(std::string folder, ErrorStatus &status) :
		context_(gpumv::IRenderingContext::getContext(640, 480)),
		folder_(folder),
		frameProvider_(context_),
		genFilter_(context_, status) {
	if(status==ERROR_STATUS_SUCCESS) {
		LOGD("Loading dataset...");
		ds_.deserialize(IO::appendFilenameToFolderPath(folder_,"dataset.txt"));
	} else {
		LOGE("There were errors in member initialization");
	}
}

GpuGenerator::~GpuGenerator() {
	gpumv::IRenderingContext::terminateContext();
}

void GpuGenerator::generateVariations() {
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

void GpuGenerator::generateImages(std::string outFolder) {
	int imIndex = 1;
	for(std::vector<mv::ImageData>::iterator it=ds_.dataset_.begin(); it!=ds_.dataset_.end(); ++it) {
		LOGD("Image %d/%u: %s", imIndex++, ds_.dataset_.size(), it->filename_.c_str());
		cv::Mat inputImage = cv::imread(IO::appendFilenameToFolderPath(folder_, it->filename_));
		frameProvider_.setNewFrame(inputImage);
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
		genFilter_.setInputTexture(frameProvider_.getFrameTexture());
		// set background texture
		genFilter_.setBackgroundTexture(frameProvider_.getFrameTexture());
		genFilter_.setTexCoordinates(points[0], points[1], points[3], points[2]); // positions of invoice corner points
		generateVariations();
	}
}

} /* namespace mv */
