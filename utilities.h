/*
 * utilities.h
 *
 *  Created on: May 20, 2020
 *      Author: zamfi
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include "globals.h"
#include "math_ext.h"

inline int scaled_x_value(double val)
{
	/* Non-branching calculation of the following:
	 * if val is integer, return it as is
	 * otherwise, multiply it by resolution.
	 * Example:
	 * if val == 5, return 5
	 * if val == 0.5 and resolution is 1000, return 500
	 * */
	return int(((!is_integer(val))*(globals().resolution_x-1)+1) * val);
}

inline int scaled_y_value(double val)
{
	/* Non-branching calculation of the following:
	 * if val is integer, return it as is
	 * otherwise, multiply it by resolution.
	 * Example:
	 * if val == 5, return 5
	 * if val == 0.5 and resolution is 1000, return 500
	 * */
	return int(((!is_integer(val))*(globals().resolution_y-1)+1) * val);
}

#endif /* UTILITIES_H_ */
