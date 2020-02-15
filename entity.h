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
#include "types.h"
#include <utility>

template <class T>
void release(T*& t)
{
	if(t != T::null)
	{
		delete t;
		t = T::null;
	}
}

class Entity
{
public:
    Entity(EntityID id);
    Entity() : Entity(-1) {}
    ~Entity()
    {
    	clear();
    }

    Entity(const Entity&) = delete;
    Entity(Entity&& rhs) : m_id(std::move(rhs.m_id))
    					 , m_position(std::move(rhs.m_position))
						 , m_control(std::move(rhs.m_control))
    					 , m_movement(std::move(rhs.m_movement))
						 , m_collision(std::move(rhs.m_collision))
						 , m_interaction(std::move(rhs.m_interaction))
						 , m_health(std::move(rhs.m_health))
						 , m_visuals(std::move(rhs.m_visuals))
    {
    	rhs.m_position = nullptr;
    	rhs.m_control = nullptr;
    	rhs.m_movement = nullptr;
    	rhs.m_collision = nullptr;
    	rhs.m_interaction = nullptr;
    	rhs.m_health = nullptr;
    	rhs.m_visuals = nullptr;
    }

    Entity& operator=(const Entity&) = delete;
    Entity& operator=(Entity&& rhs)
    {
    	delete m_position;
    	delete m_control;
    	delete m_movement;
    	delete m_collision;
    	delete m_interaction;
    	delete m_health;
    	delete m_visuals;

    	m_id = std::move(rhs.m_id);
		m_position = std::move(rhs.m_position);
		m_control = std::move(rhs.m_control);
		m_movement = std::move(rhs.m_movement);
		m_collision = std::move(rhs.m_collision);
		m_interaction = std::move(rhs.m_interaction);
		m_health = std::move(rhs.m_health);
		m_visuals = std::move(rhs.m_visuals);

		rhs.m_position = nullptr;
    	rhs.m_control = nullptr;
    	rhs.m_movement = nullptr;
    	rhs.m_collision = nullptr;
    	rhs.m_interaction = nullptr;
    	rhs.m_health = nullptr;
    	rhs.m_visuals = nullptr;

    	return *this;
    }

    Position* position() { return m_position; }
    Control* control() { return m_control; }
    Movement* movement() { return m_movement; }
    Collision* collision() { return m_collision; }
    Interaction* interaction() { return m_interaction; }
    Health* health() { return m_health; }
    Visuals* visuals() { return m_visuals; }

    void set_position(Position* _position);
    void set_control(Control* _control);
    void set_movement(Movement* _movement);
    void set_collision(Collision* _collision);
    void set_interaction(Interaction* _interaction);
    void set_health(Health* _health);
    void set_visuals(Visuals* _visuals);

    void set_id(EntityID id)
    { m_id = id; }

    EntityID id() const { return m_id; }

    void clear()
    {
    	release(m_position);
    	release(m_control);
    	release(m_movement);
    	release(m_collision);
    	release(m_interaction);
    	release(m_health);
    	release(m_visuals);
    }

private:
    EntityID m_id;
    Position* m_position;
    Control* m_control;
    Movement* m_movement;
    Collision* m_collision;
    Interaction* m_interaction;
    Health* m_health;
    Visuals* m_visuals;
};


#endif /* ENTITY_H_ */
