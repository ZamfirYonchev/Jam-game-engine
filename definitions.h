/*
 * definitions.h
 *
 *  Created on: Oct 10, 2020
 *      Author: zamfi
 */

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#include "systems/systems.h"
#include "systems/control_system.h"
#include "systems/movement_system.h"
#include "systems/collision_system.h"
#include "systems/damage_system.h"

using AllSystems = Systems<ControlSystem, MovementSystem, CollisionSystem, DamageSystem>;

#endif /* DEFINITIONS_H_ */
