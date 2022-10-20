#include "libbmp.h"
#include <iostream>

float inline mod(float x) { return x < 0 ? -x : x; }
float inline square(float x) { return x * x; }

int main() {

  const int size = 5000;            // Size of image - change as you will
  const int iterations = size / 30; // Max iteraions.
  int color = 0, step;

  float x = 0, y = 0;          // Relative positions
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

  myImage.write("Output.png");

  return 0;
}
