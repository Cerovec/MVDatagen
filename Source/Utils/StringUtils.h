/**
 * \file
 *
 * StringUtils.h
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
#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_

#include <vector>
#include <string>
#include <sstream>

namespace mv {

/**
 * Split the string in chunks separated by delimiter
 */
inline static void split(const std::string& s, char delimiter, std::vector<std::string>& elems) {
	std::stringstream ss(s);
	std::string item;
	elems.clear();
	while(std::getline(ss, item, delimiter)) {
		elems.push_back(item);
	}
}

/**
 * Trim string from left
 */
inline static std::string &trimLeft(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

/**
 * Trim string from right
 */
inline static std::string &trimRight(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

/**
 * Trim from both ends
 */
inline static std::string &trim(std::string &s) {
	return trimLeft(trimRight(s));
}

}

#endif /* STRINGUTILS_H_ */
