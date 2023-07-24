# CG-Lab1-FillingAnyPolygon

![image](https://github.com/TheKiesling/CG-Lab-FillingAnyPolygon/assets/84196494/b9caf441-8786-4bc6-a103-b3147315352d)

## Description

This is the Lab1 for the Computer Graphics course. In this lab, we have developed a C++ program to generate BMP images using the Bresenham's line algorithm to draw polygons and fill them with colors.

## Files

The project consists of the following files:

- `Color.h`: Defines the `Color` struct that represents an RGB color and provides mathematical operations for color blending and modification.

- `Vertex2.h`: Defines the `Vertex2` struct that represents a vertex with (x, y) coordinates.

- `Framebuffer.h`: Defines the `Framebuffer` struct that represents a framebuffer where objects are drawn. It contains functions to draw lines and polygons.

- `Bitmap.h`: Defines the `Bitmap` struct that represents a BMP image. It uses the framebuffer to render objects and saves the generated image to a file.

- `main.cpp`: The main file that contains the `main()` function to run the program.

## Technologies

The project has been developed using the following technologies:

- C++: For implementing the logic and drawing algorithms.

- CMake: For generating the build and compilation system.

- MinGW: The GNU toolset for Windows, including the C++ compiler and the Make build system.

## How to Run the Program

Follow these steps to compile and run the program:

1. Make sure you have MinGW and CMake installed on your system.

2. Open a terminal or command prompt in the project's root directory.

3. Run the following command to execute the project:
```
run.bat
```
Note: The generated image, `out.bmp`, will be saved in the build directory. 

Enjoy exploring the creative results of the program!

## Have Fun with Graphics Generation!

---

