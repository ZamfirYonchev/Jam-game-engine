/*
 * collision.cpp
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#include "collision.h"
#include "null_collision.h"

Collision* Collision::null(new NullCollision());
