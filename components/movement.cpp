/*
 * movement.cpp
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#include "movement.h"
#include "null_movement.h"

Movement* Movement::null(new NullMovement());
