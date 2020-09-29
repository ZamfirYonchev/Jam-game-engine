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
	const int8_t change = (_control != Control::null) - (m_control != Control::null);
	if(change < 0)
		control_system().remove_id(id());

	release(m_control);
	m_control = _control;

	if(change > 0)
		control_system().add_id(id());
}

void Entity::set_movement(Movement* _movement)
{
	const int8_t change = (_movement != Movement::null) - (m_movement != Movement::null);
	if(change < 0)
		movement_system().remove_id(id());

	release(m_movement);
	m_movement = _movement;

	if(change > 0)
		movement_system().add_id(id());
}

void Entity::set_collision(Collision* _collision)
{
	const int8_t change = (_collision != Collision::null) - (m_collision != Collision::null);
	if(change < 0)
		collision_system().remove_id(id());

	release(m_collision);
	m_collision = _collision;

	if(change > 0)
		collision_system().add_id(id());
}

void Entity::set_interaction(Interaction* _interaction)
{
	release(m_interaction);
	m_interaction = _interaction;
}

void Entity::set_health(Health* _health)
{
	const int8_t change = (_health != Health::null) - (m_health != Health::null);
	if(change < 0)
		damage_system().remove_id(id());

	release(m_health);
	m_health = _health;

	if(change > 0)
		damage_system().add_id(id());
}

void Entity::set_visuals(Visuals* _visuals)
{
	const int8_t change = (_visuals != Visuals::null) - (m_visuals != Visuals::null);
	const bool layer_change = (_visuals != Visuals::null) && (m_visuals != Visuals::null) && (m_visuals->layer() != _visuals->layer());

	if(change < 0 || layer_change)
		rendering_system().remove_id(id());

	release(m_visuals);
	m_visuals = _visuals;

	if(change > 0 || layer_change)
		rendering_system().add_id(id());

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

