/*
 * entity_system.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#include "entity_system.h"
#include "../globals.h"

Entity& EntitySystem::add_new_entity()
{
	EntityID id;
    if(m_free_entities.size() == 0)
    {
    	id = static_cast<EntityID>(m_entities.size());
    	m_entities.push_back(Entity(id));
    }
    else
    {
    	id = *m_free_entities.begin();
    	m_free_entities.erase(id);
    }

    return m_entities[id];
}

void EntitySystem::clean_removed_entites()
{
	for(auto it = m_entities_to_remove.begin(); it != m_entities_to_remove.end(); ++it)
	{
		movement_system().remove_id(*it);
		collision_system().remove_id(*it);
		damage_system().remove_id(*it);
		rendering_system().remove_id(*it);

		m_entities[*it].clear();
		m_free_entities.insert(*it);
	}
	m_entities_to_remove.clear();
}

