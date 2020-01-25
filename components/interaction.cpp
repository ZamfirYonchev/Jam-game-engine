/*
 * interaction.cpp
 *
 *  Created on: Nov 16, 2019
 *      Author: zamfi
 */

#include "interaction.h"
#include "null_interaction.h"

Interaction* Interaction::null(new NullInteraction());
