#include "libbmp.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

inline bool file_exists(const std::string &name) {
  if (FILE *file = fopen(name.c_str(), "r")) {
    fclose(file);
    return true;
  }
  return false;
}

std::string takeNextFileName() {
  std::string nextFileName = "Output";
  bool loop = true;
  int num = 0;

  while (loop) {
    num++;
    loop = file_exists(nextFileName + std::to_string(num) + ".png");
  }

  return (nextFileName + std::to_string(num) + ".png");
}

float inline mod(float x) { return x < 0 ? -x : x; }
float inline square(float x) { return x * x; }

float getUserValue(std::string message, float defaultValue) {
  std::string buffer;
  std::stringstream number;
  number << defaultValue;

  std::cout << "\n\t" << message << " ( default: " << number.str() << " ): \t";
  std::getline(std::cin, buffer);

  return buffer.empty() ? defaultValue : stof(buffer);
}

void generateFractal(int size, float x, float y) {
  std::string nextFileName;
  const int iterations = size / 30; // Max iteraions.
  int color = 0, step;

  float x1 = y, y1 = y; // X' and Y' for Julia
  float tempX;
  float tempY;

  BmpImg myImage(size, size);

  for (int X = 0; X < size; X++)
    for (int Y = 0; Y < size; Y++) {

      x = ((size / 2.0) - X) / (size / 4.0);
      y = ((size / 2.0) - Y) / (size / 4.0);

      // x1 = x; // Convert from Julia to Mandelbrot
      // y1 = y; // Un-comment these lines to render Mandelbrot

      step = 1;
      while (square(x) + square(y) <= 4 && step < iterations) {

        color = 255 * ((step % iterations) / ((float)iterations));

        tempX = x;
        tempY = y;

        x = square(tempX) - square(tempY) + x1; // xn = x² - y² + x'
        y = (2 * tempX * tempY) + y1;           // xn = 2xy + y'

        step++;
      }
      myImage.set_pixel((int)X, (int)Y, color, color, color);
    }

  nextFileName = takeNextFileName();
  myImage.write(nextFileName);
}

int main() {

  int size;
  float x, y;

  std::cout << "\n\tTo generate your fractal, fill in the following data: \n";

  size = getUserValue("Image size", 2500);
  x = getUserValue("Your X' value [ -1 < X' < 1 ]", 0);
  y = getUserValue("Your Y' value [ -1 < Y' < 1 ]", 0);

  generateFractal(size, x, y);

  std::cout << "\n\tRendering complete.";

  return 0;
}
