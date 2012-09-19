/**
 * \file
 *
 * Marker.cpp
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

#include "Marker.h"
#include "Dataset.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <set>

namespace mv {

const std::string Marker::DATASET_FILENAME_EXTENSION = "/dataset.txt";

void Marker::markDataset() {
	std::vector<std::string> filenames;
	IO::findImageFilenames(startingResultsFolder_, filenames);

	Dataset dataset;

	for (unsigned int i = 0; i < filenames.size(); i++) {
		cv::Mat image;
		IO::loadImageFromFile(image, filenames[i].c_str());
		std::cout << "Processing image " << i+1 << "/" << filenames.size() << " (" << filenames[i] << ")" << std::endl;


		std::string windowName = "Marker";
		std::vector<cv::Point> points;
		std::vector<std::string> marks;

		IO::displayImage(image, windowName.c_str());
		IO::handleUserInput(image, windowName.c_str(), points, marks);
		cv::destroyWindow(windowName.c_str());

		ImageData data(IO::getFilenameFromPath(filenames[i]));
		data.points_ = points;
		data.marks_ = marks;

		dataset.dataset_.push_back(data);
		dataset.serialize(mv::IO::appendFilenameToFolderPath(startingResultsFolder_, DATASET_FILENAME_EXTENSION).c_str());
	}

	//dataset.display(startingResultsFolder_);
//	dataset.serialize(mv::IO::appendFilenameToFolderPath(startingResultsFolder_, DATASET_FILENAME_EXTENSION).c_str());
}

void Marker::updateDataset() {
	Dataset ds;
	ds.deserialize(mv::IO::appendFilenameToFolderPath(startingResultsFolder_, DATASET_FILENAME_EXTENSION));

	// build set of existing images for faster searching from loop (log complexity instead of linear)
	std::set<std::string> existingFiles;
	for(std::vector<ImageData>::iterator imData = ds.dataset_.begin(); imData!=ds.dataset_.end(); ++imData) {
		existingFiles.insert(imData->filename_);
	}

	// get list of images in given folder
	std::vector<std::string> filenames;
	IO::findImageFilenames(startingResultsFolder_, filenames);

	// perform the marking of just new images with serializing dataset in each step (for security)

	for (unsigned int i = 0; i < filenames.size(); i++) {
		cv::Mat image;
		IO::loadImageFromFile(image, filenames[i].c_str());
		std::string filename = IO::getFilenameFromPath(filenames[i]);
		if(existingFiles.count(filename)==0) { // image does not exist in dataset
			std::cout << "Processing image " << i+1 << "/" << filenames.size() << " (" << filenames[i] << ")" << std::endl;


			std::string windowName = "Marker";
			std::vector<cv::Point> points;
			std::vector<std::string> marks;

			IO::displayImage(image, windowName.c_str());
			IO::handleUserInput(image, windowName.c_str(), points, marks);
			cv::destroyWindow(windowName.c_str());

			ImageData data(filename);
			data.points_ = points;
			data.marks_ = marks;

			ds.dataset_.push_back(data);
			ds.serialize(mv::IO::appendFilenameToFolderPath(startingResultsFolder_, DATASET_FILENAME_EXTENSION).c_str());
		}
	}
}

void Marker::showDataset() {
	Dataset ds;
	ds.deserialize(mv::IO::appendFilenameToFolderPath(startingResultsFolder_, DATASET_FILENAME_EXTENSION));
	ds.display(startingResultsFolder_);
}

} /* namespace mv */
