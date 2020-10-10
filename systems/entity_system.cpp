/*
 * entity_system.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#include "entity_system.h"
#include "../definitions.h"

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
	for(const auto id : m_entities_to_remove)
	{
		AllSystems::remove_id(id);

		m_entities[id].clear();
		m_free_entities.insert(id);
	}
	m_entities_to_remove.clear();
}

