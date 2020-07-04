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
#include <array>
#include "../entity.h"
#include "../types.h"
#include <optional>
#include "../optional_ref.h"

class EntitySystem
{
public:
	EntitySystem() : m_entities()
				   , m_entities_to_remove()
				   , m_free_entities()
				   , m_last_accessed_entities()
				   , m_head_of_last_accessed_entities(0)
				   {}
    ~EntitySystem()
    {
    	clear();
    }

    EntitySystem(const EntitySystem&) = delete;
    EntitySystem(EntitySystem&& rhs) : m_entities(std::move(rhs.m_entities))
    								 , m_entities_to_remove(std::move(rhs.m_entities_to_remove))
    								 , m_free_entities(std::move(rhs.m_free_entities))
    								 , m_last_accessed_entities(std::move(rhs.m_last_accessed_entities))
    								 , m_head_of_last_accessed_entities(std::move(rhs.m_head_of_last_accessed_entities))
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

    const std::vector<Entity>& entities() const
	{
    	return m_entities;
	}

    Entity& add_new_entity();
    void remove_entity(const EntityID id)
    {
    	m_entities_to_remove.push_back(id);
    }


    optional_ref<Entity> entity(const EntityID id)
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

    void add_accessed_entity(const EntityID id)
    {
    	m_head_of_last_accessed_entities = (m_head_of_last_accessed_entities+1)%m_last_accessed_entities.size();
    	m_last_accessed_entities[m_head_of_last_accessed_entities] = id;
    }

    optional_ref<Entity> previous_entity()
	{
    	if(previous_entity_id() < m_entities.size())
    		return optional_ref<Entity>(m_entities[previous_entity_id()]);
    	else
    		return optional_ref<Entity>();
	}

    EntityID previous_entity_id() const
    {
    	return EntityID{m_last_accessed_entities[m_head_of_last_accessed_entities]};
    }

    EntityID previous_entity_id(unsigned int n) const
    {//TODO make sure n < size
    	const int cycling_index = (m_head_of_last_accessed_entities+m_last_accessed_entities.size()-n)%m_last_accessed_entities.size();
		return EntityID{m_last_accessed_entities[cycling_index]};
    }

private:
    std::vector<Entity> m_entities;
    std::list<EntityID> m_entities_to_remove;
    std::list<EntityID> m_free_entities;
    std::array<EntityID/*::Type*/, 10> m_last_accessed_entities;
    unsigned int m_head_of_last_accessed_entities;
};

#endif /* SYSTEMS_ENTITY_SYSTEM_H_ */
