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
    const double GRAVITY_ACCEL = -0.00980665; //always (IRL, 9.80665m/s^2 = 0.00980665mm/ms^2)

    void update(const Time time_delta);
};

#endif /* SYSTEMS_MOVEMENT_SYSTEM_H_ */
