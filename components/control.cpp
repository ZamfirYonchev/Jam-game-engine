/*
 * control.cpp
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#include "control.h"
#include "null_control.h"

Control* Control::null(new NullControl());
