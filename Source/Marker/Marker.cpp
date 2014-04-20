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

#include "Dataset.hpp"
#include "Geometry.hpp"
#include "Marker.hpp"

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
#ifdef IMSHOW
		cv::destroyWindow(windowName.c_str());
#endif

		ImageData data(IO::getFilenameFromPath(filenames[i]));
		data.points_ = points;
		data.marks_ = marks;

		dataset.dataset_.push_back(data);
		dataset.serialize(mv::IO::appendFilenameToFolderPath(startingResultsFolder_, kDatasetFilenameExtension_).c_str());
	}

	//dataset.display(startingResultsFolder_);
//	dataset.serialize(mv::IO::appendFilenameToFolderPath(startingResultsFolder_, DATASET_FILENAME_EXTENSION).c_str());
}

void Marker::updateDataset() {
	Dataset ds;
	ds.deserialize(mv::IO::appendFilenameToFolderPath(startingResultsFolder_, kDatasetFilenameExtension_));

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
#ifdef IMSHOW
			cv::destroyWindow(windowName.c_str());
#endif

			ImageData data(filename);
			data.points_ = points;
			data.marks_ = marks;

			ds.dataset_.push_back(data);
			ds.serialize(mv::IO::appendFilenameToFolderPath(startingResultsFolder_, kDatasetFilenameExtension_).c_str());
		}
	}
}

void Marker::filterDataset() {
	Dataset ds;
	ds.deserialize(mv::IO::appendFilenameToFolderPath(startingResultsFolder_, kDatasetFilenameExtension_));
	// filter extra points
	for(std::vector<ImageData>::iterator it=ds.dataset_.begin(); it!=ds.dataset_.end(); ++it) {
		if(it->points_.size()>4) {
			std::vector<cv::Point> newPoints;
			newPoints.reserve(4);
			newPoints.push_back(it->points_[0]);
			for(uint32_t i=1; i<it->points_.size(); ++i) {
				// only consecutive points are filtered
				if(mv::Geometry::distance(it->points_[i-1], it->points_[i])>5) {
					newPoints.push_back(it->points_[i]);
				}
			}
			it->points_.clear();
			it->points_ = newPoints;
		}
	}
	ds.serialize(mv::IO::appendFilenameToFolderPath(startingResultsFolder_, kDatasetFilenameExtension_));
}

void Marker::showDataset() {
	Dataset ds;
	ds.deserialize(mv::IO::appendFilenameToFolderPath(startingResultsFolder_, kDatasetFilenameExtension_));
	ds.display(startingResultsFolder_);
}

} /* namespace mv */
