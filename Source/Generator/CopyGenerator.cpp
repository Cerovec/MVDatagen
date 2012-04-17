/**
 * \file
 *
 * CopyGenerator.cpp
 *
 *  Created on: Apr 17, 2012
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

#include "CopyGenerator.h"
#include "Utils/IO.h"

namespace mv {

std::string CopyGenerator::getGeneratorName() const {
	return "cp";
}

void CopyGenerator::generateSample(const ImageData& originalSample,
		ImageData& generatedSample, std::string& generatedFilename) const {

	printf("Generating image %s. ", generatedFilename.c_str());

	cv::Mat originalImage;
	IO::loadImageFromFile(originalImage,
			IO::appendFilenameToFolderPath(startingResultsFolder_, originalSample.filename_).c_str());

	generatedSample.filename_ = generatedFilename;
	generatedSample.points_ = originalSample.points_;
	generatedSample.marks_ = originalSample.marks_;

	IO::saveImageToFile(originalImage,
			IO::appendFilenameToFolderPath(generatedResultsFolder_, generatedFilename).c_str());
}

} /* namespace mv */
