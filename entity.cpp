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

