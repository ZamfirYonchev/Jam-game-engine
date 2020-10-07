/*
 * entity.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#include "entity.h"
#include "systems/systems.h"
#include "systems/control_system.h"
#include "systems/movement_system.h"
#include "systems/collision_system.h"
#include "systems/damage_system.h"
#include "systems/rendering_system.h"

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

Entity::Entity(Entity&& rhs) noexcept :
					   m_id(std::move(rhs.m_id))
					 , m_position(std::move(rhs.m_position))
					 , m_control(std::move(rhs.m_control))
					 , m_movement(std::move(rhs.m_movement))
					 , m_collision(std::move(rhs.m_collision))
					 , m_interaction(std::move(rhs.m_interaction))
					 , m_health(std::move(rhs.m_health))
					 , m_visuals(std::move(rhs.m_visuals))
{
}

Entity& Entity::operator=(Entity&& rhs) noexcept
{
	m_id = std::move(rhs.m_id);
	m_position = std::move(rhs.m_position);
	m_control = std::move(rhs.m_control);
	m_movement = std::move(rhs.m_movement);
	m_collision = std::move(rhs.m_collision);
	m_interaction = std::move(rhs.m_interaction);
	m_health = std::move(rhs.m_health);
	m_visuals = std::move(rhs.m_visuals);

	return *this;
}

void Entity::clear()
{
	m_position = std::move(make_unique_component<NullPosition>());
	m_control = std::move(make_unique_component<NullControl>());
	m_movement = std::move(make_unique_component<NullMovement>());
	m_collision = std::move(make_unique_component<NullCollision>());
	m_interaction = std::move(make_unique_component<NullInteraction>());
	m_health = std::move(make_unique_component<NullHealth>());
	m_visuals = std::move(make_unique_component<NullVisuals>());
}

template<>
Position& Entity::component()
{
	return *m_position;
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
	return *m_position;
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
void Entity::set_component_ptr<Position>(unique_component_ptr<Position> _position)
{
	m_position = std::move(_position);
}

template<>
void Entity::set_component_ptr<Control>(unique_component_ptr<Control> _control)
{
	const int8_t change = (_control.get() != Control::null) - (m_control.get() != Control::null);
	if(change < 0)
		system<ControlSystem>().remove_id(id());

	m_control = std::move(_control);

	if(change > 0)
		system<ControlSystem>().add_id(id());
}

template<>
void Entity::set_component_ptr<Movement>(unique_component_ptr<Movement> _movement)
{
	const int8_t change = (_movement.get() != Movement::null) - (m_movement.get() != Movement::null);
	if(change < 0)
		system<MovementSystem>().remove_id(id());

	m_movement = std::move(_movement);

	if(change > 0)
		system<MovementSystem>().add_id(id());
}

template<>
void Entity::set_component_ptr<Collision>(unique_component_ptr<Collision> _collision)
{
	const int8_t change = (_collision.get() != Collision::null) - (m_collision.get() != Collision::null);
	if(change < 0)
		system<CollisionSystem>().remove_id(id());

	m_collision = std::move(_collision);

	if(change > 0)
		system<CollisionSystem>().add_id(id());
}

template<>
void Entity::set_component_ptr<Interaction>(unique_component_ptr<Interaction> _interaction)
{
	m_interaction = std::move(_interaction);
}

template<>
void Entity::set_component_ptr<Health>(unique_component_ptr<Health> _health)
{
	const int8_t change = (_health.get() != Health::null) - (m_health.get() != Health::null);
	if(change < 0)
		system<DamageSystem>().remove_id(id());

	m_health = std::move(_health);

	if(change > 0)
		system<DamageSystem>().add_id(id());
}

template<>
void Entity::set_component_ptr<Visuals>(unique_component_ptr<Visuals> _visuals)
{
	const int8_t change = (_visuals.get() != Visuals::null) - (m_visuals.get() != Visuals::null);
	const bool layer_change = (_visuals.get() != Visuals::null) && (m_visuals.get() != Visuals::null) && (m_visuals->layer() != _visuals->layer());

	if(change < 0 || layer_change)
		system<RenderingSystem>().remove_id(id());

	m_visuals = std::move(_visuals);

	if(change > 0 || layer_change)
		system<RenderingSystem>().add_id(id());

}
