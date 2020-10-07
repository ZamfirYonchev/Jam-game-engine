/*
 * globals.cpp
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#include "globals.h"

Globals& globals()
{
	static Globals globals;
	return globals;
}
