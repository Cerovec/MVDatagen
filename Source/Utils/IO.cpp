/**
 * \file
 *
 * ImageIO.cpp
 *
 *  Created on: Feb 11, 2012
 *      Author: cerovec
 */

#include "IO.hpp"
#include "Geometry.hpp"
#include <stdio.h>
#ifndef _WIN32
#endif

namespace mv {

void IO::saveImageToFile(const cv::Mat& image, const char* filename) {
	cv::imwrite(filename, image);
}

void IO::loadImageFromFile(cv::Mat& image, const char* filename) {
	image = cv::imread(filename);
	if (image.data == NULL) {
		fprintf(stderr, "Cannot load image, invalid filename %s", filename);
	}
}

void IO::displayImage(const cv::Mat& image, const char* title) {

#ifdef IMSHOW
	cv::namedWindow(title);

	cv::imshow(title, image);
#endif
}

class MouseCallback {
private:
	cv::Mat* image_;

public:
	cv::Size originalImageSize_;

	const char* windowTitle_;

	std::vector<cv::Point> clickedPoints_;

	MouseCallback(cv::Mat* image, const char* windowTitle, std::vector<cv::Point>& clickedPoints) :
		image_(image), originalImageSize_(cv::Size(image->cols, image->rows)), windowTitle_(windowTitle),
		clickedPoints_(clickedPoints) {
	}

	void display() {
		cv::Mat dispImage = image_->clone();
		double ratio = (double)(image_->cols) / (double) originalImageSize_.width;
		for (unsigned int i = 0; i < clickedPoints_.size(); i++) {
			cv::circle(dispImage, clickedPoints_[i] * ratio, 5, cv::Scalar(0, 0, 255, 0), 2, 1, 0);
		}
		IO::displayImage(dispImage, windowTitle_);
	}

	void pushPoint(cv::Point& point) {
		double ratio = originalImageSize_.width / (double)(image_->cols);
        cv::Point resizedPoint = ratio * point;
        clickedPoints_.push_back(resizedPoint);
        display();
    }

	void popPoint() {
		if (!clickedPoints_.empty()) {
			clickedPoints_.pop_back();
		}
		display();
	}
};

void onMouseClick(int event, int x, int y, int flags, void* ptr) {
    if (event != CV_EVENT_LBUTTONDOWN)
        return;

    cv::Point seed = cv::Point(x, y);

    MouseCallback *callback = static_cast<MouseCallback*>(ptr);
    callback->pushPoint(seed);
}


void IO::handleUserInput(const cv::Mat& image, const char* title, std::vector<cv::Point>& points, std::vector<std::string>& marks) {
#ifdef IMSHOW
    int key;
	cv::Mat currentImage = image.clone();

	mv::MouseCallback callback(&currentImage, title, points);

	cv::setMouseCallback(title, onMouseClick, &callback);

	while(1) {
		/* wait for keyboard input */
		key = cv::waitKey(0) % 0x100;

		/* 'q' pressed, quit the program */
		if (key == ' ') break;

		switch(key) {
			/* '+' pressed, zoom in the image and display larger image */
			case '+':
				mv::zoomImage(currentImage, currentImage, 40);
				callback.display();
				break;

			/* '2' pressed, zoom out the image */
			case '-':
				mv::zoomImage(currentImage, currentImage, -40);
				callback.display();
				break;

			/* 'backspace' pressed, remove last clicked point */
			case '\b':
			case 127:
				callback.popPoint();
				break;
		}
	}

	points = callback.clickedPoints_;
#endif
}

void IO::findImageFilenames(std::string folderName, std::vector<std::string>& imageFilenames) {
#ifndef _WIN32
	DIR *d;
	struct dirent* dirent;

	d = opendir(folderName.c_str());
	if (!d) {
		fprintf(stderr, "Invalid directory %s", folderName.c_str());
	} else {
		while ((dirent = readdir(d)) != NULL) {
			std::string filename(dirent->d_name);
			if (isSupportedFileType(filename)) {
				imageFilenames.push_back(folderName + "/" + filename);
			}
		}

		closedir(d);
	}
#endif
}

} /* namespace photopay */
