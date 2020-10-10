/*
 * use_component_command.cpp
 *
 *  Created on: Jul 1, 2020
 *      Author: zamfi
 */

#include "use_component_command.h"
#include "../utilities.h"
#include "../systems/systems.h"
#include "../systems/entity_system.h"

#include "../components/absolute_position.h"
#include "../components/attached_position.h"
#include "../components/null_position.h"

#include "../components/chase_ai_control.h"
#include "../components/constant_control.h"
#include "../components/guide_control.h"
#include "../components/input_control.h"
#include "../components/input_select_control.h"
#include "../components/null_control.h"

#include "../components/full_movement.h"
#include "../components/instant_movement.h"
#include "../components/null_movement.h"

#include "../components/basic_collision.h"
#include "../components/damage_collision.h"
#include "../components/null_collision.h"

#include "../components/full_interaction.h"
#include "../components/normal_interaction.h"
#include "../components/trigger_interaction.h"
#include "../components/null_interaction.h"

#include "../components/attached_health.h"
#include "../components/character_health.h"
#include "../components/timed_health.h"
#include "../components/null_health.h"

#include "../components/character_visuals.h"
#include "../components/health_visuals.h"
#include "../components/menu_item_visuals.h"
#include "../components/static_visuals.h"
#include "../components/tiled_visuals.h"
#include "../components/null_visuals.h"

template<typename T>
void UseComponentCommand<T>::execute() const
{
	system<EntitySystem>().set_entity_component<T>(system<EntitySystem>().previous_entity_id(), m_component);
}

void UseComponentCommand<InputControl>::execute() const
{
	system<EntitySystem>().set_entity_component<InputControl>(system<EntitySystem>().previous_entity_id(), m_proc_id, m_proc_cooldown, system<EntitySystem>().previous_entity_id(), m_stability_control);
}

void UseComponentCommand<InputSelectControl>::execute() const
{
	system<EntitySystem>().set_entity_component<InputSelectControl>(system<EntitySystem>().previous_entity_id(), m_select, m_max, m_proc_id);
}

void UseComponentCommand<ChaseAIControl>::execute() const
{
	system<EntitySystem>().set_entity_component<ChaseAIControl>(system<EntitySystem>().previous_entity_id(), system<EntitySystem>().previous_entity_id(), system<EntitySystem>().resolved_id(m_target_id), m_attack_id, m_attack_cooldown, m_attack_range);
}

void UseComponentCommand<GuideControl>::execute() const
{
	system<EntitySystem>().set_entity_component<GuideControl>(system<EntitySystem>().previous_entity_id(), system<EntitySystem>().previous_entity_id(), system<EntitySystem>().resolved_id(m_target_id), m_range);
}

void UseComponentCommand<HealthVisuals>::execute() const
{
	system<EntitySystem>().set_entity_component<HealthVisuals>(system<EntitySystem>().previous_entity_id(), system<EntitySystem>().previous_entity_id(), m_spr_id, m_repeat_x);
}

void UseComponentCommand<MenuItemVisuals>::execute() const
{
	system<EntitySystem>().set_entity_component<MenuItemVisuals>(system<EntitySystem>().previous_entity_id(), m_spr_id, system<EntitySystem>().previous_entity_id());
}

void UseComponentCommand<BuildPosition>::execute() const
{
	const auto& builder_pos = system<EntitySystem>().entity_component<Position>(m_builder_id);
	system<EntitySystem>().set_entity_component<BuildPosition>(system<EntitySystem>().previous_entity_id(), system<EntitySystem>().previous_entity_id(), m_builder_id, builder_pos.x(), builder_pos.y());
}

void UseComponentCommand<TiledVisuals>::execute() const
{
	system<EntitySystem>().set_entity_component<TiledVisuals>(system<EntitySystem>().previous_entity_id(), m_spr_id, m_tile_w, m_tile_h, system<EntitySystem>().previous_entity_id());
}

void UseComponentCommand<AttachedPosition>::execute() const
{
	system<EntitySystem>().set_entity_component<AttachedPosition>(system<EntitySystem>().previous_entity_id(), system<EntitySystem>().resolved_id(m_attached_id), m_offset_x, m_offset_y, m_offset_w, m_offset_h);
}

void UseComponentCommand<AttachedHealth>::execute() const
{
	system<EntitySystem>().set_entity_component<AttachedHealth>(system<EntitySystem>().previous_entity_id(), system<EntitySystem>().resolved_id(m_attached_id), m_offset_hp, m_offset_max_hp);
}

template class UseComponentCommand<AbsolutePosition>;
template class UseComponentCommand<AttachedPosition>;
template class UseComponentCommand<NullPosition>;

template class UseComponentCommand<ChaseAIControl>;
template class UseComponentCommand<ConstantControl>;
template class UseComponentCommand<GuideControl>;
template class UseComponentCommand<InputControl>;
template class UseComponentCommand<InputSelectControl>;
template class UseComponentCommand<NullControl>;

template class UseComponentCommand<FullMovement>;
template class UseComponentCommand<InstantMovement>;
template class UseComponentCommand<NullMovement>;

template class UseComponentCommand<BasicCollision>;
template class UseComponentCommand<DamageCollision>;
template class UseComponentCommand<NullCollision>;

template class UseComponentCommand<FullInteraction>;
template class UseComponentCommand<NormalInteraction>;
template class UseComponentCommand<TriggerInteraction>;
template class UseComponentCommand<NullInteraction>;

template class UseComponentCommand<AttachedHealth>;
template class UseComponentCommand<CharacterHealth>;
template class UseComponentCommand<TimedHealth>;
template class UseComponentCommand<NullHealth>;

template class UseComponentCommand<CharacterVisuals>;
template class UseComponentCommand<HealthVisuals>;
template class UseComponentCommand<MenuItemVisuals>;
template class UseComponentCommand<StaticVisuals>;
template class UseComponentCommand<TiledVisuals>;
template class UseComponentCommand<NullVisuals>;
