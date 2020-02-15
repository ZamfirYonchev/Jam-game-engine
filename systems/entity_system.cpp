/*
 * entity_system.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#include "entity_system.h"
#include "../globals.h"

void EntitySystem::add_new_entity()
{
    if(m_free_entities.size() == 0)
    {
    	m_last_id = m_entities.size();
    	m_entities.push_back(Entity(m_last_id));
    }
    else
    {
    	m_last_id = m_free_entities.front();
    	m_free_entities.pop_front();
    }
}

void EntitySystem::clean_removed_entites()
{
	for(auto it = m_entities_to_remove.begin(); it != m_entities_to_remove.end(); ++it)
	{
		globals.movement_system.remove_id(*it);
		globals.collision_system.remove_id(*it);
		globals.damage_system.remove_id(*it);
		globals.rendering_system.remove_id(*it);

		m_entities[*it].clear();
		m_free_entities.push_back(*it);
	}
	m_entities_to_remove.clear();
}

