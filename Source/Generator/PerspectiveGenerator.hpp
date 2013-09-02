/**
 * \file
 *
 * PerspectiveGenerator.h
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
#ifndef PERSPECTIVEGENERATOR_H_
#define PERSPECTIVEGENERATOR_H_

#include "Generator/Generator.hpp"
#include "Utils/Utils.hpp"
#include <opencv2/opencv.hpp>

namespace mv {

/**
 * Class generates samples that are blurred
 */
class PerspectiveGenerator: public mv::Generator {

protected:
	/**
	 * Variance of white noise
	 */
	const double perspectiveVariance_;

	/** Forbids copy constructor and assignment operator */
	DISALLOW_COPY_AND_ASSIGN(PerspectiveGenerator);

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
	PerspectiveGenerator(const std::string startingResultsFolder, const std::string generatedResultsFolder,
			const int numSamples, const unsigned int perspectiveVariance) :
				Generator(startingResultsFolder, generatedResultsFolder, numSamples),
				perspectiveVariance_(perspectiveVariance) {
		// nothing to do
	}

	virtual ~PerspectiveGenerator() {
		// TODO Auto-generated destructor stub
	}
};

} /* namespace mv */

#endif /* PERSPECTIVEGENERATOR_H_ */
