/**
 * \file
 *
 * Geometry.h
 *
 *  Created on: Apr 5, 2012
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

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <opencv2/opencv.hpp>

namespace mv {

class Geometry {
private:
	Geometry() {
		// static class
	}
	virtual ~Geometry() {
		// static class
	}

public:

	static void zoomImage(const cv::Mat& input, cv::Mat& output, unsigned int widthIncrease);
};

} /* namespace mv */
#endif /* GEOMETRY_H_ */
