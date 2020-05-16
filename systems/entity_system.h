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
#include <stdexcept>

class EntitySystem
{
public:
	EntitySystem() : m_last_id(-1) {}
    ~EntitySystem()
    {
    	clear();
    }

    EntitySystem(const EntitySystem&) = delete;
    EntitySystem(EntitySystem&& rhs) : m_entities(std::move(rhs.m_entities))
    								 , m_entities_to_remove(std::move(rhs.m_entities_to_remove))
    								 , m_free_entities(std::move(rhs.m_free_entities))
    								 , m_last_id(std::move(rhs.m_last_id))
    {}

    EntitySystem& operator=(const EntitySystem&) = delete;
    EntitySystem& operator=(EntitySystem&& rhs)
    {
    	clear();
    	m_entities = std::move(rhs.m_entities);
    	m_entities_to_remove = std::move(rhs.m_entities_to_remove);
    	m_free_entities = std::move(rhs.m_free_entities);
    	m_last_id = std::move(rhs.m_last_id);

    	return *this;
    }

    void add_new_entity();
    void remove_entity(EntityID id)
    {
    	m_entities_to_remove.push_back(id);
    }

    Entity& entity(EntityID id)
    {
    	if(id < m_entities.size())
            return m_entities[id];
    	else
    		throw std::out_of_range("out of range id");
    }

    void clear()
    {
        m_entities.clear();
        m_entities_to_remove.clear();
        m_free_entities.clear();
    }

    EntityID last_id() const
    {
    	return m_last_id;
    }

    void clean_removed_entites();

private:
    std::vector<Entity> m_entities;
    std::list<EntityID> m_entities_to_remove;
    std::list<EntityID> m_free_entities;
    int m_last_id;
};

#endif /* SYSTEMS_ENTITY_SYSTEM_H_ */
