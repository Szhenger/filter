# Filter

## Problem to Solve

There are many file formats that support images, such as BMP, JPEG, and PNG. Among these, bitmaps (BMP) are a simple and intuitive format for representing images as a grid of pixels. In black-and-white images, each pixel is typically represented by a binary value (0 for black, 1 for white). For color images, each pixel is represented by a three-tuple of bytes corresponding to the concentrations of red, green, and blue (RGB), using 24 bits per pixel. These RGB values are usually represented in hexadecimal format (e.g., `0x00` instead of binary `0b0`) for clarity.

Despite sharing similar concepts, the various image file formats differ in implementation, leading to diverse challenges in processing them. This project focuses specifically on applying image filters to BMP files, transforming and enhancing them by altering their pixels through various algorithms. 

## Background

This project implements basic image processing techniques and filters on BMP files. Images, when stored in the BMP format, consist of pixel grids where each pixel holds RGB values. Modifying these pixels in various ways can result in common transformations like:
* Grayscale: Converting the image to black and white, or shades of grey.
* Reflection: Flipping the image horizontally to mirror its content.
* Blur: Smoothing the image by averaging the pixel values with neighboring pixels.
* Edge Detection: Identifying the edges in the image using algorithms like Sobel.
This project is particularly focused on processing BMP files due to the simplicity of their structure and their ability to be manipulated directly on a pixel-by-pixel basis. The algorithms implemented provide a foundation for understanding how pixel-based image manipulation works across various file types.

## Understanding

The `filter` program allows users to apply various image transformation filters to BMP files. Below is a detailed explanation of how the program is structured and how each filter works at a technical level, providing insights into the logic behind each image processing algorithm.

#### Program Flow and Structure:
* Command-Line Interface:
    * The program is executed from the command line. Users provide the input BMP file and specify the filter they want to apply. The filter options are grayscale, reflection, blur, and edge detection.
    * The filter is chosen through a single character (g for grayscale, r for reflection, b for blur, e for edges), which is passed as an argument alongside the input file. The program identifies the selected filter and processes the image accordingly.
* Core Components:
    * The program is divided into two main parts:
        * helpers.c: This file contains the actual implementations of the image filters.
        * filter.c: This file acts as the main controller of the program. It handles user input, reads the image file, and applies the appropriate filter using functions defined in helpers.c.
    * Upon execution, the input BMP is loaded into memory, processed according to the specified filter, and then saved as an output BMP file with the filter applied.

#### How Each Filter Works:
* Grayscale:
    * The grayscale filter converts a color image to black and white (shades of grey). Each pixel’s RGB values are averaged to compute a single intensity value that represents the brightness of that pixel. This average value is then assigned back to the red, green, and blue channels, resulting in a grayscale image.
Implementation: The algorithm loops through each pixel in the image, calculates the average of its RGB values, and updates the pixel to reflect the computed grey value.
* Reflection:
    * This filter horizontally reflects the image, effectively flipping it like a mirror. For each row of pixels, the pixels on the leftmost side are swapped with the pixels on the rightmost side, progressively moving towards the center of the row.
Implementation: The algorithm iterates through each row of the image and performs an in-place swap of the pixels from the edges towards the center.
* Blur:
    * The blur filter smooths the image by averaging the color values of each pixel and its neighboring pixels within a sliding window (typically 3x3). This results in a softened image where details are less sharp, as the variation in color intensity is reduced.
    * Implementation: For each pixel, the algorithm calculates the average RGB values of the pixel and its surrounding neighbors. Since the surrounding pixels are taken into account, the algorithm must carefully handle edge cases at the borders of the image where fewer neighbors are available (e.g., pixels on the corners or edges).
* Edge Detection:
    * The edge detection filter highlights the edges in an image by identifying areas where there is a significant change in pixel intensity. This is done using the Sobel operator, which calculates the gradient of the pixel values in both the horizontal (x) and vertical (y) directions.
    * Implementation: The algorithm applies two convolution kernels (one for horizontal and one for vertical gradients) to each pixel, computing the resulting gradient magnitude. The combination of the gradients produces an output where higher gradient values correspond to edges in the image. As with the blur algorithm, careful handling of edge cases is required when processing pixels at the image borders.

#### Key Concepts in Image Processing:
* Pixel-by-Pixel Manipulation:
    * Each of the four filters operates by processing the image on a pixel-by-pixel basis. A BMP image is essentially a grid of pixels, where each pixel holds three values corresponding to the red, green, and blue color channels. By modifying these pixel values, we can achieve different visual effects like grayscale or edge detection.
* Handling Image Boundaries:
    * Filters such as blur and edge detection rely on neighboring pixels to compute the new pixel values. However, at the edges of an image (i.e., the pixels on the borders), some of these neighboring pixels don’t exist. The program accounts for this by either ignoring non-existent pixels or using only the available neighboring pixels for computation.
* Performance Considerations:
    * The program operates efficiently even for large images by processing each pixel individually. While filters like grayscale and reflection involve simple calculations (i.e., averaging values or swapping pixels), filters like blur and edge detection require more complex operations that involve iterating over neighboring pixels, which can slow down performance for larger images. However, this design allows for accurate and visually appealing results.
* Modularity and Extensibility:
    * The design of the program ensures that new filters can be added easily. The core image processing logic is isolated within `helpers.c`, while `filter.c` serves as the entry point that directs user input to the appropriate filtering function. This structure makes it easy to extend the program by adding new algorithms to `helpers.c` and updating the switch-case logic in `filter.c`.

## Specification

The `filter` program processes BMP images by applying one of four available image filters: grayscale, reflection, blur, or edge detection. It is executed through the command line, where users provide the input image and select a filter to apply. The program then outputs a new BMP image with the specified transformation.

#### Input:
* Command-line Arguments:
    * The program accepts two command-line arguments:
        * Input Image: A BMP file (.bmp) that the user wants to process.
        * Filter Type: A single character representing the filter to apply:
            * 'g' for grayscale
            * 'r' for reflection
            * 'b' for blur
            * 'e' for edge detection
         
#### Output:
* The output is a new BMP file with the applied filter, saved in the same directory as the input file.
* The output file retains the BMP format and pixel dimensions of the input file, with its visual content modified according to the selected filter.

#### File Structure:
* `helpers.c`: Implements the core logic for each image filter.
    * Grayscale
    * Reflection
    * Blur
    * Edge Detection
* Each function modifies the pixel values of the input BMP according to the specified filter.
* `filter.c`: Acts as the main entry point for the program.
    * Processes command-line arguments, reads the input BMP file, and applies the specified filter.
    * Uses a switch statement to direct control flow to the appropriate filter function from helpers.c.
* Makefile:
    * The Makefile provides instructions to compile the program.
    * Run make filter to compile the filter.c and helpers.c files into an executable named filter.
