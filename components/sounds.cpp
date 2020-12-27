/*
 * sounds.cpp
 *
 *  Created on: Nov 25, 2020
 *      Author: zamfi
 */

#include "sounds.h"
#include "null_sounds.h"

Sounds* Sounds::null(new NullSounds());
