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
	free(m_position);
	m_position = _position;
}

void Entity::set_control(Control* _control)
{
	if(m_control != Control::null && _control == Control::null)
	{
		globals.control_system.remove(id());
		m_control = _control;
	}

	free(m_control);

	if(m_control == Control::null && _control != Control::null)
	{
		m_control = _control;
		globals.control_system.add(id());
	}
	else
		m_control = _control;
}

void Entity::set_movement(Movement* _movement)
{
	if(m_movement != Movement::null && _movement == Movement::null)
	{
		globals.movement_system.remove(id());
		m_movement = _movement;
	}

	free(m_movement);

	if(m_movement == Movement::null && _movement != Movement::null)
	{
		m_movement = _movement;
		globals.movement_system.add(id());
	}
	else
		m_movement = _movement;
}

void Entity::set_collision(Collision* _collision)
{
	if(m_collision != Collision::null && _collision == Collision::null)
	{
		globals.collision_system.remove(id());
		m_collision = _collision;
	}

	free(m_collision);

	if(m_collision == Collision::null && _collision != Collision::null)
	{
		m_collision = _collision;
		globals.collision_system.add(id());
	}
	else
		m_collision = _collision;
}

void Entity::set_interaction(Interaction* _interaction)
{
	free(m_interaction);
	m_interaction = _interaction;
}

void Entity::set_health(Health* _health)
{
	if(m_health != Health::null && _health == Health::null)
	{
		globals.damage_system.remove(id());
		m_health = _health;
	}

	free(m_health);

	if(m_health == Health::null && _health != Health::null)
	{
		m_health = _health;
		globals.damage_system.add(id());
	}
	else
		m_health = _health;
}

void Entity::set_visuals(Visuals* _visuals)
{
	if(m_visuals != Visuals::null && _visuals == Visuals::null)
		globals.rendering_system.remove(id());

	free(m_visuals);

	if(m_visuals == Visuals::null && _visuals != Visuals::null)
	{
		m_visuals = _visuals;
		globals.rendering_system.add(id());
	}
	else
		m_visuals = _visuals;
}

