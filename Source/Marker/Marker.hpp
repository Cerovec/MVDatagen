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

#pragma once

#include "CommonHeaders.h"
#include "Utils/IO.hpp"
#include "Counted.hpp"
#include <fstream>

namespace mv {

class Marker : public Counted {

protected:
	/**
	 * Folder in which the starting dataset is placed
	 */
	const std::string startingResultsFolder_;

	/**
	 * Datset filename extension
	 */
	const std::string kDatasetFilenameExtension_;

public:
	/**
	 * Datset filename extension
	 */
	static const std::string DATASET_FILENAME_EXTENSION;

	/**
	 * Constructor
	 */
	Marker(std::string startingResultsFolder) :
		startingResultsFolder_(startingResultsFolder),
		kDatasetFilenameExtension_("/dataset.txt"){
		// nothing to do
	}

	Marker(std::string startingResultsFolder,
		   std::string datasetFilenameExtension) :
		startingResultsFolder_(startingResultsFolder),
		kDatasetFilenameExtension_(datasetFilenameExtension){
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
        std::ifstream file(mv::IO::appendFilenameToFolderPath(startingResultsFolder_, kDatasetFilenameExtension_).c_str());
		return (file.good());
	}

	/**
	 * Performs the dataset marking
	 */
	virtual void markDataset();

	/**
	 * Performs the dataset marking - ignores images that are already in dataset
	 */
	virtual void updateDataset();

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
