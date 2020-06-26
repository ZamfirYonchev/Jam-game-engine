/*
 * damage_system.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef SYSTEMS_DAMAGE_SYSTEM_H_
#define SYSTEMS_DAMAGE_SYSTEM_H_

#include "system_base.h"

class DamageSystem : public SystemBase
{
public:
    void update(const Time time_diff);
};

#endif /* SYSTEMS_DAMAGE_SYSTEM_H_ */
