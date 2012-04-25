/**
 * \file
 *
 * Geometry.cpp
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

#include "Geometry.h"

namespace mv {

void Geometry::zoomImage(const cv::Mat& input, cv::Mat& output, unsigned int widthIncrease) {

	// explicitly specify dsize=dst.size(); fx and fy will be computed from that.
	int newWidth = input.cols + widthIncrease;
	int newHeight = newWidth / (double) input.cols * input.rows;
	cv::resize(input, output, cv::Size(newWidth, newHeight), 0, 0, cv::INTER_LANCZOS4);
}

} /* namespace mv */
