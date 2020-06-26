/*
 * control_system.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef SYSTEMS_CONTROL_SYSTEM_H_
#define SYSTEMS_CONTROL_SYSTEM_H_

#include "system_base.h"

class ControlSystem : public SystemBase
{
public:
    void update(const Time time_diff);
};


#endif /* SYSTEMS_CONTROL_SYSTEM_H_ */
