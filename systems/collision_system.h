/*
 * collision_system.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef SYSTEMS_COLLISION_SYSTEM_H_
#define SYSTEMS_COLLISION_SYSTEM_H_

#include "system_base.h"
#include <unordered_map>

class CollisionSystem : public SystemBase
{
public:
    void update(const Time time_diff);
    std::unordered_map<EntityID/*::Type*/, bool> entities_last_triggered_reset();
};

#endif /* SYSTEMS_COLLISION_SYSTEM_H_ */
