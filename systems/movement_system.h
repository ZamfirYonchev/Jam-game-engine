/*
 * movement_system.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef SYSTEMS_MOVEMENT_SYSTEM_H_
#define SYSTEMS_MOVEMENT_SYSTEM_H_

#include "system_base.h"

class MovementSystem : public SystemBase
{
public:
    const double GRAVITY_ACCEL = -0.005; //always

    void update(Time time_delta);
};

#endif /* SYSTEMS_MOVEMENT_SYSTEM_H_ */
