/**
 * \file
 *
 * Dataset.h
 *
 *  Created on: Apr 12, 2012
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

#ifndef DATASET_H_
#define DATASET_H_

#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

namespace mv {

/**
 * Represents marked data for one image
 */
class ImageData {
public:
	/**
	 * Default constructor
	 */
	ImageData() {
		// nothing to do;
	}

	/**
	 * Constructor for image data. Takes the image filename
	 */
	ImageData(std::string filename) : filename_(filename) {
	}

	/**
	 * Destructor
	 */
	virtual ~ImageData() {
	}

	/**
	 * Copy constructor
	 */
	ImageData(const ImageData& other) : filename_(other.filename_), points_(other.points_), marks_(other.marks_) {
	}

	/**
	 * assignment operator
	 */
	ImageData& operator=(const ImageData& other) {
		if (this != & other) {
			filename_ = other.filename_;
			points_ = other.points_;
			marks_ = other.marks_;
		}
		return *this;
	}

	/**
	 * Serializes the image data to output stream
	 */
	void serialize(std::ostream& stream);

	/**
	 * deserializes the object from input stream
	 */
	void deserialize(std::istream& stream);

	/**
	 * Outputs the data to std::out
	 */
	void print() const {
		printf("Filename: %s\n", filename_.c_str());
		printf("Points: ");
		for (unsigned int i = 0; i < points_.size(); i++) {
			printf("[%d,%d] ", points_[i].x, points_[i].y);
		}
		printf("\nMarks: ");
		for (unsigned int i = 0; i < marks_.size(); i++) {
			printf("\"%s\" ", marks_[i].c_str());
		}
		printf("\n\n");
	}

	/**
	 * Displays the image and it's points
	 */
	void display(const std::string& folderName) const;

	/**
	 * Image file name
	 */
	std::string filename_;

	/**
	 * Points marked on the image
	 */
	std::vector<cv::Point> points_;

	/**
	 * Other string marks for the image
	 */
	std::vector<std::string> marks_;
};

/**
 * Represents dataset for all images in dataset
 */
class Dataset {
public:
	/**
	 * Constructor, creates a vector with image data objects
	 */
	Dataset();

	/**
	 * Destructor
	 */
	virtual ~Dataset();

	/**
	 * Serializes the dataset to file
	 */
	void serialize(const std::string& filename);

	/**
	 * Creates the dataset from file
	 */
	void deserialize(const std::string& filename);

	/**
	 * Outputs the dataset to std::out
	 */
	void print() const {
		for (unsigned int i = 0; i < dataset_.size(); i++) {
			dataset_[i].print();
			printf("\n");
		}
	}

	void display(const std::string& folderName) const {
		for (unsigned int i = 0; i < dataset_.size(); i++) {
			dataset_[i].display(folderName);
		}
	}

	/**
	 * Image data objects
	 */
	std::vector<ImageData> dataset_;
};

} /* namespace mv */
#endif /* DATASET_H_ */
