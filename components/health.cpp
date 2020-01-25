/*
 * health.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#include "health.h"
#include "null_health.h"

Health* Health::null(new NullHealth());
