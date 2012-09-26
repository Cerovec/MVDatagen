/*
 * MatrixModifier.hpp
 *
 *  Created on: Sep 26, 2012
 *      Author: dodo
 */

#ifndef MATRIXMODIFIER_HPP_
#define MATRIXMODIFIER_HPP_

#include "CommonHeaders.h"

namespace gpumv {

class MatrixModifier {
public:
	MatrixModifier();
	virtual ~MatrixModifier();

	MatrixModifier& translate(float x, float y, float z);
	MatrixModifier& rotateAroundX(float radians);
	MatrixModifier& rotateAroundY(float radians);
	MatrixModifier& rotateAroundZ(float radians);
	MatrixModifier& scale(float x, float y, float z);

	cv::Mat getTransformMatrix() const { return transformMat_; }

private:
	cv::Mat transformMat_;
};

} /* namespace gpumv */
#endif /* MATRIXMODIFIER_HPP_ */
