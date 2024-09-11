# Filter

#### Problem to Solve

There are many file formats that support images; however, a simple and intuitive encoding are bitmaps such that images represented as a grid of pixels of binary value 0 or 1 to denote black and white respectively. For additional color, we can associate with each pixel instead of a bit, but a three-tuple of bytes that represent concentrations of red, green, or blue (RGB), i.e. 24 bits per pixel. For the sake of clarity, we present the RGB values in hexadecimal opposed to binary i.e. 0x00 vs 0b0. Please observe that many file formats such as BMP, JPEG, and PNG have similar interfaces or specifications for what the file contain; however, the implementation is different amoung these file formats. This repository stores files that apply image filters to BMPs.    

#### Description

Functionally, the set of files applies filter algorithms to input BMPs to produced output BMPs; however, the implementations are designed to be clear for the sake of correctness and style. In particular, the algorithms take each input file and modify each pixel in the bitmaps according to the interface of each algorithm. The repository has 4 filter algorithms that support grayscale, reflection, blur, and edge detection operations. For the greyscale algorithm, the specification is converting each pixel to a black-or-white encoding by averaging the RGB values for each pixel and map each pixel to a shade of grey that matches the value of the average. For the relection algorithm, apply a reverse procedure on each row of the bitmap to achieve the desired result of reflection. For the blur algorithm, it is worth noting that we need to apply a sliding window technique of a box around each input pixel by averaging each pixel in the surrounding area for the new value of the pixel. For the edge detection, applying the Sobel algorithm for weighted sums finds the edges in any box of pixels.      

#### Specification

In helpers.c, we have filter algorithms such that grayscale takes an image and returns the image such that it is a black-and-white version of that same image, reflect takes an image and reflects it horizontally, blur takes an image and box-blur the image, and edges should highlight the edges between objects.

In filter.c, there is a main procedure that takes input images and characters at the commend-line to initate what filter algorithm should be applied and the resulting image shall apply the algorithm via the switch subroutine. 

In the Makefile, run make filter to compile the files to obtain the command ./filter input.bmp filter_char that runs the program to apply filters.

