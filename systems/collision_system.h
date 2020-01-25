/*
 * collision_system.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef SYSTEMS_COLLISION_SYSTEM_H_
#define SYSTEMS_COLLISION_SYSTEM_H_

#include "system_base.h"

class CollisionSystem : public SystemBase
{
public:
    void update(Time time_diff);
};

#endif /* SYSTEMS_COLLISION_SYSTEM_H_ */
