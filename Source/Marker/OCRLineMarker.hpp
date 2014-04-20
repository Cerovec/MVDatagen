/*
 * OCRLineMarker.hpp
 *
 *  Created on: Jun 11, 2013
 *      Author: boris
 */

#ifndef OCRLINEMARKER_HPP_
#define OCRLINEMARKER_HPP_

#include "CommonHeaders.h"
#include "Marker.hpp"

namespace mv {

class OCRLineMarker: public mv::Marker {
private:
	float imagePercentage_;

	/**
	 * Based on seed point generates four points that selects horizontal
	 * image area which selects imagePercentage_ of image height
	 */
	void getOcrLinePoints(const cv::Point& seed,
						  const cv::Size& imageSize,
						  std::vector<cv::Point>& points);

public:
	/**
	 * Constructor
	 */
	OCRLineMarker(std::string startingResultsFolder,
				  int imagePercentage);

	/**
	 * Destructor
	 */
	virtual ~OCRLineMarker();

	/**
	 * Performs the dataset marking
	 */
	virtual void markDataset();

	/**
	 * Performs the dataset marking - ignores images that are already in dataset
	 */
	virtual void updateDataset();
};

} /* namespace barcode */
#endif /* OCRLINEMARKER_HPP_ */
