/*
 * entity.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include "components/visuals.h"
#include "types.h"
#include <utility>
#include <ostream>
#include <memory>
#include <type_traits>
#include "components/component.h"
#include <iostream>
#include "utilities.h"
#include "type_pack.h"

template<typename... Ts>
class Entity
{
public:
    Entity(EntityID id)
	: m_id(id)
	{
    	clear();
	}

    ~Entity()
    {
    	clear();
    }

    Entity(const Entity&) = delete;
    Entity(Entity&& rhs) noexcept = default;

    Entity& operator=(const Entity&) = delete;
    Entity& operator=(Entity&& rhs) noexcept = default;

    template<typename T>
    T& component(const T*)
    {
    	return *(m_component_pack.access((unique_component_ptr<T>*)nullptr));
    }

    template<typename T>
    const T& component(const T*) const
    {
    	return *(m_component_pack.access((unique_component_ptr<T>*)nullptr));
    }

    template<typename T>
	void set_component_ptr(unique_component_ptr<T> _component)
    {
    	m_component_pack.access(&_component) = std::move(_component);
    }

    template<typename T, typename AllSystemsT, typename RenderingSystemT>
	void set_component(AllSystemsT& all_systems, RenderingSystemT& rendering_system, const T& _component)
	{
    	using BaseT = typename T::Base;
		const int8_t change = is_null_component(component((BaseT*)nullptr)) - is_null_component(_component);

		set_component_ptr<BaseT>(make_unique_component<T>(_component));

		all_systems.component_updated(component((BaseT*)nullptr), m_id, change);
		if constexpr(std::is_same<BaseT, Visuals>::value)
			rendering_system.component_updated(component((BaseT*)nullptr), m_id, change);
	}

	void set_id(const EntityID id) { m_id = id; }

	EntityID id() const { return m_id; }

    void clear()
    {
    	((void) m_component_pack.access((unique_component_ptr<Ts>*)nullptr).reset(Ts::null), ...);
    }

    friend std::ostream& operator<<(std::ostream& stream, const Entity& entity)
    {
		stream << "AddEntity\n";
    	((stream << entity.component((Ts*)nullptr)), ...);
		stream << std::endl;

    	return stream;
    }

private:
    EntityID m_id;
    TypePack<unique_component_ptr<Ts>...> m_component_pack;
};

#endif /* ENTITY_H_ */
