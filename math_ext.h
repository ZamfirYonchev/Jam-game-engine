/*
 * math_ext.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef MATH_EXT_H_
#define MATH_EXT_H_

template <typename T>
int sign(T val)
{
    return (T(0) < val) - (val < T(0));
}

template <typename T>
T abs(T val)
{
    return T(val * sign(val));
}

template <typename T>
T max(T val0, T val1)
{
    return T((val0+val1)/2.0 + abs(val0-val1)/2.0);
}

template <typename T>
T min(T val0, T val1)
{
    return T((val0+val1)/2.0 - abs(val0-val1)/2.0);
}

template <typename T>
T clip(T val0, T val1, T val2)
{
    T min_val = min(val1, val2);
    T max_val = min_val + abs(val1-val2);
    return min(max(val0, min_val), max_val);
}

double lines_cross(double x0, double y0, double w0, double h0, double x1, double y1, double w1, double h1);

bool objects_collide(double x0, double y0, double w0, double h0, double x1, double y1, double w1, double h1);

#endif /* MATH_EXT_H_ */
