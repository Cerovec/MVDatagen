/**
 * \file
 *
 * NoiseGenerator.h
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

#ifndef NOISEGENERATOR_H_
#define NOISEGENERATOR_H_

#include "Generator.h"
#include "MVDatagen.h"

namespace mv {

/**
 * Generates samples with additive white gaussian noise
 */
class NoiseGenerator : public mv::Generator {
private:
	/**
	 * Variance of white noise
	 */
	const double noiseVariance_;

	/** Forbids copy constructor and assignment operator */
	DISALLOW_COPY_AND_ASSIGN(NoiseGenerator);

public:

	/**
	 * Constructor
	 */
	NoiseGenerator(const std::string startingResultsFilename, const std::string generatedResultsFilename,
			const int numSamples, const double noiseVariance) :
				Generator(startingResultsFilename, generatedResultsFilename, numSamples),
				noiseVariance_(noiseVariance) {
		// nothing to do
	}

	virtual ~NoiseGenerator() {
		// TODO Auto-generated destructor stub
	}

	/**
	 * Performs generation process
	 */
	void generateSamples();
};

} /* namespace mv */
#endif /* NOISEGENERATOR_H_ */
