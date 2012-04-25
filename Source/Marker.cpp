/**
 * \file
 *
 * Marker.cpp
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

#include "Marker.h"
#include <stdio.h>
#include <dirent.h>
#include "ImageIO.h"
#include <opencv2/opencv.hpp>

namespace mv {

void Marker::findImageFilenames(std::string folderName, std::vector<std::string>& imageFilenames) {
	DIR *d;
	struct dirent* dirent;

	d = opendir(folderName.c_str());
	if (!d) {
		fprintf(stderr, "Invalid directory %s", folderName.c_str());
	} else {
		while ((dirent = readdir(d)) != NULL) {
			std::string filename(dirent->d_name);
			if (isSupportedFileType(filename)) {
				imageFilenames.push_back(folderName + "/" + filename);
			}
		}

		closedir(d);
	}
}

void Marker::markDataset() {

	std::vector<std::string> imageFilenames;

	findImageFilenames(folderName_, imageFilenames);

	for (unsigned int i = 0; i < imageFilenames.size(); i++) {
		printf("%s\n", imageFilenames[i].c_str());
		cv::Mat image;
		const char* title = "Image";
		std::vector<cv::Point> points;
		std::vector<std::string> marks;

		mv::ImageIO::loadImageFromFile(image, imageFilenames[i].c_str());
		mv::ImageIO::displayImage(image, title);

		mv::ImageIO::handleUserInput(image, title, points, marks);

		cv::destroyWindow(title);
	}
}

} /* namespace mv */
