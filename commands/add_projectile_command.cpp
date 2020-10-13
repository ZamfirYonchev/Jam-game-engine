/*
 * add_projectile_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "add_projectile_command.h"
#include "../entity.h"
#include "../components/absolute_position.h"
#include "../components/constant_control.h"
#include "../components/full_movement.h"
#include "../components/damage_collision.h"
#include "../components/static_visuals.h"
#include "../systems/systems.h"
#include "../systems/entity_system.h"
#include "../systems/rendering_system.h"

void AddProjectileCommand::execute() const
{
	Entity& entity = system<EntitySystem>().add_new_entity();
    entity.set_component<AbsolutePosition>(m_pos);
    entity.set_component<ConstantControl>(1.0, 0.0, 0.0, Control::RIGHT);
    entity.set_component<FullMovement>(false);
    entity.set_component<DamageCollision>(Collision::TRANSPARENT, 0.01);
    entity.set_component<StaticVisuals>(m_spr_id, 0);
    system<RenderingSystem>().set_entity_layer(entity.id(), Visuals::FOREGROUND);
    system<EntitySystem>().add_accessed_entity(entity.id());
}


