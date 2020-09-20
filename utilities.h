/*
 * utilities.h
 *
 *  Created on: May 24, 2020
 *      Author: zamfi
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include "globals.h"
#include "math_ext.h"

constexpr double absolute_or_scaled(double val, double scale)
{
	return val*(is_normalized(val)*(scale-1)+1);
}

constexpr unsigned long hash(const char* str)
{
    unsigned long hash = 5381;

    while (int c = *str++) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

#endif /* UTILITIES_H_ */
