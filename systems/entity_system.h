/*
 * entity_system.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef SYSTEMS_ENTITY_SYSTEM_H_
#define SYSTEMS_ENTITY_SYSTEM_H_

#include <vector>
#include <list>
#include "../entity.h"
#include "../types.h"
#include <optional>
#include "../optional_ref.h"

class EntitySystem
{
public:
	EntitySystem() = default;
    ~EntitySystem()
    {
    	clear();
    }

    EntitySystem(const EntitySystem&) = delete;
    EntitySystem(EntitySystem&& rhs) : m_entities(std::move(rhs.m_entities))
    								 , m_entities_to_remove(std::move(rhs.m_entities_to_remove))
    								 , m_free_entities(std::move(rhs.m_free_entities))
    {}

    EntitySystem& operator=(const EntitySystem&) = delete;
    EntitySystem& operator=(EntitySystem&& rhs)
    {
    	clear();
    	m_entities = std::move(rhs.m_entities);
    	m_entities_to_remove = std::move(rhs.m_entities_to_remove);
    	m_free_entities = std::move(rhs.m_free_entities);

    	return *this;
    }

    Entity& add_new_entity();
    void remove_entity(EntityID id)
    {
    	m_entities_to_remove.push_back(id);
    }


    optional_ref<Entity> entity(EntityID id)
    {
    	//EntityID actual_id = (id < 0) ? m_entities.size()-id : id;
    	if(id >= 0 && id < int(m_entities.size()))
    		return optional_ref<Entity>(m_entities[id]);
    	else
    		return optional_ref<Entity>();
    }

    void clear()
    {
        m_entities.clear();
        m_entities_to_remove.clear();
        m_free_entities.clear();
    }

    void clean_removed_entites();

private:
    std::vector<Entity> m_entities;
    std::list<EntityID> m_entities_to_remove;
    std::list<EntityID> m_free_entities;
};

#endif /* SYSTEMS_ENTITY_SYSTEM_H_ */
