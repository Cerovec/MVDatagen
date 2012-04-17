/**
 * \file
 *
 * CopyGenerator.h
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

#ifndef COPYGENERATOR_H_
#define COPYGENERATOR_H_

#include "Generator.h"
#include "Utils/Utils.h"

namespace mv {

class CopyGenerator: public mv::Generator {
protected:
	/** Forbids copy constructor and assignment operator */
	DISALLOW_COPY_AND_ASSIGN(CopyGenerator);

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
	CopyGenerator(const std::string startingResultsFolder, const std::string generatedResultsFolder) :
		Generator(startingResultsFolder, generatedResultsFolder, 1) {
		// nothing to do
	}

	virtual ~CopyGenerator() {
		// nothing to do
	}
};

} /* namespace mv */
#endif /* COPYGENERATOR_H_ */
