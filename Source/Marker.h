/**
 * \file
 *
 * Marker.h
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

#ifndef MARKER_H_
#define MARKER_H_

#include "MVDatagen.h"
#include <string>
#include <vector>

namespace mv {

/**
 * Class responsible for marking of images
 */
class Marker {
private:
	/**
	 * File in which the marked results are places
	 */
	std::string folderName_;

	/**
	 * Forbid copy construcor and assignment operator
	 */
	DISALLOW_COPY_AND_ASSIGN(Marker);

	/**
	 * Returns true if the file with a given filename is supported by the marker
	 */
	bool isSupportedFileType(std::string filename) {
		size_t position = filename.find_last_of('.');

		std::string extension = filename.substr(position + 1);

		return (extension.compare("jpg") == 0 ||
			extension.compare("JPG") == 0 ||
			extension.compare("png") == 0 ||
			extension.compare("PNG") == 0 ||
			extension.compare("bmp") == 0 ||
			extension.compare("BMP") == 0);
	}

	/**
	 * Method fills the vector of image filenames (with full path) on which tha marking process should be done
	 */
	void findImageFilenames(const std::string folderName, std::vector<std::string>& imageFilenames);

public:

	/**
	 * Constructor
	 */
	Marker(std::string folderName) : folderName_(folderName) {
		// nothing to do
	}

	/**
	 * Destructor
	 */
	virtual ~Marker() {
		// nothing to do
	}

	/**
	 * Performs marking process
	 */
	void markDataset();
};

} /* namespace mv */
#endif /* MARKER_H_ */
