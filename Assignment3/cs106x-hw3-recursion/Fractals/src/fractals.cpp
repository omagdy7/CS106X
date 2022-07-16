/*
 * File: fractals.cpp
 * --------------------------
 * Name:
 * Section leader:
 * This file contains fractal problems for CS106X.
 */


#include "fractals.h"
#include <cmath>
#include "gbufferedimage.h"
#include "plasmacolor.h"
#include "complex.h"

using namespace std;

/**
 * Draws a Sierpinski triangle of the specified size and order, placing its
 * bottom-left corner at position (x, y).
 *
 * This will be called by fractalgui.cpp.
 *
 * @param window - The window in which to draw the Sierpinski triangle.
 * @param x - The x coordinate of the bottom-left corner of the triangle.
 * @param y - The y coordinate of the bottom-left corner of the triangle.
 * @param sideLength - The length of one side of the triangle.
 * @param order - The order of the fractal.
 */
void drawSierpinskiTriangle(GWindow& window, double x, double y, double sideLength, int order) {
    // TODO: remove the lines below and write this function
    if(order > 1) {
        GPoint leftP(x, y);
        GPoint rightP(x + sideLength, y);
//        double height = sqrt(pow((leftP.getX() + rightP.getX()) / 2, 2) - (sideLength * sideLength));
        GPoint middleUp((leftP.getX() + rightP.getX()) / 2, y - sideLength);
        window.drawLine(leftP.getX(), leftP.getY(), rightP.getX(), rightP.getY());
        window.drawLine(leftP.getX(), leftP.getY(), middleUp.getX(), middleUp.getY());
        window.drawLine(rightP.getX(), rightP.getY(), middleUp.getX(), middleUp.getY());
        drawSierpinskiTriangle(window, x, y, sideLength / 2, order - 1);
        drawSierpinskiTriangle(window, x + sideLength / 2, y, sideLength / 2, order - 1);
        drawSierpinskiTriangle(window, x + sideLength / 4, y - sideLength / 2, sideLength / 2, order - 1);
    }
}

/**
 * Draws a recursive tree fractal image of the specified size and order,
 * placing the bounding box's top-left corner at position (x,y).
 *
 * This will be called by fractalgui.cpp.
 *
 * @param window - The window in which to draw the recursive tree.
 * @param x - The x coordinate of the top-left corner of the bounding box.
 * @param y - The y coordinate of the top-left corner of the bounding box.
 * @param size - The length of one side of the bounding box.
 * @param order - The order of the fractal.
 */

void drawTreeHelper(GWindow& window, double x, double y, double size, int order, int degree) {
    // TODO: remove the lines below and write this function
    GPoint p1(x, y);
    if(order >= 1) {
        window.setColor("#8b7765");
        if(order == 1) {
            window.setColor("#2e8b57");
        }
        GPoint p2 = window.drawPolarLine(p1, size, 90);
        GPoint p3 = window.drawPolarLine(p1, size , degree + 90);
        GPoint p4 = window.drawPolarLine(p1, size , degree + 45);
        GPoint p5 = window.drawPolarLine(p1, size , degree + 180 - 45);
        GPoint p6 = window.drawPolarLine(p1, size , degree + 60);
        GPoint p7 = window.drawPolarLine(p1, size , degree + 75);
        GPoint p8 = window.drawPolarLine(p1, size , degree + 120);
        GPoint p9 = window.drawPolarLine(p1, size , degree + 180 - 75);
        drawTreeHelper(window, p3.getX(), p3.getY() , size / 2, order - 1, degree + 0);
        drawTreeHelper(window, p4.getX(), p4.getY() , size / 2, order - 1, degree + -45);
        drawTreeHelper(window, p5.getX(), p5.getY() , size / 2, order - 1, degree + 45);
        drawTreeHelper(window, p6.getX(), p6.getY() , size / 2, order - 1, degree + -30);
        drawTreeHelper(window, p7.getX(), p7.getY() , size / 2, order - 1, degree + -15);
        drawTreeHelper(window, p8.getX(), p8.getY() , size / 2, order - 1, degree + 30);
        drawTreeHelper(window, p9.getX(), p9.getY() , size / 2, order - 1, degree + 15);
    }
}



void drawTree(GWindow& window, double x, double y, double size, int order) {
    int degree = 0;
    GPoint p1(x, y);
    GPoint p2 = window.drawPolarLine(p1, size, 90);
    drawTreeHelper(window, p2.getX(), p2.getY(), size, order, degree);
}

/**
 * Draws a Mandelbrot Set in the graphical window at the specified location/size,
 * with maxIterations and in a given color.
 *
 * This will be called by fractalgui.cpp.
 *
 * @param window - The window in which to draw the Mandelbrot set.
 * @param leftX - The x coordinate of the top-left corner of the bounding box.
 * @param topY - The y coordinate of the top-left corner of the bounding box.
 * @param min - the minimum Complex number you should examine
 * @param max - the maximum Complex number you should examine
 * @param iterations - The maximum number of iterations to run recursive step
 * @param color - The color of the fractal
 */

double mapRange(int x, int v1, int size, double min, double max) {
    int diff = x - v1;
    return min + diff * (max - min) / size;
}




void drawMandelbrotSet(GWindow& window, double leftX, double topY, double size,
                       const Complex& min, const Complex& max,
                       int iterations, int color) {
    GBufferedImage image(size, size, 0xffffff);
    window.add(&image, leftX, topY);
    Grid<int> pixels = image.toGrid(); // Convert image to grid
    int realMin = min.real();
    int realMax = max.real();
    int imagMin = min.imag();
    int imagMax = max.imag();
    for(int i = 0; i < pixels.numRows(); i++) {
        for(int j = 0; j < pixels.numCols(); j++) {
            double r = mapRange(topY + i, topY, size, imagMin, imagMax);
            double c = mapRange(leftX + j, leftX, size, realMin, realMax);
            double ca = r;
            double cb = c;
            int n = 0;
            bool ok = false;
            Complex comp(r, c);
            while (n < iterations) {
                double aa = comp.real() * comp.real() - (comp.imag() * comp.imag());
                double bb = 2 * comp.real() * comp.imag();
                r = aa + ca;
                c = bb + cb;
//                cerr << n << ": " << endl;
//                cerr << r << " " << c << endl;
                if(abs(r + c) > 1) {
                    break;
                }
                n++;
            }
            if(n == iterations) {
                pixels[i][j] = color;
            }
        }
    }

    image.fromGrid(pixels); // Converts and puts the grid back into the image onscreen
}

/**
 * Generates a random displacement value you can add to a color to randomly shift it.
 *
 * You should call this function when calculating middle color values.
 *
 * @param newWidth - the width of the subdivided rectangles you are creating at that moment
 * @param newHeight - the height of the subdivided rectangles you are creating at that moment
 * @param totalWidth - the width of the entire plasma fractal (not just the part you are filling in at the moment)
 * @param totalHeight - the height of the entire plasma fractal (not just the part you are filling in at the moment)
 */
double displace(double newWidth, double newHeight, double totalWidth, double totalHeight) {
    double max = 3*(newWidth + newHeight) / (totalWidth + totalHeight);
    return (randomReal(0, 1) - 0.5) * max;
}

/**
 * Draws a Plasma Fractal in the graphical window at the specified location/size.
 *
 * This will be called by fractalgui.cpp.
 *
 * @param window - The window in which to draw the fractal.
 * @param x - The x coordinate of the top-left corner of the bounding box.
 * @param y - The y coordinate of the top-left corner of the bounding box.
 * @param size - The length of one side of the bounding box.
 */
void drawPlasma(GWindow &window, double x, double y, double size) {
    GBufferedImage image(size, size, 0xffffff);
    window.add(&image, x, y);
    Grid<int> pixels = image.toGrid(); // Convert image to grid
    for(int i = 0; i < pixels.numRows(); i++) {
        for(int j = 0; j < pixels.numCols(); j++) {

        }
    }
    image.fromGrid(pixels); // Converts and puts the grid back into the image onscreen
}
