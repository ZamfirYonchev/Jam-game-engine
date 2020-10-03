/*
 * use_component_command.cpp
 *
 *  Created on: Jul 1, 2020
 *      Author: zamfi
 */

#include "use_component_command.h"
#include "../globals.h"
#include "../utilities.h"
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
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_component<T>(m_component);
	else
	{
		//error globals().access_entity_id
	}
}

template<>
void UseComponentCommand<NullPosition>::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_component<NullPosition>();
	else
	{
		//error globals().access_entity_id
	}
}

template<>
void UseComponentCommand<NullControl>::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_component<NullControl>();
	else
	{
		//error globals().access_entity_id
	}
}

template<>
void UseComponentCommand<NullMovement>::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_component<NullMovement>();
	else
	{
		//error globals().access_entity_id
	}
}

template<>
void UseComponentCommand<NullCollision>::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_component<NullCollision>();
	else
	{
		//error globals().access_entity_id
	}
}

template<>
void UseComponentCommand<NullInteraction>::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_component<NullInteraction>();
	else
	{
		//error globals().access_entity_id
	}
}

template<>
void UseComponentCommand<NullHealth>::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_component<NullHealth>();
	else
	{
		//error globals().access_entity_id
	}
}

template<>
void UseComponentCommand<NullVisuals>::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_component<NullVisuals>();
	else
	{
		//error globals().access_entity_id
	}
}

void UseComponentCommand<InputControl>::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_component<InputControl>(&input_handler(), m_proc_id, m_proc_cooldown, entity_system().previous_entity()->id(), m_stability_control);
	else
	{
		//error globals().access_entity_id
	}
}

void UseComponentCommand<InputSelectControl>::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_component<InputSelectControl>(&input_handler(), m_select, m_max, m_proc_id);
	else
	{
		//error globals().access_entity_id
	}
}

void UseComponentCommand<ChaseAIControl>::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_component<ChaseAIControl>(entity_system().previous_entity()->id(), entity_system().resolved_id(m_target_id), m_attack_id, m_attack_cooldown, m_attack_range);
	else
	{
		//error globals().access_entity_id
	}
}

void UseComponentCommand<GuideControl>::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_component<GuideControl>(entity_system().previous_entity()->id(), entity_system().resolved_id(m_target_id), m_range);
	else
	{
		//error globals().access_entity_id
	}
}

void UseComponentCommand<HealthVisuals>::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_component<HealthVisuals>(entity_system().previous_entity()->id(), m_spr_id, m_repeat_x);
	else
	{
		//error globals().access_entity_id
	}
}

void UseComponentCommand<MenuItemVisuals>::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_component<MenuItemVisuals>(m_spr_id, entity_system().previous_entity()->id());
	else
	{
		//error globals().access_entity_id
	}
}

void UseComponentCommand<BuildPosition>::execute() const
{
	if(entity_system().previous_entity() && entity_system().entity(m_builder_id))
		entity_system().previous_entity()->set_component<BuildPosition>
														( entity_system().previous_entity()->id()
														, m_builder_id
														, entity_system().entity(m_builder_id)->component<Position>().x()
														, entity_system().entity(m_builder_id)->component<Position>().y()
														);
	else
	{
		//error globals().access_entity_id || m_builder_id
	}
}

void UseComponentCommand<TiledVisuals>::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_component<TiledVisuals>(m_spr_id, m_tile_w, m_tile_h, entity_system().previous_entity()->id());
	else
	{
		//error globals().access_entity_id
	}
}

void UseComponentCommand<AttachedPosition>::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_component<AttachedPosition>
														(
														entity_system().resolved_id(m_attached_id)
														, m_offset_x
														, m_offset_y
														, m_offset_w
														, m_offset_h
														);
	else
	{
		//error globals().access_entity_id
	}
}

void UseComponentCommand<AttachedHealth>::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_component<AttachedHealth>
														(
															entity_system().resolved_id(m_attached_id)
															, m_offset_hp
															, m_offset_max_hp
														);
	else
	{
		//error globals().access_entity_id
	}
}

template class UseComponentCommand<AbsolutePosition>;
template class UseComponentCommand<AttachedPosition>;
template class UseComponentCommand<ChaseAIControl>;
template class UseComponentCommand<ConstantControl>;
template class UseComponentCommand<GuideControl>;
template class UseComponentCommand<InputControl>;
template class UseComponentCommand<InputSelectControl>;
template class UseComponentCommand<NullControl>;

template class UseComponentCommand<FullMovement>;
template class UseComponentCommand<InstantMovement>;

template class UseComponentCommand<BasicCollision>;
template class UseComponentCommand<DamageCollision>;

template class UseComponentCommand<FullInteraction>;
template class UseComponentCommand<NormalInteraction>;
template class UseComponentCommand<TriggerInteraction>;

template class UseComponentCommand<AttachedHealth>;
template class UseComponentCommand<CharacterHealth>;
template class UseComponentCommand<TimedHealth>;

template class UseComponentCommand<CharacterVisuals>;
template class UseComponentCommand<HealthVisuals>;
template class UseComponentCommand<MenuItemVisuals>;
template class UseComponentCommand<StaticVisuals>;
template class UseComponentCommand<TiledVisuals>;

