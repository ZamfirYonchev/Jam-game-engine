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
    entity_system().add_new_entity();
    Entity& entity = *(entity_system().entity(entity_system().last_id()));
    entity.set_position(new AbsolutePosition(m_x, m_y, m_w, m_h));
    entity.set_control(new ConstantControl(1, false, false, Control::RIGHT));
    entity.set_movement(new FullMovement(false));
    entity.set_collision(new DamageCollision(Collision::TRANSPARENT, 0.01));
    entity.set_visuals(new StaticVisuals(m_spr_id, 0));
    rendering_system().set_entity_layer(entity.id(), Visuals::FOREGROUND);
    globals().access_entity_id = entity_system().last_id();
}


