/*
 * GpuGenerator.hpp
 *
 *  Created on: Sep 24, 2012
 *      Author: dodo
 */

#ifndef GPUGENERATOR_HPP_
#define GPUGENERATOR_HPP_

#include "Dataset.hpp"
#include "CommonHeaders.h"
#include <string>

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
#endif /* GPUGENERATOR_HPP_ */
