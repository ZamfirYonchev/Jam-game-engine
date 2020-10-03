/*
 * entity.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include "components/position.h"
#include "components/control.h"
#include "components/movement.h"
#include "components/collision.h"
#include "components/interaction.h"
#include "components/health.h"
#include "components/visuals.h"
#include "components/null_position.h"
#include "components/null_control.h"
#include "components/null_movement.h"
#include "components/null_collision.h"
#include "components/null_interaction.h"
#include "components/null_health.h"
#include "components/null_visuals.h"
#include "types.h"
#include <utility>
#include <ostream>
#include <memory>
#include <type_traits>
#include "components/component.h"
#include <iostream>

class Entity
{
public:
    Entity(EntityID id);
    Entity() : Entity(EntityID(-1)) {}
    ~Entity()
    {
    	clear();
    }

    Entity(const Entity&) = delete;
    Entity(Entity&& rhs) noexcept;

    Entity& operator=(const Entity&) = delete;
    Entity& operator=(Entity&& rhs) noexcept;

    template<typename T>
    T& component() { return *T::null; }

    template<typename T>
    const T& component() const  { return *T::null; }

	template<typename T, typename... Args>
	void set_component(Args&&... args)
	{
		set_component_ptr(make_unique_component<T>(std::forward<Args>(args)...));
	}

	template<typename T>
	void set_component_ptr(unique_component_ptr<T> _component) { std::cerr << "Missing set_component_ptr for component " << *_component << '\n';}

	void set_id(EntityID id)
    { m_id = id; }

    EntityID id() const { return m_id; }

    void clear();

    friend std::ostream& operator<<(std::ostream& stream, const Entity& entity)
    {
    	stream << "AddEntity\n"
    	   << *(entity.m_position)
		   << *(entity.m_control)
		   << *(entity.m_movement)
		   << *(entity.m_collision)
		   << *(entity.m_interaction)
		   << *(entity.m_health)
		   << *(entity.m_visuals)
		   << std::endl;

    	return stream;
    }

private:
    EntityID m_id;
    unique_component_ptr<Position> m_position;
    unique_component_ptr<Control> m_control;
    unique_component_ptr<Movement> m_movement;
    unique_component_ptr<Collision> m_collision;
    unique_component_ptr<Interaction> m_interaction;
    unique_component_ptr<Health> m_health;
    unique_component_ptr<Visuals> m_visuals;
};

#endif /* ENTITY_H_ */
