/**
 * \file
 *
 * Geometry.h
 *
 *  Created on: Apr 13, 2012
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
#include <vector>

namespace mv {

inline static void zoomImage(const cv::Mat& input, cv::Mat& output, unsigned int widthIncrease) {
	if (input.cols + widthIncrease > 0) {
		int newWidth = input.cols + widthIncrease;
		int newHeight = newWidth / (double) input.cols * input.rows;
		cv::resize(input, output, cv::Size(newWidth, newHeight), 0, 0, cv::INTER_LANCZOS4);
	} else {
		output = input.clone();
	}
}

inline static void perspectiveTranform(const std::vector<cv::Point>& originalPoints,
		std::vector<cv::Point>& transformedPoints, cv::Mat& transformMatrix) {

	for (unsigned int i = 0; i < originalPoints.size(); i++) {
		int x = originalPoints[i].x;
		int y = originalPoints[i].y;
		float xet = transformMatrix.at<float>(0, 0) * x + transformMatrix.at<float>(0, 1) * y + transformMatrix.at<float>(0, 2);
		float xdt = transformMatrix.at<float>(2, 0) * x + transformMatrix.at<float>(2, 1) * y + transformMatrix.at<float>(2, 2);
		float yet = transformMatrix.at<float>(1, 0) * x + transformMatrix.at<float>(1, 1) * y + transformMatrix.at<float>(1, 2);
		if (fabs(xdt) > 0.0001) {
			transformedPoints.push_back(cv::Point(xet / xdt, yet / xdt));
		} else {
			transformedPoints.push_back(cv::Point(0, 0));
		}
	}
}

inline static bool arePointsInside(const std::vector<cv::Point>& points, const cv::Size& imageSize) {
	for (unsigned int i = 0; i < points.size(); i++) {
		if (points[i].x >= imageSize.width || points[i].y >= imageSize.height) {
			return false;
		}
	}
	return true;
}

} // namespace

#endif /* GEOMETRY_H_ */
