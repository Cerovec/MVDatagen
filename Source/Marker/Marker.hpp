/**
 * \file
 *
 * Marker.h
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

#ifndef MARKER_H_
#define MARKER_H_

#include <iostream>
#include <fstream>
#include "Utils/IO.hpp"

namespace mv {

class Marker {

private:
	/**
	 * Folder in which the starting dataset is placed
	 */
	const std::string startingResultsFolder_;


public:
	/**
	 * Datset filename extension
	 */
	static const std::string DATASET_FILENAME_EXTENSION;

	/**
	 * Constructor
	 */
	Marker(std::string startingResultsFolder) : startingResultsFolder_(startingResultsFolder) {
		// nothing to do
	}

	/**
	 * Destructor
	 */
	virtual ~Marker() {
		// nothing to do
	}

	/**
	 * Checks if dataset already exists in given folder
	 */
	bool datasetExists() {
		std::ifstream file(mv::IO::appendFilenameToFolderPath(startingResultsFolder_, DATASET_FILENAME_EXTENSION).c_str());
		return (file.good());
	}

	/**
	 * Performs the dataset marking
	 */
	void markDataset();

	/**
	 * Performs the dataset marking - ignores images that are already in dataset
	 */
	void updateDataset();

	/**
	 * shows images and their marks from dataset
	 */
	void showDataset();

	/**
	 * method filters the dataset by removing all points that are too close and leaving just one
	 * this is required to filter out errors introduced by accidentaly double-clicking the same
	 * point while marking the dataset
	 */
	void filterDataset();
};

} /* namespace mv */
#endif /* MARKER_H_ */
