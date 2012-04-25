/**
 * \file
 *
 * ImageIO.cpp
 *
 *  Created on: Feb 11, 2012
 *      Author: cerovec
 */

#include "ImageIO.h"
#include "Geometry.h"
#include <string>
#include <stdio.h>

#define ENABLE_IMSHOW

namespace mv {

void ImageIO::saveImageToFile(const cv::Mat& image, const char* filename) {
	cv::imwrite(filename, image);
}

void ImageIO::loadImageFromFile(cv::Mat& image, const char* filename) {
	image = cv::imread(filename);
	if (image.data == NULL) {
		fprintf(stderr, "Cannot load image, invalid filename %s", filename);
	}
}

void ImageIO::displayImage(const cv::Mat& image, const char* title) {

#ifdef ENABLE_IMSHOW
	cv::namedWindow(title);

	cv::imshow(title, image);
#endif
}

class MouseCallback {
private:
	const cv::Size originalImageSize_;

public:
	cv::Size zoomedImageSize_;

	std::vector<cv::Point> clickedPoints_;

	MouseCallback(const cv::Size originalImageSize, std::vector<cv::Point>& clickedPoints) :
		originalImageSize_(originalImageSize), zoomedImageSize_(originalImageSize), clickedPoints_(clickedPoints) {
	}

	void addPoint(cv::Point& point) {
		double ratio = originalImageSize_.width / (double)(zoomedImageSize_.width);
        cv::Point resizedPoint = ratio * point;
        clickedPoints_.push_back(resizedPoint);
        printf("%d %d ", resizedPoint.x, resizedPoint.y);
    }
};

void onMouseClick(int event, int x, int y, int flags, void* ptr) {
    if( event != CV_EVENT_LBUTTONDOWN )
        return;

    cv::Point seed = cv::Point(x, y);

    MouseCallback *callback = static_cast<MouseCallback*>(ptr);
    callback->addPoint(seed);
}


void ImageIO::handleUserInput(const cv::Mat& image, const char* title, std::vector<cv::Point>& points, std::vector<std::string>& marks) {
	int key;
	cv::Mat currentImage = image.clone();

	mv::MouseCallback callback(cv::Size(image.cols, image.rows), points);

	cv::setMouseCallback(title, onMouseClick, &callback);

	while(1) {
		/* wait for keyboard input */
		key = cvWaitKey(0);

		/* 'q' pressed, quit the program */
		if (key == ' ') break;

		switch(key) {
			/* '+' pressed, zoom in the image and display larger image */
			case '+':
				mv::Geometry::zoomImage(currentImage, currentImage, 40);
				mv::ImageIO::displayImage(currentImage, title);
				callback.zoomedImageSize_ = cv::Size(currentImage.cols, currentImage.rows);
				break;

			/* '2' pressed, zoom out the image */
			case '-':
				mv::Geometry::zoomImage(currentImage, currentImage, -40);
				mv::ImageIO::displayImage(currentImage, title);
				callback.zoomedImageSize_ = cv::Size(currentImage.cols, currentImage.rows);
				break;
		}
	}

	points = callback.clickedPoints_;
}

} /* namespace photopay */
