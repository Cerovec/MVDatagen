/**
 * \file
 *
 * FlipGenerator.cpp
 *
 *  Created on: Apr 18, 2012
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

#include "FlipGenerator.h"
#include <opencv2/opencv.hpp>

namespace mv {

std::string FlipGenerator::getGeneratorName() const {
	return "flip";
}

void FlipGenerator::generateSample(const ImageData& originalSample,
		ImageData& generatedSample, std::string& generatedFilename) const {

	printf("Generating flipped image %s.\n", generatedFilename.c_str());

	cv::Mat originalImage;
	IO::loadImageFromFile(originalImage,
			IO::appendFilenameToFolderPath(startingResultsFolder_, originalSample.filename_).c_str());

	generatedSample.filename_ = generatedFilename;
	generatedSample.marks_ = originalSample.marks_;

	cv::Mat generatedImage;
	cv::flip(originalImage, generatedImage, -1);

	std::vector<cv::Point> newPoints;
	for (unsigned int i = 0; i < originalSample.points_.size(); i++) {
		cv::Point point = originalSample.points_[i];
		newPoints.push_back(cv::Point(originalImage.cols - 1 - point.x, originalImage.rows - 1 - point.y));
	}

	generatedSample.points_ = newPoints;

	IO::saveImageToFile(generatedImage,
			IO::appendFilenameToFolderPath(generatedResultsFolder_, generatedFilename).c_str());
}

} /* namespace mv */
