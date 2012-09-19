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
#include "Dataset.h"
#include "Marker/Marker.h"
#include "Utils/IO.h"
#include "Generator/NoiseGenerator.h"
#include "Generator/BlurGenerator.h"
#include "Generator/PerspectiveGenerator.h"
#include "Generator/CopyGenerator.h"
#include "Generator/FlipGenerator.h"

static struct option options[] = {
    {"existing_dataset_folder", required_argument, 0, 'e'},
    {"generated_dataset_folder", required_argument, 0, 'g'},
    {"noise-num", required_argument, 0, 'n'},
    {"noise-variance", required_argument, 0, 'v'},
    {"perspective-num", required_argument, 0, 'p'},
    {"perspective-variance", required_argument, 0, 's'},
    {"blur-num", required_argument, 0, 'b'},
    {"blur-radius", required_argument, 0, 'r'},
    {"flip", required_argument, 0, 'f'},
    {"show-only", no_argument, 0, 'o'},
    {0, 0,  0, 0}
};

static void help() {
	printf(
		"\n"
		"Use the command as follows:\n"
		"./MVDatagen -e <existing_dataset_folder> [-g <generated_dataset_folder>]\n"
		" If -g option is ommited, only marking process will be performed.\n"
		" Adding -o option will just show images that are in dataset and their marks. No updates will be performed."
		"\n"
		"For the first use, locate the folder with your images and decide where you want your generated images to be placed.\n"
		"Then use: ./MVDatagen -e <existingImagesFolder> -g <generatedImagesFolder>\n"
		"This will place the generated images in <generatedImagesFolder>, and also create two files "
		"<existingImagesFolder>/dataset.txt and <generatedImagesFolder>/dataset.txt. These contain descriptions of the datasets.\n"
		"The file it will serve as the basis for generation of test samples.\n"
		"\n"
		"If MVDatagen finds the existing file <existingImages>/dataset.txt, the marking process will "
		"be skipped if there are no new images in <existingImages> folder, and you will see the appropriate message. "
		"<existingImages>/dataset.txt will then serve as the basis for generation process. "
		"Also, if the <generated_dataset_folder>/dataset.txt does exist, the "
		"generating process will be skipped and you will see the appropriate message.\n"
		"\n"
		"Additional options are:\n"
		"\t-n(value) (e.g. -n10) creates 10 noised images for each original image. Default is 5. Must be greater than 0.\n"
		"\t-v(value) (e.g. -v6) variance of noise. Default is 10.\n"
		"\t-p(value) (e.g. -p8) creates 8 perspective transformed images for each original image. Default is 10.\n"
		"\t-s(value) (e.g. -s5) variance of perspective. Default is 10.\n"
		"\t-b(value) (e.g. -b6) creates 6 blurred images for each original image. Default is 5.\n"
		"\t-r(value) (e.g. -r3) radius of blur. Default is 3.\n"
		"\t-f(value) (e.g. -f1) Generate flipped image. Default is 1 (true).\n"
		);
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
	char* existingDatasetFolder = NULL;
	char* generatedDatasetFolder = NULL;

	int noiseNum = 3;
	int noiseVariance = 10;

	int blurNum = 3;
	int blurRadius = 3;

	int perspectiveNum = 3;
	int perspectiveVariance = 5;

	int optionIndex = 0;
	char argument;

	bool flipNum = 1;
	bool showOnly = false;

	while ((argument = getopt_long(
			argc, argv, "e:g:n:v:p:s:b:r:f:o:", options, &optionIndex)) > -1) {
		switch (argument) {
			case 'e':
				existingDatasetFolder = optarg;
				break;
			case 'g':
				generatedDatasetFolder = optarg;
				break;
			case 'n':
				noiseNum = atoi(optarg);
				break;
			case 'v':
				noiseVariance = atoi(optarg);
				break;
			case 'p':
				perspectiveNum = atoi(optarg);
				break;
			case 's':
				perspectiveVariance = atoi(optarg);
				break;
			case 'b':
				blurNum = atoi(optarg);
				break;
			case 'r':
				blurRadius = atoi(optarg);
				break;
			case 'f':
				flipNum = atoi(optarg);
				break;
			case 'o':
				showOnly = true;
				break;
			default:
				help();
				break;
		}
	}

	/** check if folder names are present */
	if (existingDatasetFolder == NULL) {
		help();
	}

	/** trim folder names */
	size_t startingLength = strlen(existingDatasetFolder);
	if (existingDatasetFolder[startingLength - 1] == '/') {
		existingDatasetFolder[startingLength - 1] = 0;
	}
	size_t generatedLength = 0;
	if(generatedDatasetFolder!=NULL) {
		generatedLength = strlen(generatedDatasetFolder);
		if (generatedDatasetFolder[generatedLength - 1] == '/') {
			generatedDatasetFolder[generatedLength - 1] = 0;
		}
	}
	/** Mark the original images if dataset doesn't exist */
	mv::Marker marker(existingDatasetFolder);
	if(!showOnly) {
		if (!marker.datasetExists()) {
			printf("Marking dataset for \"%s\"...\n", existingDatasetFolder);
			marker.markDataset();
		} else {
			printf("Dataset for images at \"%s\" already exists.\n"
					"Updating dataset for new images...\n", existingDatasetFolder);
			marker.updateDataset();
		}

		if(generatedDatasetFolder!=NULL) {
			/** Remove existing dataset in generated dataset folder */
			std::string genDatasetFilename = mv::IO::appendFilenameToFolderPath(
					generatedDatasetFolder, mv::Marker::DATASET_FILENAME_EXTENSION);
			remove(genDatasetFilename.c_str());

			/** Create generator chain */
			mv::CopyGenerator copyGenerator(
					existingDatasetFolder, generatedDatasetFolder);
			mv::FlipGenerator flipGenerator(
					generatedDatasetFolder, generatedDatasetFolder, flipNum);
			mv::PerspectiveGenerator perspectiveGenerator(
					generatedDatasetFolder, generatedDatasetFolder, perspectiveNum, perspectiveVariance);
			mv::BlurGenerator blurGenerator(
					generatedDatasetFolder, generatedDatasetFolder, blurNum, blurRadius);
			mv::NoiseGenerator noiseGenerator(
					generatedDatasetFolder, generatedDatasetFolder, noiseNum, noiseVariance);

			copyGenerator.setNext(&flipGenerator);
			flipGenerator.setNext(&perspectiveGenerator);
			perspectiveGenerator.setNext(&blurGenerator);
			blurGenerator.setNext(&noiseGenerator);

			/** Generate dataset */
			copyGenerator.generateDataset();
		}
	} else {
		if(marker.datasetExists()) {
			printf("Showing contents of existing dataset...\n");
			marker.showDataset();
		} else {
			printf("Given dataset does not exist! There is nothing to show!");
		}
	}

	return EXIT_SUCCESS;
}
