/*
 * MatrixModifier.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: dodo
 */

#include "MatrixModifier.hpp"

namespace gpumv {

MatrixModifier::MatrixModifier() :
	transformMat_(cv::Mat::eye(4, 4, CV_32F)) {}

MatrixModifier::~MatrixModifier() {}

MatrixModifier& MatrixModifier::translate(float x, float y, float z) {
	// create translation matrix
	cv::Mat translation = cv::Mat::eye(4, 4, CV_32F);
	translation.at<float>(0, 3) = x;
	translation.at<float>(1, 3) = y;
	translation.at<float>(2, 3) = z;
	transformMat_ = translation * transformMat_;
	return *this;
}

MatrixModifier& MatrixModifier::rotateAroundX(float radians) {
	// create rotation around X matrix
	cv::Mat xrot = cv::Mat::eye(4, 4, CV_32F);
	float c = cosf(radians), s = sinf(radians);
	xrot.at<float>(1, 1) = c;
	xrot.at<float>(1, 2) = -s;
	xrot.at<float>(2, 1) = s;
	xrot.at<float>(2, 2) = c;
	transformMat_ = xrot * transformMat_;
	return *this;
}

MatrixModifier& MatrixModifier::rotateAroundY(float radians) {
	// create rotation around Y matrix
	cv::Mat yrot = cv::Mat::eye(4, 4, CV_32F);
	float c = cosf(radians), s = sinf(radians);
	yrot.at<float>(0, 0) = c;
	yrot.at<float>(0, 2) = s;
	yrot.at<float>(2, 0) = -s;
	yrot.at<float>(2, 2) = c;
	transformMat_ = yrot * transformMat_;
	return *this;
}

MatrixModifier& MatrixModifier::rotateAroundZ(float radians) {
	// create rotation around Z matrix
	cv::Mat zrot = cv::Mat::eye(4, 4, CV_32F);
	float c = cosf(radians), s = sinf(radians);
	zrot.at<float>(0, 0) = c;
	zrot.at<float>(0, 1) = -s;
	zrot.at<float>(1, 0) = s;
	zrot.at<float>(1, 1) = c;
	transformMat_ = zrot * transformMat_;
	return *this;
}

MatrixModifier& MatrixModifier::scale(float x, float y, float z) {
	// create scale matrix
	cv::Mat scale = cv::Mat::eye(4, 4, CV_32F);
	scale.at<float>(0, 0) = x;
	scale.at<float>(1, 1) = y;
	scale.at<float>(2, 2) = z;
	transformMat_ = scale * transformMat_;
	return *this;
}

} /* namespace gpumv */
