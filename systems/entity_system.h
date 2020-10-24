/*
 * entity_system.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef SYSTEMS_ENTITY_SYSTEM_H_
#define SYSTEMS_ENTITY_SYSTEM_H_

#include <vector>
#include <unordered_set>
#include <array>
#include "../entity.h"
#include "../types.h"
#include <algorithm>
#include "../type_pack.h"

class RenderingSystem;

template<typename... Ts>
class EntitySystem
{
public:
	using EntityT = Entity<Ts...>;
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
    EntitySystem(EntitySystem&& rhs) noexcept :
    								   m_entities(std::move(rhs.m_entities))
    								 , m_entities_to_remove(std::move(rhs.m_entities_to_remove))
    								 , m_free_entities(std::move(rhs.m_free_entities))
    								 , m_last_accessed_entities(std::move(rhs.m_last_accessed_entities))
    								 , m_head_of_last_accessed_entities(std::move(rhs.m_head_of_last_accessed_entities))
    {}

    EntitySystem& operator=(const EntitySystem&) = delete;
    EntitySystem& operator=(EntitySystem&& rhs) noexcept
    {
    	clear();
    	m_entities = std::move(rhs.m_entities);
    	m_entities_to_remove = std::move(rhs.m_entities_to_remove);
    	m_free_entities = std::move(rhs.m_free_entities);

    	return *this;
    }

    template<typename F>
    void for_each(F&& func) const
    {
    	std::for_each(std::cbegin(m_entities), std::cend(m_entities), std::forward<F>(func));
    }

    template<typename F>
    void for_each(F&& func)
    {
    	std::for_each(std::begin(m_entities), std::end(m_entities), std::forward<F>(func));
    }

    AbsEntityID add_new_entity()
    {
    	AbsEntityID id;
        if(m_free_entities.size() == 0)
        {
        	id = m_entities.size();
        	m_entities.push_back(EntityT(id));
        }
        else
        {
        	id = *m_free_entities.begin();
        	m_free_entities.erase(id);
        }

        return id;
    }

    void remove_entity(const EntityID id)
    {
    	m_entities_to_remove.insert(resolved_id(id));
    }

    template<typename T>
    T& entity_component(const AbsEntityID id, const T* ptr)
    {
    	if(id < m_entities.size())
    		return m_entities[id].component(ptr);
    	else
    		return *T::null;
    }

    template<typename T>
    T& entity_component(const EntityID id, const T* ptr)
    {
    	return entity_component(resolved_id(id), ptr);
    }

    template<typename T>
    const T& entity_component(const AbsEntityID id, const T* ptr) const
    {
    	if(id < int(m_entities.size()))
    		return m_entities[id].component(ptr);
    	else
    		return *T::null;
    }

    template<typename T>
    const T& entity_component(const EntityID id, const T* ptr) const
    {
    	return entity_component(resolved_id(id), ptr);
    }

    template<typename T, typename AllSystemsT>
	void set_entity_component(const AbsEntityID id, AllSystemsT& all_systems, RenderingSystem& rendering_system, const T& component)
    {
    	if(id < m_entities.size())
    		m_entities[id].set_component(all_systems, rendering_system, component);
    }

    template<typename T, typename AllSystemsT>
	void set_entity_component(const EntityID id, AllSystemsT& all_systems, RenderingSystem& rendering_system, const T& component)
    {
    	set_entity_component(resolved_id(id), all_systems, rendering_system, component);
    }

    void clear()
    {
        m_entities_to_remove.clear();
    	m_free_entities.clear();
        m_entities.clear();
    }

    template<typename AllSystemsT>
    void clean_removed_entites(AllSystemsT& all_systems)
    {
    	for(const auto id : m_entities_to_remove)
    	{
    		all_systems.remove_id(id);

    		m_entities[id].clear();
    		m_free_entities.insert(id);
    	}
    	m_entities_to_remove.clear();
    }

    void add_accessed_entity(const AbsEntityID id)
    {
    	m_head_of_last_accessed_entities = (m_head_of_last_accessed_entities-1+m_last_accessed_entities.size())%m_last_accessed_entities.size();
    	m_last_accessed_entities[m_head_of_last_accessed_entities] = id;
    }

    void add_accessed_entity(const EntityID id)
    {
    	add_accessed_entity(resolved_id(id));
    }

    constexpr AbsEntityID previous_entity_id() const
    {
    	return AbsEntityID{m_last_accessed_entities[m_head_of_last_accessed_entities]};
    }

    constexpr AbsEntityID previous_entity_id(const unsigned int n) const
    {
    	const unsigned int cycling_index = (m_head_of_last_accessed_entities+n)%m_last_accessed_entities.size();
		return AbsEntityID{m_last_accessed_entities[cycling_index]};
    }

    AbsEntityID resolved_id(const EntityID in_entity_id)
    {
    	if(in_entity_id >= 0)
    		return AbsEntityID(in_entity_id);
    	else
    		return previous_entity_id(-1-in_entity_id);
    }

private:
    std::vector<EntityT> m_entities;
    std::unordered_set<AbsEntityID> m_entities_to_remove;
    std::unordered_set<AbsEntityID> m_free_entities;
    std::array<AbsEntityID, 10> m_last_accessed_entities;
    unsigned int m_head_of_last_accessed_entities;
};

#endif /* SYSTEMS_ENTITY_SYSTEM_H_ */
