/*
 * system_base.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef SYSTEMS_SYSTEM_BASE_H_
#define SYSTEMS_SYSTEM_BASE_H_

#include "../types.h"
#include <unordered_set>

class SystemBase
{
public:
    void add_id(const EntityID entity)
    {
		entities.insert(entity);
    }

    void remove_id(const EntityID entity)
    {
		entities.erase(entity);
    }

    void clear()
    {
        entities.clear();
    }

protected:
    std::unordered_set<EntityID> entities;
};

#endif /* SYSTEMS_SYSTEM_BASE_H_ */
