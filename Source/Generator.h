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
#include "MVDatagen.h"
#include <string>

namespace mv {

/**
 * Abstract class for generating machine vision dataset
 */
class Generator {
private:
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
	 * Next generator in responsibility chain
	 */
	Generator* next_;

	/** Forbids copy constructor and assignment operator */
	DISALLOW_COPY_AND_ASSIGN(Generator);

protected:

	/**
	 * The method does the bulk work.
	 * It takes all images from the folder where <startingResultsFile> is placed,
	 * does performs the distorting of the image, saves the image in folder where <generatedResultsFile> is placed,
	 * then calcualtes new results based on the given ones, and saves them to a file <generatedResultsFile>
	 */
	virtual void generateSamples() = 0;

public:

	/**
	 * Constructor
	 */
	Generator(const std::string startingResultsFilename, const std::string generatedResultsFilename, const int numSamples) :
		startingResultsFilename_(startingResultsFilename),
		generatedResultsFilename_(generatedResultsFilename),
		numSamples_(numSamples), next_(NULL) {
		// nothing to do
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

	void generateDataset();

};

} /* namespace mv */
#endif /* GENERATOR_H_ */
