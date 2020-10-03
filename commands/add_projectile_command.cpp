/*
 * add_projectile_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "add_projectile_command.h"
#include "../globals.h"
#include "../entity.h"
#include "../components/absolute_position.h"
#include "../components/constant_control.h"
#include "../components/full_movement.h"
#include "../components/damage_collision.h"
#include "../components/static_visuals.h"

void AddProjectileCommand::execute() const
{
	Entity& entity = entity_system().add_new_entity();
    entity.set_component<AbsolutePosition>(m_x, m_y, m_w, m_h);
    entity.set_component<ConstantControl>(1.0, 0.0, 0.0, Control::RIGHT);
    entity.set_component<FullMovement>(false);
    entity.set_component<DamageCollision>(Collision::TRANSPARENT, 0.01);
    entity.set_component<StaticVisuals>(m_spr_id, 0);
    rendering_system().set_entity_layer(entity.id(), Visuals::FOREGROUND);
    entity_system().add_accessed_entity(entity.id());
}


