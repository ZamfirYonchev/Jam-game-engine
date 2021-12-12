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
#include "../types.h"
#include <algorithm>
#include "../type_pack.h"
#include "../components/component.h"
#include "../ref_pack.h"

template<typename... Ts>
class EntitySystem
{
public:
	EntitySystem() = default;
    ~EntitySystem() = default;
    EntitySystem(const EntitySystem&) = delete;
    EntitySystem(EntitySystem&& rhs) noexcept = default;
    EntitySystem& operator=(const EntitySystem&) = delete;
    EntitySystem& operator=(EntitySystem&& rhs) noexcept = default;

    template<typename F>
    void for_each_component_pack(F&& func)
    {
    	for(int entity_id = 0; entity_id < size(); ++entity_id)
    		func((m_components.template access<std::vector<Ts>>()[entity_id])...);
    }

    int size() const
    {
    	return m_components.t.size();
    }

    EntityID add_new_entity()
    {
    	EntityID id;
        if(m_free_entities.size() == 0)
        {
        	id = size();
        	(m_components.template access<std::vector<Ts>>().emplace_back(), ...);
        }
        else
        {
        	id = *m_free_entities.begin();
        	m_free_entities.erase(id);
        }

        //TODO add debug_level control
        //std::cout << (size() - m_free_entities.size()) << " entities.\n";

        return id;
    }

    void remove_entity(const EntityID id)
    {
    	m_entities_to_remove.insert(id);
    }

    template<typename T>
    T& entity_component(const EntityID id)
    {
    	if(0 <= id && id < static_cast<EntityID>(size()))
    		return m_components.template access<std::vector<T>>()[id];
    	else
    		return null<T>();
    }

    template<typename T>
    const T& entity_component(const EntityID id) const
    {
    	if(0 <= id && id < static_cast<EntityID>(size()))
    		return m_components.template access<std::vector<T>>()[id];
    	else
    		return null<T>();
    }

    template<typename T>
    T& set_entity_component(const EntityID id, T&& component, int8_t& change)
    {
    	using ComponentT = std::decay_t<T>;

    	change = 0;

    	if(0 <= id && id < static_cast<EntityID>(size()))
    	{
    		T& local_component = m_components.template access<std::vector<ComponentT>>()[id];
    		change = bool(component) - bool(local_component);
    		local_component = std::forward<T>(component);
        	return  local_component;
    	}
    	else
    		return null<ComponentT>();
    }

    void clear()
    {
        m_entities_to_remove.clear();
    	m_free_entities.clear();
    	(m_components.template access<std::vector<Ts>>().clear(), ...);
    }

    template<typename AllSystemsT>
    void clean_removed_entites(AllSystemsT& all_systems)
    {
    	for(const auto id : m_entities_to_remove)
    	{
    		all_systems.remove_id(id);

    		((m_components.template access<std::vector<Ts>>()[id] = null<Ts>()), ...);
    		m_free_entities.insert(id);
    	}
    	m_entities_to_remove.clear();
    }

    template<typename ComponentT>
    struct ComponentAccessor
    {
    	ComponentAccessor(EntitySystem& _entity_system) : entity_system{_entity_system} {}

    	const ComponentT& operator()(const EntityID id) const
    	{
    		return entity_system.get().template entity_component<ComponentT>(id);
    	}

    	ComponentT& operator()(const EntityID id)
    	{
    		return entity_system.get().template entity_component<ComponentT>(id);
    	}

    	std::reference_wrapper<EntitySystem> entity_system;
    };


private:
    TypePack<std::vector<Ts>...> m_components;
    std::unordered_set<EntityID> m_entities_to_remove;
    std::unordered_set<EntityID> m_free_entities;
    std::array<EntityID, 16> m_last_accessed_entities;
    unsigned int m_head_of_last_accessed_entities {0};
};

#endif /* SYSTEMS_ENTITY_SYSTEM_H_ */
