/**
 * \file
 *
 * PerspectiveGenerator.cpp
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

#include "PerspectiveGenerator.h"
#include "Utils/IO.h"
#include "Utils/Geometry.h"

namespace mv {

std::string PerspectiveGenerator::getGeneratorName() const {
	return "persp";
}

void PerspectiveGenerator::generateSample(const ImageData& originalSample,
		ImageData& generatedSample, std::string& generatedFilename) const {

	printf("Generating image %s.\n", generatedFilename.c_str());

	cv::Mat originalImage;
	IO::loadImageFromFile(originalImage,
			IO::appendFilenameToFolderPath(startingResultsFolder_, originalSample.filename_).c_str());

	double variance;
	variance = fabs(RNG.gaussian(perspectiveVariance_));

	cv::Mat generatedImage;

	std::vector<cv::Point> newPoints;
	cv::Mat transformMatrix(3, 3, CV_32FC1);

	do {
		newPoints.clear();

		transformMatrix.at<float>(0,0) = RNG.uniform( 0.8f, 1.2f);
		transformMatrix.at<float>(0,1) = RNG.uniform(-0.1f, 0.1f);
		transformMatrix.at<float>(0,2) = RNG.uniform(-0.1f, 0.1f) * originalImage.cols;
		transformMatrix.at<float>(1,0) = RNG.uniform(-0.1f, 0.1f);
		transformMatrix.at<float>(1,1) = RNG.uniform( 0.8f, 1.2f);
		transformMatrix.at<float>(1,2) = RNG.uniform(-0.1f, 0.1f) * originalImage.rows;
		transformMatrix.at<float>(2,0) = RNG.uniform( -1e-4f, 1e-4f);
		transformMatrix.at<float>(2,1) = RNG.uniform( -1e-4f, 1e-4f);
		transformMatrix.at<float>(2,2) = RNG.uniform( 0.8f, 1.2f);

		mv::perspectiveTranform(originalSample.points_, newPoints, transformMatrix);
	} while (!mv::arePointsInside(newPoints, cv::Size(originalImage.cols, originalImage.rows)));

	warpPerspective(originalImage, generatedImage, transformMatrix, originalImage.size());

	generatedSample.filename_ = generatedFilename;
	generatedSample.points_ = newPoints;
	generatedSample.marks_ = originalSample.marks_;

	IO::saveImageToFile(generatedImage,
			IO::appendFilenameToFolderPath(generatedResultsFolder_, generatedFilename).c_str());
}

} /* namespace mv */
