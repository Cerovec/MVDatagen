/**
 * \file
 *
 * Generator.h
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

#ifndef GENERATOR_H_
#define GENERATOR_H_

#include <stdlib.h>
#include <string>
#include <opencv2/opencv.hpp>
#include "Utils/Utils.hpp"
#include "Marker/Marker.hpp"
#include "Dataset.hpp"

namespace mv {

/**
 * Abstract class for generating machine vision dataset
 */
class Generator {
protected:

	/**
	 * Folder in which the generated dataset is placed
	 */
	const std::string startingResultsFolder_;

	/**
	 * Folder in which the generated dataset is placed
	 */
	const std::string generatedResultsFolder_;

	/**
	 * File in which the generated dataset is placed
	 */
	const std::string startingResultsFilename_;

	/**
	 * File in which the generated dataset is placed
	 */
	const std::string generatedResultsFilename_;

	/**
	 * Number of generated samples for each original sample
	 */
	const unsigned int numSamples_;

	/**
	 * Random number generator
	 */
	static cv::RNG RNG;

	/**
	 * Next generator in responsibility chain
	 */
	Generator* next_;

	/** Forbids copy constructor and assignment operator */
	DISALLOW_COPY_AND_ASSIGN(Generator);

	/**
	 * The method does the bulk work.
	 * It takes all images from the folder where <startingResultsFile> is placed,
	 * does performs the distorting of the image, saves the image in folder where
	 * <generatedResultsFile> is placed, then calcualtes new results based on
	 * the given ones, and saves them to a file <generatedResultsFile>
	 */
	virtual void generateSamplesInDataset(const Dataset& original, Dataset& generated) const;

	/**
	 * Function creates a filename for the generated image based on original
	 * image filename and index of the generated image
	 */
	virtual std::string createFilename(const std::string& originalFilename,
			const unsigned int index) const;

	/**
	 * Returns the generator's name
	 */
	virtual std::string getGeneratorName() const = 0;

	/**
	 * Method generates the transformed sample based on the original sample
	 */
	virtual void generateSample(const ImageData& originalSample,
			ImageData& generatedSample, std::string& generatedFilename) const = 0;

public:

	/**
	 * Constructor
	 */
	Generator(const std::string startingResultsFolder, const std::string generatedResultsFolder, const int numSamples) :
		startingResultsFolder_(startingResultsFolder), generatedResultsFolder_(generatedResultsFolder),
		startingResultsFilename_(startingResultsFolder + Marker::DATASET_FILENAME_EXTENSION),
		generatedResultsFilename_(generatedResultsFolder + Marker::DATASET_FILENAME_EXTENSION),
		numSamples_(numSamples), next_(NULL) {
	}

	/**
	 * Sets the next generator in generator chain
	 */
	void setNext(Generator* next) {
		next_ = next;
	}

	/**
	 * Destructor
	 */
	virtual ~Generator() {
		// nothing to do
	}

	/**
	 * Loads the dataset from specified filename (startingResultsFilename)
	 */
	void loadDataset(Dataset& dataset) const {
		dataset.deserialize(startingResultsFilename_);
	}

	/**
	 * Saves the dataset to specified file (generatedResultsFilename)
	 */
	void saveDataset(Dataset& dataset) const {
		dataset.serialize(generatedResultsFilename_);
	}

	/**
	 * Generates the new dataset and saves it to
	 */
	void generateDataset() const;

};

} /* namespace mv */
#endif /* GENERATOR_H_ */
