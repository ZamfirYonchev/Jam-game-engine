/*
 * math_ext.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef MATH_EXT_H_
#define MATH_EXT_H_

#include <cmath>

template <typename T>
constexpr int sign(T val)
{
    return (T(0) < val) - (val < T(0));
}

template <typename T>
constexpr T abs(T val)
{
    return T(val * sign(val));
}

template <typename T>
constexpr T max(T val0, T val1)
{
    return T((val0+val1)/2.0 + abs(val0-val1)/2.0);
}

template <typename T>
constexpr T min(T val0, T val1)
{
    return T((val0+val1)/2.0 - abs(val0-val1)/2.0);
}

template <typename T>
constexpr T clip(T val0, T val1, T val2)
{
    T min_val = min(val1, val2);
    T max_val = min_val + abs(val1-val2);
    return min(max(val0, min_val), max_val);
}

constexpr double lines_cross(double x0, double y0, double w0, double h0, double x1, double y1, double w1, double h1)
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

constexpr bool objects_collide(double x0, double y0, double w0, double h0, double x1, double y1, double w1, double h1)
{
    double x3 = x1 + w1;
    double y3 = y1 + h1;
    double sx = x0 + w0 + w1;
    double sy = y0 + h0 + h1;

    return x3 > x0 && x3 < sx && y3 > y0 && y3 < sy;
}

constexpr bool is_integer(double val)
{
	return int(val) == val;
}

constexpr bool is_negative_zero(double val)
{
	return val == 0 && std::signbit(val);
}

constexpr bool is_normalized(double val)
{
	return (val >= -1.0) && (val <= 1.0);
}

#endif /* MATH_EXT_H_ */
