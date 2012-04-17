/**
 * \file
 *
 * ImageIO.h
 *
 *  Created on: Feb 11, 2012
 *      Author: cerovec
 */

#ifndef IO_H_
#define IO_H_

#include <vector>
#include <opencv2/opencv.hpp>

namespace cv {
	class Mat;
}

namespace mv {

class IO {
private:
	IO() {
		// TODO Auto-generated constructor stub

	}
	virtual ~IO() {
		// TODO Auto-generated destructor stub
	}

public:

	static void saveImageToFile(const cv::Mat& image, const char* filename);

	static void loadImageFromFile(cv::Mat& image, const char* filename);

	static void displayImage(const cv::Mat& image, const char* title);

	static void handleUserInput(const cv::Mat& image, const char* title, std::vector<cv::Point>& points, std::vector<std::string>& marks);

	static void findImageFilenames(const std::string folderName, std::vector<std::string>& imageFilenames);

	/**
	 * Returns true if the file with a given filename is supported by the marker
	 */
	static bool isSupportedFileType(std::string filename) {
		size_t position = filename.find_last_of('.');

		std::string extension = filename.substr(position + 1);

		return (extension.compare("jpg") == 0 ||
			extension.compare("JPG") == 0 ||
			extension.compare("png") == 0 ||
			extension.compare("PNG") == 0 ||
			extension.compare("bmp") == 0 ||
			extension.compare("BMP") == 0);
	}

	static std::string getFilenameFromPath(const std::string& path) {
		// find filename
		size_t startFilename = path.find_last_of("/");
		if (startFilename == std::string::npos) {
			startFilename = 0;
		}
		return path.substr(startFilename + 1);
	}

	static std::string getFoldernameFromPath(const std::string& path) {
		// find filename
		size_t startFilename = path.find_last_of("/");
		if (startFilename == std::string::npos) {
			startFilename = path.length();
		}
		return path.substr(0, startFilename);
	}

	static std::string appendFilenameToFolderPath(const std::string& path, const std::string& filename) {
		// find filename
		std::string res = path;
		unsigned int len = path.length();
		if (path[len - 1] != '/' && filename[0] != '/') {
			res.append("/");
		}
		return res.append(filename);
	}
};

}

 /* namespace photopay */
#endif /* IMAGEIO_H_ */
