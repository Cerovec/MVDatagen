/**
 * \file
 *
 * PerspectiveGenerator.h
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

#ifndef PERSPECTIVEGENERATOR_H_
#define PERSPECTIVEGENERATOR_H_

#include "Generator.h"
#include "MVDatagen.h"

namespace mv {

class PerspectiveGenerator: public mv::Generator {
private:

	/**
	 * Regulates strength of perspective distortion
	 */
	double perspectiveVariance_;

	/** Forbids copy constructor and assignment operator */
	DISALLOW_COPY_AND_ASSIGN(PerspectiveGenerator);

public:

	/**
	 * Constructor
	 */
	PerspectiveGenerator(const std::string startingResultsFilename, const std::string generatedResultsFilename,
			const int numSamples, const double perspectiveVariance) :
				Generator(startingResultsFilename, generatedResultsFilename, numSamples),
				perspectiveVariance_(perspectiveVariance) {
		// nothing to do
	}

	virtual ~PerspectiveGenerator() {
		// nothing to do
	}

	void generateSamples();
};

} /* namespace mv */
#endif /* PERSPECTIVEGENERATOR_H_ */
