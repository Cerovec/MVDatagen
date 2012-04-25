/**
 * \file
 *
 * ImageIO.h
 *
 *  Created on: Feb 11, 2012
 *      Author: cerovec
 */

#ifndef IMAGEIO_H_
#define IMAGEIO_H_

#include <vector>
#include <opencv2/opencv.hpp>

namespace cv {
	class Mat;
}

namespace mv {

class ImageIO {
private:
	ImageIO() {
		// TODO Auto-generated constructor stub

	}
	virtual ~ImageIO() {
		// TODO Auto-generated destructor stub
	}

public:

	static void saveImageToFile(const cv::Mat& image, const char* filename);

	static void loadImageFromFile(cv::Mat& image, const char* filename);

	static void displayImage(const cv::Mat& image, const char* title);

	static void handleUserInput(const cv::Mat& image, const char* title, std::vector<cv::Point>& points, std::vector<std::string>& marks);

};

}

 /* namespace photopay */
#endif /* IMAGEIO_H_ */
