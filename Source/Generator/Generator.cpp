/**
 * \file
 *
 * Generator.cpp
 *
 *  Created on: Apr 4, 2012
 *      Author: cerovec
 */

/**
 * Copyright (c)2012 Racuni.hr d.o.o. All rights reserved.
 *
 * ANY UNAUTHORIZED USE OR SALE, DUPLICATION, OR DISTRIBUTION
 * OF THIS PROGRAM OR ANY OF ITS PARTS, IN SOURCE OR BINARY FORMS,
 * WITH OR WITHOUT MODIFICATION, WITH THE PURPOSE OF ACQUIRING
 * UNLAWFUL MATERIAL OR ANY OTHER BENEFIT IS PROHIBITED!
 * THIS PROGRAM IS PROTECTED BY COPYRIGHT LAWS AND YOU MAY NOT
 * REVERSE ENGINEER, DECOMPILE, OR DISASSEMBLE IT.
 */

#include "Generator.h"
#include <time.h>

namespace mv {

cv::RNG Generator::RNG = cv::RNG(time(0));

std::string Generator::createFilename(const std::string& originalFilename,
		const unsigned int index) const {
	// find extension
	size_t startExtension = originalFilename.find_last_of(".");
	std::string extension;
	if (startExtension == std::string::npos) {
		startExtension = originalFilename.length() - 1;
		extension = "JPG";
	} else {
		extension = originalFilename.substr(startExtension);
	}

	std::string filename = originalFilename.substr(0, startExtension);

	std::ostringstream oss;

	oss << filename << "_" << getGeneratorName() << index << extension;

	return oss.str();
}

void Generator::generateSamplesInDataset(const Dataset& original, Dataset& generated) const {
	printf("Generating %s dataset..\n", getGeneratorName().c_str());

	for (unsigned int i = 0; i < original.dataset_.size(); i++) {
		cv::Mat image;
		ImageData data = original.dataset_[i];

		for (unsigned int j = 0; j < numSamples_; j++) {
			ImageData generatedData;

			std::string generatedFilename = createFilename(data.filename_, j);
			generateSample(data, generatedData, generatedFilename);

			generated.dataset_.push_back(generatedData);
		}
	}
}

void Generator::generateDataset() const {
	Dataset dataset;
	loadDataset(dataset);

	Dataset generatedDataset;
	generateSamplesInDataset(dataset, generatedDataset);
	saveDataset(generatedDataset);

	if (next_ != NULL) {
		next_->generateDataset();
	}
}

} /* namespace mv */
