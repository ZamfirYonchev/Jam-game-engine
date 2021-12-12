/*
 * visuals_enums.h
 *
 *  Created on: Nov 27, 2021
 *      Author: zamfi
 */

#ifndef COMPONENTS_VISUALS_ENUMS_H_
#define COMPONENTS_VISUALS_ENUMS_H_

#include "../types.h"

enum class VisualLayer {FAR_BACKGROUND = 0, CLOSE_BACKGROUND = 1, ACTION = 2, ACTION_FRONT = 3, FOREGROUND = 4};
static constexpr int NUM_OF_LAYERS = 5;

struct AnimationFrame {AnimationID id; int frame; };

#endif /* COMPONENTS_VISUALS_ENUMS_H_ */
