/**
 * \file
 *
 * BlurGenerator.h
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

#ifndef BLURGENERATOR_H_
#define BLURGENERATOR_H_

#include "Generator/Generator.hpp"
#include "Utils/Utils.hpp"

namespace mv {

/**
 * Class generates samples that are blurred
 */
class BlurGenerator: public mv::Generator {

protected:
	/**
	 * Variance of white noise
	 */
	const unsigned int blurRadius_;

	/** Forbids copy constructor and assignment operator */
	DISALLOW_COPY_AND_ASSIGN(BlurGenerator);

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

	/**
	 * Constructor
	 */
	BlurGenerator(const std::string startingResultsFolder, const std::string generatedResultsFolder,
			const int numSamples, const unsigned int blurRadius) :
				Generator(startingResultsFolder, generatedResultsFolder, numSamples),
				blurRadius_(blurRadius) {
		// nothing to do
	}

	virtual ~BlurGenerator() {
		// TODO Auto-generated destructor stub
	}
};

} /* namespace mv */
#endif /* BLURGENERATOR_H_ */
