/*
 * entity.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#include "entity.h"
#include "globals.h"

Entity::Entity(EntityID id)
: m_id(id)
, m_position(Position::null)
, m_control(Control::null)
, m_movement(Movement::null)
, m_collision(Collision::null)
, m_interaction(Interaction::null)
, m_health(Health::null)
, m_visuals(Visuals::null)
{}


void Entity::set_position(Position* _position)
{
	release(m_position);
	m_position = _position;
}

void Entity::set_control(Control* _control)
{
	if(m_control != Control::null && _control == Control::null)
	{
		control_system().remove_id(id());
		m_control = _control;
	}

	release(m_control);

	if(m_control == Control::null && _control != Control::null)
	{
		m_control = _control;
		control_system().add_id(id());
	}
	else
		m_control = _control;
}

void Entity::set_movement(Movement* _movement)
{
	if(m_movement != Movement::null && _movement == Movement::null)
	{
		movement_system().remove_id(id());
		m_movement = _movement;
	}

	release(m_movement);

	if(m_movement == Movement::null && _movement != Movement::null)
	{
		m_movement = _movement;
		movement_system().add_id(id());
	}
	else
		m_movement = _movement;
}

void Entity::set_collision(Collision* _collision)
{
	if(m_collision != Collision::null && _collision == Collision::null)
	{
		collision_system().remove_id(id());
		m_collision = _collision;
	}

	release(m_collision);

	if(m_collision == Collision::null && _collision != Collision::null)
	{
		m_collision = _collision;
		collision_system().add_id(id());
	}
	else
		m_collision = _collision;
}

void Entity::set_interaction(Interaction* _interaction)
{
	release(m_interaction);
	m_interaction = _interaction;
}

void Entity::set_health(Health* _health)
{
	if(m_health != Health::null && _health == Health::null)
	{
		damage_system().remove_id(id());
		m_health = _health;
	}

	release(m_health);

	if(m_health == Health::null && _health != Health::null)
	{
		m_health = _health;
		damage_system().add_id(id());
	}
	else
		m_health = _health;
}

void Entity::set_visuals(Visuals* _visuals)
{
	if(m_visuals != Visuals::null && _visuals == Visuals::null)
		rendering_system().remove_id(id());

	release(m_visuals);

	if(m_visuals == Visuals::null && _visuals != Visuals::null)
	{
		m_visuals = _visuals;
		rendering_system().add_id(id());
	}
	else
		m_visuals = _visuals;
}

template<>
Position& Entity::component()
{
	return *position();
}

template<>
Control& Entity::component()
{
	return *m_control;
}

template<>
Movement& Entity::component()
{
	return *m_movement;
}

template<>
Collision& Entity::component()
{
	return *m_collision;
}

template<>
Interaction& Entity::component()
{
	return *m_interaction;
}

template<>
Health& Entity::component()
{
	return *m_health;
}

template<>
Visuals& Entity::component()
{
	return *m_visuals;
}

template<>
const Position& Entity::component() const
{
	return *position();
}

template<>
const Control& Entity::component() const
{
	return *m_control;
}

template<>
const Movement& Entity::component() const
{
	return *m_movement;
}

template<>
const Collision& Entity::component() const
{
	return *m_collision;
}

template<>
const Interaction& Entity::component() const
{
	return *m_interaction;
}

template<>
const Health& Entity::component() const
{
	return *m_health;
}

template<>
const Visuals& Entity::component() const
{
	return *m_visuals;
}

template<>
void Entity::set_component(Position* component)
{
	set_position(component);
}

template<>
void Entity::set_component(Control* component)
{
	set_control(component);
}

template<>
void Entity::set_component(Movement* component)
{
	set_movement(component);
}

template<>
void Entity::set_component(Collision* component)
{
	set_collision(component);
}

template<>
void Entity::set_component(Interaction* component)
{
	set_interaction(component);
}

template<>
void Entity::set_component(Health* component)
{
	set_health(component);
}

template<>
void Entity::set_component(Visuals* component)
{
	set_visuals(component);
}

