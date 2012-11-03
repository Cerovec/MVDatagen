/*
 * GpuGenerator.hpp
 *
 *  Created on: Sep 24, 2012
 *      Author: dodo
 */

#ifndef GPUGENERATOR_HPP_
#define GPUGENERATOR_HPP_

#include "Dataset.h"
#include "CommonHeaders.h"
#include "CameraFrameProvider.hpp"
#include "GpuImageFilters/ImageGeneratorFilter.hpp"
#include <string>

namespace gpumv {
	class RenderingContext;
}

namespace mv {

class GpuGenerator {
public:
	GpuGenerator(std::string folder, ErrorStatus &status);
	virtual ~GpuGenerator();

	void generateImages(std::string outFolder);

private:
	gpumv::RenderingContext *context_;
	std::string folder_;
	mv::Dataset ds_;
	gpumv::CameraFrameProvider frameProvider_;
	gpumv::ImageGeneratorFilter genFilter_;

	void generateVariations();
};

} /* namespace mv */
#endif /* GPUGENERATOR_HPP_ */
