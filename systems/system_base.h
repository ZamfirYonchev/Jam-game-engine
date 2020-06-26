/*
 * system_base.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef SYSTEMS_SYSTEM_BASE_H_
#define SYSTEMS_SYSTEM_BASE_H_

#include "../types.h"
#include <list>
#include <algorithm>

class SystemBase
{
public:
    void add_id(const EntityID entity)
    {
    	auto it = std::find_if(cbegin(entities), cend(entities), [entity](EntityID id){ return id == entity; });
    	if(it == cend(entities))
    		entities.push_back(entity);
    }

    void remove_id(const EntityID entity)
    {
    	auto it = std::find_if(cbegin(entities), cend(entities), [entity](EntityID id){ return id == entity; });
    	if(it != cend(entities))
			entities.erase(it);
    }

    void clear()
    {
        entities.clear();
    }

protected:
    std::list<EntityID> entities;
};

#endif /* SYSTEMS_SYSTEM_BASE_H_ */
