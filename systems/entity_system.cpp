/*
 * entity_system.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#include "entity_system.h"
#include "systems.h"
#include "control_system.h"
#include "movement_system.h"
#include "collision_system.h"
#include "damage_system.h"
#include "rendering_system.h"

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
		system<MovementSystem>().remove_id(*it);
		system<CollisionSystem>().remove_id(*it);
		system<DamageSystem>().remove_id(*it);
		system<RenderingSystem>().remove_id(*it);

		m_entities[*it].clear();
		m_free_entities.insert(*it);
	}
	m_entities_to_remove.clear();
}

