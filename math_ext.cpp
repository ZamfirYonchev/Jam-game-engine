/*
 * math_ext.cpp
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#include "math_ext.h"

double lines_cross(double x0, double y0, double w0, double h0, double x1, double y1, double w1, double h1)
{
    double d = (w1*h0 - h1*w0);

    if(d == 0) return -1;

    double t1 = ((x0-x1)*h0 - (y0-y1)*w0) / d;
    double t0 = ((x0-x1)*h1 - (y0-y1)*w1) / d;

    if(t0 >= 0 && t1 >= 0 && t1 <= 1.0)
        return t0;
    else
        return -1;
}

bool objects_collide(double x0, double y0, double w0, double h0, double x1, double y1, double w1, double h1)
{
    double x3 = x1 + w1;
    double y3 = y1 + h1;
    double sx = x0 + w0 + w1;
    double sy = y0 + h0 + h1;

    return x3 > x0 && x3 < sx && y3 > y0 && y3 < sy;
}




