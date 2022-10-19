#include "libbmp.h"
#include <iostream>

float mod(float x) { return x < 0 ? -x : x; }
float square(float x) { return x * x; }

int main() {

  int size = 5000;
  int maxSteps = size / 30;
  int center = size / 2;
  int color = 0, step;

  float x = 0, y = 0;              // Relative positions
  float x1 = -0.01, y1 = 0.69;     // X' and Y' for Julia
  float tempX = x;
  float tempY = y;

  BmpImg myImage(size, size);

  for (int X = 0; X < size; X++)
    for (int Y = 0; Y < size; Y++) {

      x = (center - X) / (size / 4.0);
      y = (center - Y) / (size / 4.0);

      // x1 = x; // Convert from Julia to Mandelbrot
      // y1 = y; // Un-comment these lines to render Mandelbrot

      step = 1;
      while (square(x) + square(y) <= 4 && step < maxSteps) {  // 500 steps
        
        color = 255 * (float)(((step) % maxSteps) / (float)maxSteps);

        tempX = x;
        tempY = y;

        x = square(tempX) - square(tempY) + x1;     // xn = x² - x² + x0
        y = (2 * tempX * tempY) + y1;               // xn = 2xy + y0

        step++;
      }
            myImage.set_pixel((int)X, (int)Y, color, color/4, color/4);
    
    }

  myImage.write("Output.png");

  return 0;
}
