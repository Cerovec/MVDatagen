/**
 * \file
 *
 * DatagenMain.cpp
 *
 *  Created on: Apr 4, 2012
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

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "Marker.h"
#include "NoiseGenerator.h"

static struct option options[] = {
    {"existing_dataset_folder", 	required_argument, 	0, 'e'},
    {"generated_dataset_folder", 	required_argument, 	0, 'g'},
    {"noise-num", 					required_argument, 	0, 'n'},
    {"noise-variance",				required_argument, 	0, 'v'},
    {"perspective-num", 			required_argument, 	0, 'p'},
    {"perspective-variance",		required_argument, 	0, 's'},
    {"blur-num", 					required_argument, 	0, 'b'},
    {"blur-radius", 				required_argument, 	0, 'r'},
    {0, 							0, 					0, 	0}
};

static void help() {
	printf(
		"\n"
		"Use the command as follows:\n"
		"./MVDatagen -d <existing_dataset_folder> -g <generated_dataset_folder>\n"
		"\n"
		"For the first use, locate the folder with your images and decide where you want your generated images to be placed.\n"
		"Then use: ./MVDatagen -d <existingImagesFolder> -g <generatedImagesFolder>\n"
		"This will place the generated images in <generatedImagesFolder>, and also create two files "
		"<existingImagesFolder>/dataset.txt and <generatedImagesFolder>/dataset.txt. These contain descriptions of the datasets.\n"
		"The file it will serve as the basis for generation of test samples.\n"
		"\n"
		"If MVDatagen finds the existing file <existingImages>/dataset.txt, the marking process will be skipped, and you will see the appropriate message. "
		"<existingImages>/dataset.txt will then serve as the basis for generation process. "
		"Also, if the <generated_dataset_folder>/dataset.txt does exist, the generating process will be skipped and you will see the appropriate message."
		);
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
	char* existingDatasetFilename = NULL;
	char* generatedDatasetFilename = NULL;

	int noiseNum = 0;
	double noiseVariance = 0;

	int blurNum = 0;
	double blurVariance = 0;

	int perspectiveNum = 0;
	int perspectiveVariance = 0;

	int optionIndex = 0;
	char argument;

	while ((argument = getopt_long(argc, argv, "e:g:", options, &optionIndex)) > -1) {
		switch (argument) {
			case 'e':
				existingDatasetFilename = optarg;
				break;
			case 'g':
				generatedDatasetFilename = optarg;
				break;
			default:
				help();
				break;
		}
	}

	if (existingDatasetFilename == NULL ||  generatedDatasetFilename == NULL) {
		help();
	}

	/**
	 * Mark the original images, if needed
	 */
	mv::Marker marker(existingDatasetFilename);
	marker.markDataset();

	/**
	 * Create generator chain
	 */
	mv::NoiseGenerator noiseGenerator(existingDatasetFilename, generatedDatasetFilename, noiseNum, noiseVariance);
	mv::NoiseGenerator blurGenerator(existingDatasetFilename, generatedDatasetFilename, blurNum, blurVariance);
	mv::NoiseGenerator perspectiveGenerator(existingDatasetFilename, generatedDatasetFilename, perspectiveNum, perspectiveVariance);

	noiseGenerator.setNext(&blurGenerator);
	blurGenerator.setNext(&perspectiveGenerator);

	/**
	 * Generate dataset
	 */
	noiseGenerator.generateDataset();

	return EXIT_SUCCESS;
}


