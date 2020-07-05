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
	using BaseT = typename T::Base;
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_component<BaseT>(new T(m_component));
	else
	{
		//error globals().access_entity_id
	}
}

void UseComponentCommand<InputControl>::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_control(new InputControl(&input_handler(), m_proc_id, m_proc_cooldown, entity_system().previous_entity()->id(), m_stability_control));
	else
	{
		//error globals().access_entity_id
	}
}

void UseComponentCommand<InputSelectControl>::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_control(new InputSelectControl(&input_handler(), m_select, m_max, m_proc_id));
	else
	{
		//error globals().access_entity_id
	}
}

void UseComponentCommand<ChaseAIControl>::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_control(new ChaseAIControl(entity_system().previous_entity()->id(), resolved_entity(m_target_id), m_attack_id, m_attack_cooldown, m_attack_range));
	else
	{
		//error globals().access_entity_id
	}
}

void UseComponentCommand<GuideControl>::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_control(new GuideControl(entity_system().previous_entity()->id(), resolved_entity(m_target_id), m_range));
	else
	{
		//error globals().access_entity_id
	}
}

void UseComponentCommand<HealthVisuals>::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_visuals(new HealthVisuals(entity_system().previous_entity()->id(), m_spr_id, m_repeat_x));
	else
	{
		//error globals().access_entity_id
	}
}

void UseComponentCommand<MenuItemVisuals>::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_visuals(new MenuItemVisuals(m_spr_id, entity_system().previous_entity()->id()));
	else
	{
		//error globals().access_entity_id
	}
}

void UseComponentCommand<BuildPosition>::execute() const
{
	if(entity_system().previous_entity() && entity_system().entity(m_builder_id))
		entity_system().previous_entity()->set_position
			(
				new BuildPosition
					( entity_system().previous_entity()->id()
					, m_builder_id
					, entity_system().entity(m_builder_id)->position()->x()
					, entity_system().entity(m_builder_id)->position()->y()
					)
			);
	else
	{
		//error globals().access_entity_id || m_builder_id
	}
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

