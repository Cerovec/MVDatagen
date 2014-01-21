/**
 * \file
 *
 * Dataset.cpp
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

#include "Dataset.hpp"
#include "Utils/StringUtils.hpp"
#include "Utils/IO.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>

namespace mv {

void ImageData::display(const std::string& folderName) const {
	cv::Mat image;
	IO::loadImageFromFile(image, IO::appendFilenameToFolderPath(folderName, filename_).c_str());

	for (unsigned int i = 0; i < points_.size(); i++) {
		cv::circle(image, points_[i], 5, cv::Scalar(255, 255, 255, 0), 2, 1, 0);
	}

	IO::displayImage(image, "Dataset");
#ifdef IMSHOW
	cv::waitKey(0);
	cv::destroyWindow("Dataset");
#endif
}

void ImageData::serialize(std::ostream& stream) {
	if(points_.size()>0 || marks_.size()>0) {
		unsigned int i;
		// filename
		stream << "\"Filename\": \""  << filename_ << "\"; ";

		// points
		stream << "\"Points\": [";

		if (points_.size() > 1) {
			for (i = 0; i < points_.size()-1; i++) {
				stream << "[" << points_[i].x << "," << points_[i].y << "], ";
			}
			stream << "[" << points_[i].x << "," << points_[i].y << "]";
		} else if (points_.size() == 1) {
			stream << "[" << points_[0].x << "," << points_[0].y << "]";
		}

		// marks
		stream << "]; \"Marks\": [";
		if (marks_.size() > 1) {
			for (i = 0; i < marks_.size()-1; i++) {
				stream << "\"" << marks_[i] << "\", ";
			}
			stream << "\"" << marks_[i] << "\"]" << std::endl;
		} else if (marks_.size() == 1) {
			stream << "\"" << marks_[0] << "\"]" << std::endl;
		} else {
			stream << "]" << std::endl;
		}
	}
}

void ImageData::deserialize(std::istream& stream) {
	std::string line;
	std::getline(stream, line);

	if (trim(line).compare("") == 0) {
		return;
	}

	std::istringstream iss(line);

	std::vector<std::string> properties;
	mv::split(line, ';', properties);

	for (unsigned int i = 0; i < properties.size(); i++) {
		std::vector<std::string> parts;
		parts.clear();
		mv::split(properties[i], ':', parts);

		if (parts.size() == 2) { // has to be true
			std::string key = trim(parts[0]);
			std::string value = trim(parts[1]);

			if (key.compare("\"Filename\"") == 0 && value.length() > 2) {
				filename_ = value.substr(1, value.length() - 2);
			} else if (key.compare("\"Points\"") == 0) {
				std::vector<std::string> pointParts;
				mv::split(value, ']', pointParts);

				for (unsigned int j = 0; j < pointParts.size(); j++) {
					size_t startIndex = pointParts[j].find_last_of("[");
					if (startIndex != std::string::npos && startIndex < pointParts[j].size() - 1) {
						int x, y;
						sscanf(pointParts[j].substr(startIndex+1).c_str(), "%d,%d", &x, &y);
						points_.push_back(cv::Point(x, y));
					}
				}
			} else if (key.compare("\"Marks\"") == 0) {
				std::vector<std::string> pointParts;
				mv::split(value.substr(1, value.length()-2), ',', pointParts);

				for (unsigned int j = 0; j < pointParts.size(); j++) {
					std::string trimmed = trim(pointParts[j]);
					if (trimmed.length() > 0) {
						if (trimmed[0] == '\"') {
							if (trimmed.length() > 2) {
								marks_.push_back(trimmed.substr(1, trimmed.length() - 2));
							}
						} else {
							marks_.push_back(trimmed);
						}
					}
				}
			}
		}
	}
}

Dataset::Dataset() {
	// nothing to do
}

Dataset::~Dataset() {
	// nothing to do
}

void Dataset::serialize(const std::string& filename) {
	std::ofstream ofs(filename.c_str());

	if (ofs.is_open()) {
		for (unsigned int i = 0; i < dataset_.size(); i++) {
			dataset_[i].serialize(ofs);
		}

		ofs.flush();
		ofs.close();
	}
}

std::istream& operator>>(std::istream& str, ImageData& data) {
    data.deserialize(str);
    return str;
}

void Dataset::deserialize(const std::string& filename) {
	std::ifstream ifs(filename.c_str());

	if (ifs.is_open()) {
		ImageData data;
		while (ifs >> data) {
			dataset_.push_back(data);
			data.filename_ = "";
			data.points_.clear();
			data.marks_.clear();
		}

		ifs.close();
	} else {
		fprintf(stderr, "Unable to open %s!\n", filename.c_str());
	}
}

Dataset::Dataset(const Dataset& other) :
    dataset_(other.dataset_) {
}

Dataset& Dataset::operator =(const Dataset& other) {
    if(this!=&other) {
        dataset_ = other.dataset_;
    }
    return *this;
}

} /* namespace mv */
