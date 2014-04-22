/*
 * GpuGenerator.hpp
 *
 *  Created on: Sep 24, 2012
 *      Author: dodo
 */

#pragma once

#include "CommonHeaders.h"
#include "Dataset.hpp"

namespace gpumv {
	class RenderingContext;
}

namespace mv {

struct GpuGeneratorImpl;
class GpuGenerator {
public:
	GpuGenerator(const std::string& folder, ErrorStatus &status);
	virtual ~GpuGenerator();

	void generateImages(std::string outFolder);

private:
	GpuGeneratorImpl* impl_;
};

} /* namespace mv */
