#include "libbmp.h"
#include <iostream>

float mod(float x) { return x < 0 ? -x : x; }
float square(float x) { return x * x; }

int main() {

  int size = 5000;
  int center = size / 2;
  int color = 0, step = 0;

  float x = 0, y = 0;       // Relative positions
  float x1 = 0, y1 = 0;     // X' and Y' for Julia

  BmpImg myImage(size, size);

  for (int X = 0; X < size; X++)
    for (int Y = 0; Y < size; Y++) {

      x = (center - X) / (size / 4.0);
      y = (center - Y) / (size / 4.0);

      x1 = x; // Convert from Julia to Mandelbrot
      y1 = y; // Comment these lines to render Julia

      if(square(x) + square(y) > 4)
        myImage.set_pixel((int)X, (int)Y, color, color, color); // Background color

      step = 0;
      while (square(x) + square(y) <= 4 && step < 500) {  // 500 steps

        step++;
        color = 255 * (float)(((step) % 128) / 128.0);

        float tempX = x;
        float tempY = y;

        myImage.set_pixel((int)X, (int)Y, color, color, color);

        x = square(tempX) - square(tempY) + x1;     // xn = x² - x² + x0
        y = (2 * tempX * tempY) + y1;               // xn = 2xy + y0

      }
    }

  myImage.write("Output.png");

  return 0;
}