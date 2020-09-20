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
constexpr int sign(const T val)
{
	if constexpr(std::is_integral<T>::value)
	    return std::signbit(val);
	else
		return (T(0) < val) - (val < T(0));
}

template <typename T>
constexpr T abs(const T val)
{
    return T(val * sign(val));
}

template <typename T>
constexpr T max(const T val0, const T val1)
{
	if constexpr(std::is_integral<T>::value)
		return std::max(val0, val1);
	else
		return T(val0 * (val0 >= val1) + val1 * (val0 < val1));
}

template <typename T>
constexpr T min(const T val0, const T val1)
{
	if constexpr(std::is_integral<T>::value)
		return std::min(val0, val1);
	else
		return T(val1 * (val0 >= val1) + val0 * (val0 < val1));
}

template <typename T>
constexpr T clip(const T val0, const T val1, const T val2)
{
    T min_val = min(val1, val2);
    T max_val = min_val + abs(val1-val2);
    return min(max(val0, min_val), max_val);
}

constexpr double lines_cross(const double x0, const double y0, const double w0, const double h0, const double x1, const double y1, const double w1, const double h1)
{
	const double d = (w1*h0 - h1*w0);

    if(d == 0) return -1;

    const double t1 = ((x0-x1)*h0 - (y0-y1)*w0) / d;
    const double t0 = ((x0-x1)*h1 - (y0-y1)*w1) / d;

    if(t1 >= 0 && t1 <= 1.0)
        return t0;
    else
        return -1;
}

constexpr bool objects_collide(const double x0, const double y0, const double w0, const double h0, const double x1, const double y1, const double w1, const double h1)
{
	const double x3 = x1 + w1;
	const double y3 = y1 + h1;
	const double sx = x0 + w0 + w1;
	const double sy = y0 + h0 + h1;

    return x3 > x0 && x3 < sx && y3 > y0 && y3 < sy;
}

constexpr bool is_integer(const double val)
{
	return int(val) == val;
}

constexpr bool is_negative_zero(const double val)
{
	return val == 0 && std::signbit(val);
}

constexpr bool is_normalized(const double val)
{
	return (val >= -1.0) && (val <= 1.0);
}

#endif /* MATH_EXT_H_ */
