# Fractal Generator in C++

## Image outputs

With this program, you can generate images like this one:

![fractal (1)](https://user-images.githubusercontent.com/103672525/196289510-8a7fbc12-0581-4069-90d1-80b1155c5a06.png)

The image above is 1.000 x 1.000 pixels and is a render of three hundred iterations of the Mandelbrot formulas.

It is interesting to notice, however, that for any images below the 10.000 x 10.000 resolution threshold, more than 100 iterations are not really necessary.

## Install

To install, run the following program via Git:

```
git clone https://github.com/OctavioFurio/Fractal_Generator_in_C-.git
```

That's it! To compile and run, simply call g++ or your compiler of choice using the three files. 
For example, in g++ the command is as follows:

```
g++ libbmp.h libbmp.cpp fractal.cpp -o example_program
```

To render the fractals, run the executable you've just created in the directory of your choice. The resulting images will be saved in the same directory.

After compilation, you can save the executable, by itself, anywhere in your file system, and the generated images will be saved in the same directory.


## The math behind it

Though fractals are *usually* represented in the complex plane, it is possible *- though not as elegant -* to calculate them with real numbers, and the process follows the same logic:

> Pick a point (x, y) and call its coordinates x0 and y0.
> Apply the following equations:
> 
>> f(x) = x² - y² + x0
>> 
>> g(y) = 2xy + y0
> 
> Then, for every new iteration, apply f to itself and g to itself, as such:
> 
>> f(f(f(...(f(x))...)))
>>
>> g(g(g(...(g(y))...)))
> 
> If, after any given iteration, the values of X or Y leave the area defined by the circle x0² + y0² = 4, that point does not belong to the set, and then is drawn as the color representing the last iteration in which it was present in such area.

The Julia sets are easy to achieve from there - simply change x0 and y0 to a number x' and y' of your liking, such that (-1 < x' < 1) and (-1 < y' < 1).

The example program given (fractal.cpp) has an implementation that easily allows you to choose which you want to generate.

## Fonts and References

This program is based around LIBBMP, which can be found [here](https://github.com/marc-q/libbmp).

This program was inspired by an incredible visualization of Mandelbrot made in Desmos, that can be found [here](https://www.desmos.com/calculator/tvu1jflxc5)

To better understand the Mandelbrot set, I strongly recommend this [website](https://courses.lumenlearning.com/mathforliberalartscorequisite/chapter/generating-fractals-with-complex-numbers/)

This [website](http://xahlee.info/cmaci/fractal/mandelbrot.html) was also a nice and informative read.
