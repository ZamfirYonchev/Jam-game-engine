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

class SystemBase
{
public:
    void add(EntityID entity)
    {
        for(auto it = entities.begin(); it != entities.end(); ++it)
            if((*it) == entity)
            	return;

        entities.push_back(entity);
    }

    void remove(EntityID entity)
    {
        for(auto it = entities.begin(); it != entities.end(); ++it)
            if((*it) == entity)
            {
                entities.erase(it);
                break;
            }
    }

    void clear()
    {
        entities.clear();
    }

protected:
    std::list<EntityID> entities;
};

#endif /* SYSTEMS_SYSTEM_BASE_H_ */
