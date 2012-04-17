/**
 * \file
 *
 * BlurGenerator.cpp
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

#include "BlurGenerator.h"
#include "Utils/IO.h"
#include <stdio.h>

namespace mv {

std::string BlurGenerator::getGeneratorName() const {
	return "blur";
}

void BlurGenerator::generateSample(const ImageData& originalSample,
		ImageData& generatedSample, std::string& generatedFilename) const {

	printf("Generating image %s. ", generatedFilename.c_str());

	cv::Mat originalImage;
	IO::loadImageFromFile(originalImage,
			IO::appendFilenameToFolderPath(startingResultsFolder_, originalSample.filename_).c_str());

	generatedSample.filename_ = generatedFilename;
	generatedSample.points_ = originalSample.points_;
	generatedSample.marks_ = originalSample.marks_;

	cv::Mat generatedImage;

	int kernel = RNG.uniform(0, blurRadius_ / 2 + 1);
	kernel *= 2;
	kernel += 1;
	printf("Blur radius  is: %d\n", kernel);
	cv::GaussianBlur(originalImage, generatedImage, cv::Size(kernel, kernel), 0, 0, cv::BORDER_DEFAULT);

	IO::saveImageToFile(generatedImage,
			IO::appendFilenameToFolderPath(generatedResultsFolder_, generatedFilename).c_str());
}

} /* namespace mv */
