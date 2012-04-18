/**
 * \file
 *
 * FlipGenerator.h
 *
 *  Created on: Apr 18, 2012
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

#ifndef FLIPGENERATOR_H_
#define FLIPGENERATOR_H_

#include "Generator.h"

namespace mv {

class FlipGenerator: public mv::Generator {

protected:
	/** Forbids copy constructor and assignment operator */
	DISALLOW_COPY_AND_ASSIGN(FlipGenerator);

	/**
	 * Returns the generator's name
	 */
	virtual std::string getGeneratorName() const;

	/**
	 * Performs generation process
	 */
	void generateSample(const ImageData& originalSample,
			ImageData& generatedSample, std::string& generatedFilename) const;

public:
	FlipGenerator(const std::string startingResultsFolder, const std::string generatedResultsFolder, const int flipNum) :
		Generator(startingResultsFolder, generatedResultsFolder, flipNum != 0) {
		// nothing to do
	}

	virtual ~FlipGenerator() {
		// nothing to do
	}
};

} /* namespace mv */
#endif /* FLIPGENERATOR_H_ */
