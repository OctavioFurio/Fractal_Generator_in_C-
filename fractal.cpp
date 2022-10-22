#include "libbmp.h"
#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>

inline bool file_exists (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    }

    return false;
}

std::string takeNextFileName () {
  std::string nextFileName = "Images/Output";
  bool loop = true;
  int num = 0;

  while(loop){
    num ++;
    loop = file_exists(nextFileName + std::to_string(num) + ".png");
  }

  return (nextFileName + std::to_string(num) + ".png");

}

void generateFractal(int size, float x, float y);
float getUserValue(std::string message, float defaultValue);

float inline mod(float x) { return x < 0 ? -x : x; }
float inline square(float x) { return x * x; }

int main() {

  int size;       // Size of image
  float x, y;     // Relative positions
  
  std::cout << "Image size (5000): ";

  size = getUserValue("Image size", 5000);
  x = getUserValue("x value", 0);
  y = getUserValue("y value", 0);

  generateFractal(size, x, y);

  return 0;
}

float getUserValue(std::string message, float defaultValue) {
  std::string buffer;
  std::stringstream number;
  number << defaultValue;

  std::cout << message << " (" << number.str() << "): ";
  std::getline(std::cin, buffer);

  if (buffer.empty()) {
    return defaultValue;
  } 
  
  return stof(buffer);
}

void generateFractal(int size, float x, float y) {
  std::string nextFileName;
  const int iterations = size / 30;      // Max iteraions.
  int color = 0, step;

  float x1 = -0.01, y1 = 0.69; // X' and Y' for Julia
  float tempX = x;
  float tempY = y;

  BmpImg myImage(size, size);

  for (int X = 0; X < size; X++)
    for (int Y = 0; Y < size; Y++) {

      x = ((size / 2.0) - X) / (size / 4.0);
      y = ((size / 2.0) - Y) / (size / 4.0);

      // x1 = x; // Convert from Julia to Mandelbrot
      // y1 = y; // Un-comment these lines to render Mandelbrot

      step = 1;
      while (square(x) + square(y) <= 4 && step < iterations) {

        color = 255 * (step % iterations) / (float)iterations;

        tempX = x;
        tempY = y;

        x = square(tempX) - square(tempY) + x1; // xn = x² - y² + x'
        y = (2 * tempX * tempY) + y1;           // xn = 2xy + y'

        step++;
      }
      myImage.set_pixel((int)X, (int)Y, color, color / 4, color / 4);
    }

  nextFileName = takeNextFileName();
  myImage.write(nextFileName);

}
