/*
 * OCRLineMarker.cpp
 *
 *  Created on: Jun 11, 2013
 *      Author: boris
 */

#include "OCRLineMarker.hpp"
#include "Dataset.hpp"
#include "Geometry.hpp"
#include "Marker.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <set>

namespace mv {

OCRLineMarker::OCRLineMarker(std::string startingResultsFolder,
							 int imagePercentage) :
		Marker(startingResultsFolder, "/ocrDataset.txt"){
	imagePercentage_ = std::min(std::max(imagePercentage/(float)100, 0.1f), 0.9f);
}

OCRLineMarker::~OCRLineMarker() {
	// nothing to do
}

void OCRLineMarker::getOcrLinePoints(const cv::Point& seed,
									 const cv::Size& imageSize,
									 std::vector<cv::Point>& points){
    int height = (int)(imageSize.height*imagePercentage_);
	int up = seed.y - (height >> 1);
	int lo = seed.y + (height >> 1);
	if (up < 0){
		up -= up;
		lo -= up;
	}
	if (lo >= imageSize.height){
		int diff = lo - imageSize.height + 1;
		up -= diff;
		lo -= diff;
	}
	points.push_back(cv::Point(0, up));
	points.push_back(cv::Point(imageSize.width-1, up));
	points.push_back(cv::Point(imageSize.width-1, lo));
	points.push_back(cv::Point(0, lo));
}

void OCRLineMarker::markDataset() {
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

		for (int j = 0; j < (int)points.size(); ++ j){
			ImageData data(IO::getFilenameFromPath(filenames[i]));
			getOcrLinePoints(points[j], cv::Size(image.cols, image.rows), data.points_);
			data.marks_ = marks;
			dataset.dataset_.push_back(data);
		}

		dataset.serialize(mv::IO::appendFilenameToFolderPath(startingResultsFolder_, kDatasetFilenameExtension_).c_str());
	}

	//dataset.display(startingResultsFolder_);
//	dataset.serialize(mv::IO::appendFilenameToFolderPath(startingResultsFolder_, DATASET_FILENAME_EXTENSION).c_str());
}

void OCRLineMarker::updateDataset() {
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
			cv::destroyWindow(windowName.c_str());

			for (int j = 0; j < (int)points.size(); ++ j){
				ImageData data(filename);
				getOcrLinePoints(points[j], cv::Size(image.cols, image.rows), data.points_);
				data.marks_ = marks;
				ds.dataset_.push_back(data);
			}

			ds.serialize(mv::IO::appendFilenameToFolderPath(startingResultsFolder_, kDatasetFilenameExtension_).c_str());
		}
	}
}

} /* namespace barcode */
