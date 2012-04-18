# MVDatagen
The tool aims to facilitate generation of image based datasets for machine vision projects.

The project solves two problems:

- marking of existing images

- generating new marked images via transformations like perspective transformations, adding blur, noise etc. This can enlarge your dataset and make your learning algorithms more accurate and robust.

## Compilation

The project uses OpenCV for image IO and geometry transformations.

Project can be compiled using:
    
    g++ -lopencv_core -lopencv_highgui -lopencv_imgproc -I. Main.cpp Dataset.cpp Utils/IO.cpp Marker/Marker.cpp Generator/Generator.cpp Generator/NoiseGenerator.cpp Generator/CopyGenerator.cpp Generator/FlipGenerator.cpp Generator/PerspectiveGenerator.cpp Generator/BlurGenerator.cpp -o ./MVDatagen

## Usage

Once compiled the tool can be used in the following way

	./MVDatagen -e <existing_dataset_folder> -g <generated_dataset_folder> <additional_options>
	
For the first use, locate the folder with your images and decide where you want your generated images to be placed.
Then use: 

    ./MVDatagen -e <existingImagesFolder> -g <generatedImagesFolder>
This will place the generated images in `<generatedImagesFolder>`, and also create two files:
`<existingImagesFolder>/dataset.txt` and `<generatedImagesFolder>/dataset.txt`. These contain dataset information.

If MVDatagen finds the existing file `<existingImages>/dataset.txt`, the marking process will be skipped, and you will see the appropriate message. That file will then serve as the basis for generation process.

Additional options are:
	
    -n(value) (e.g. -n10) - creates 10 noised images for each original image. Default is 5. Must be greater than 0.
    -v(value) (e.g. -v6) - variance of noise. Default is 10.
    -p(value) (e.g. -p8) - creates 8 perspective transformed images for each original image. Default is 10.
    -s(value) (e.g. -s5) - variance of perspective. Default is 10.
    -b(value) (e.g. -b6) - creates 6 blurred images for each original image. Default is 5.
    -r(value) (e.g. -r3) - radius of blur. Default is 3.
    -f(value) (e.g. -f1) - Generate flipped image. Default is 1 (true).