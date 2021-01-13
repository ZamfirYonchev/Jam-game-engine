/*
 * use_component_command.h
 *
 *  Created on: Jul 1, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_COMPONENT_COMMAND_H_
#define COMMANDS_USE_COMPONENT_COMMAND_H_

#include "../types.h"
#include "null_command.h"

#include "../components/absolute_position.h"
#include "../components/attached_position.h"
#include "../components/build_position.h"
#include "../components/null_position.h"

#include "../components/input_control.h"
#include "../components/input_select_control.h"
#include "../components/constant_control.h"
#include "../components/guide_control.h"
#include "../components/chase_ai_control.h"
#include "../components/particle_control.h"
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

#include "../components/character_health.h"
#include "../components/attached_health.h"
#include "../components/timed_health.h"
#include "../components/null_health.h"

#include "../components/character_sounds.h"
#include "../components/null_sounds.h"

#include "../components/character_visuals.h"
#include "../components/health_visuals.h"
#include "../components/menu_item_visuals.h"
#include "../components/static_visuals.h"
#include "../components/tiled_visuals.h"
#include "../components/null_visuals.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

template<typename T>
class UseComponentCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	set_component(entity_system, rendering_system, all_systems, T{});
		return 0.0;
	}

    template<typename EntitySystemT, typename AllSystemsT>
    void set_component(EntitySystemT& entity_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, const T& component) const
    {
		entity_system.set_entity_component(entity_system.previous_entity_id(), all_systems, rendering_system, component);
    }
};

template<>
template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
CommandReturnValue UseComponentCommand<AbsolutePosition>::operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
{
	const auto x = command_system.exec_next();
	const auto y = command_system.exec_next();
	const auto w = command_system.exec_next();
	const auto h = command_system.exec_next();

	set_component(entity_system, rendering_system, all_systems, {x.real(), y.real(), w.real(), h.real()});

	return 0.0;
}


template<>
template<typename EntitySystemT>
class UseComponentCommand<AttachedPosition<EntitySystemT>>
{
public:
    template<typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	const auto attached_id = command_system.exec_next();
    	const auto offset_x = command_system.exec_next();
    	const auto offset_y = command_system.exec_next();
    	const auto offset_w = command_system.exec_next();
    	const auto offset_h = command_system.exec_next();

		entity_system.set_entity_component(entity_system.previous_entity_id(), all_systems, rendering_system, AttachedPosition<EntitySystemT>{EntityID(attached_id.integer()), offset_x.real(), offset_y.real(), offset_w.real(), offset_h.real(), entity_system});

		return 0.0;
	}
};

class UseAttachedPositionCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	const auto attached_id = command_system.exec_next();
    	const auto offset_x = command_system.exec_next();
    	const auto offset_y = command_system.exec_next();
    	const auto offset_w = command_system.exec_next();
    	const auto offset_h = command_system.exec_next();

		entity_system.set_entity_component(entity_system.previous_entity_id(), all_systems, rendering_system, AttachedPosition<EntitySystemT>{attached_id.integer(), offset_x.real(), offset_y.real(), offset_w.real(), offset_h.real(), entity_system});

		return 0.0;
	}
};

class UseBuildPositionCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	const auto self_id = entity_system.previous_entity_id();
    	const auto attached_id = command_system.exec_next();
    	const auto offset_x = command_system.exec_next();
    	const auto offset_y = command_system.exec_next();

		entity_system.set_entity_component(entity_system.previous_entity_id(), all_systems, rendering_system, BuildPosition<EntitySystemT>{self_id, EntityID(attached_id.integer()), offset_x.real(), offset_y.real(), entity_system});

		return 0.0;
	}
};

class UseInputControlCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	const auto self_id = entity_system.previous_entity_id();
    	const auto shoot_proc_id = command_system.exec_next();
    	const auto cooldown = command_system.exec_next();
    	const auto stability_control = command_system.exec_next();

		entity_system.set_entity_component(entity_system.previous_entity_id(), all_systems, rendering_system, InputControl<EntitySystemT>{ProcedureID(shoot_proc_id.integer()), cooldown.real(), self_id, stability_control.real(), entity_system, input_system});

		return 0.0;
	}
};

template<>
template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
CommandReturnValue UseComponentCommand<InputSelectControl>::operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
{
	const auto select = command_system.exec_next();
	const auto max = command_system.exec_next();
	const auto proc_id = command_system.exec_next();

	set_component(entity_system, rendering_system, all_systems, {int(select.integer()), int(max.integer()), ProcedureID(proc_id.integer()), input_system});

	return 0.0;
}

template<>
template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
CommandReturnValue UseComponentCommand<ConstantControl>::operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
{
	const auto move_decision = command_system.exec_next();
	const auto vetical_decision = command_system.exec_next();
	const auto look_dir = command_system.exec_next();

	set_component(entity_system, rendering_system, all_systems, {move_decision.real(), vetical_decision.real(), Control::LookDir(look_dir.integer())});

	return 0.0;
}

class UseGuideControlCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	const auto self_id = entity_system.previous_entity_id();
    	const auto target_id = command_system.exec_next();
    	const auto range = command_system.exec_next();

		entity_system.set_entity_component(entity_system.previous_entity_id(), all_systems, rendering_system, GuideControl<EntitySystemT>{self_id, EntityID(target_id.integer()), range.real(), entity_system});

		return 0.0;
	}
};

class UseChaseAIControlCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	const auto self_id = entity_system.previous_entity_id();
    	const auto target_id = command_system.exec_next();
    	const auto attack_proc_id = command_system.exec_next();
    	const auto attack_cooldown = command_system.exec_next();
    	const auto range = command_system.exec_next();

		entity_system.set_entity_component(entity_system.previous_entity_id(), all_systems, rendering_system, ChaseAIControl<EntitySystemT>{self_id, EntityID(target_id.integer()), ProcedureID(attack_proc_id.integer()), attack_cooldown.real(), range.real(), entity_system});

		return 0.0;
	}
};

class UseParticleControlCommand
{
public:
	UseParticleControlCommand(std::mt19937& gen) : m_gen{gen} {}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	const auto random_factor = command_system.exec_next();
    	const auto directed_factor = command_system.exec_next();
    	const auto direction_angle = command_system.exec_next();

		entity_system.set_entity_component(entity_system.previous_entity_id(), all_systems, rendering_system, ParticleControl{m_gen, random_factor.real(), directed_factor.real(), direction_angle.real()});

		return 0.0;
	}

private:
    std::mt19937& m_gen;
};

template<>
template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
CommandReturnValue UseComponentCommand<FullMovement>::operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
{
	const auto mass = command_system.exec_next();
	const auto friction_x = command_system.exec_next();
	const auto friction_y = command_system.exec_next();
	const auto move_force = command_system.exec_next();
	const auto jump_force = command_system.exec_next();
	const auto gravity_affected = command_system.exec_next();

	set_component(entity_system, rendering_system, all_systems, {mass.real(), friction_x.real(), friction_x.real(), move_force.real(), jump_force.real(), gravity_affected.boolean()});

	return 0.0;
}

template<>
template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
CommandReturnValue UseComponentCommand<InstantMovement>::operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
{
	const auto mass = command_system.exec_next();
	const auto friction_x = command_system.exec_next();
	const auto friction_y = command_system.exec_next();
	const auto move_force = command_system.exec_next();

	set_component(entity_system, rendering_system, all_systems, {mass.real(), friction_x.real(), friction_x.real(), move_force.real()});

	return 0.0;
}

template<>
template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
CommandReturnValue UseComponentCommand<BasicCollision>::operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
{
	const auto state = command_system.exec_next();
	const auto elasticity = command_system.exec_next();

	set_component(entity_system, rendering_system, all_systems, {Collision::CollisionState(state.integer()), elasticity.real()});

	return 0.0;
}

template<>
template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
CommandReturnValue UseComponentCommand<DamageCollision>::operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
{
	const auto state = command_system.exec_next();
	const auto damage = command_system.exec_next();

	set_component(entity_system, rendering_system, all_systems, {Collision::CollisionState(state.integer()), damage.real()});

	return 0.0;
}

template<>
template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
CommandReturnValue UseComponentCommand<FullInteraction>::operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
{
	const auto group_vec = command_system.exec_next();
	const auto trigger_group = command_system.exec_next();
	const auto proc_id_self = command_system.exec_next();
	const auto proc_id_other = command_system.exec_next();
	const auto proc_id_self_on_exit = command_system.exec_next();

	set_component(entity_system, rendering_system, all_systems, {int32_t(group_vec.integer()), int8_t(trigger_group.integer()), ProcedureID(proc_id_self.integer()), ProcedureID(proc_id_other.integer()), ProcedureID(proc_id_self_on_exit.integer())});

	return 0.0;
}

template<>
template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
CommandReturnValue UseComponentCommand<NormalInteraction>::operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
{
	const auto group_vec = command_system.exec_next();

	set_component(entity_system, rendering_system, all_systems, {int32_t(group_vec.integer())});

	return 0.0;
}

template<>
template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
CommandReturnValue UseComponentCommand<TriggerInteraction>::operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
{
	const auto trigger_group = command_system.exec_next();
	const auto proc_id_self = command_system.exec_next();
	const auto proc_id_other = command_system.exec_next();
	const auto proc_id_self_on_exit = command_system.exec_next();

	set_component(entity_system, rendering_system, all_systems, {int8_t(trigger_group.integer()), ProcedureID(proc_id_self.integer()), ProcedureID(proc_id_other.integer()), ProcedureID(proc_id_self_on_exit.integer())});

	return 0.0;
}

template<>
template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
CommandReturnValue UseComponentCommand<CharacterHealth>::operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
{
	const auto hp = command_system.exec_next();
	const auto max_hp = command_system.exec_next();

	set_component(entity_system, rendering_system, all_systems, {hp.real(), max_hp.real()});

	return 0.0;
}

class UseAttachedHealthCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	const auto attached_id = command_system.exec_next();
    	const auto offset_hp = command_system.exec_next();
    	const auto offset_max_hp = command_system.exec_next();

		entity_system.set_entity_component(entity_system.previous_entity_id(), all_systems, rendering_system, AttachedHealth<EntitySystemT>{EntityID(attached_id.integer()), offset_hp.real(), offset_max_hp.real(), entity_system});

		return 0.0;
	}
};

template<>
template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
CommandReturnValue UseComponentCommand<TimedHealth>::operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
{
	const auto ttl = command_system.exec_next();
	const auto proc_id = command_system.exec_next();

	set_component(entity_system, rendering_system, all_systems, {ttl.real(), ProcedureID(proc_id.integer())});

	return 0.0;
}

class UseCharacterSoundsCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	const auto idle_id = command_system.exec_next();
    	const auto walk_id = command_system.exec_next();
    	const auto jump_id = command_system.exec_next();
    	const auto fall_id = command_system.exec_next();
    	const auto land_id = command_system.exec_next();
    	const auto attack_id = command_system.exec_next();
    	const auto hit_id = command_system.exec_next();
    	const auto dead_id = command_system.exec_next();
    	const auto volume = command_system.exec_next();
    	const auto self_id = entity_system.previous_entity_id();

		entity_system.set_entity_component(entity_system.previous_entity_id(), all_systems, rendering_system
				, CharacterSounds<EntitySystemT>{SoundID(idle_id.integer())
											   , SoundID(walk_id.integer())
											   , SoundID(jump_id.integer())
											   , SoundID(fall_id.integer())
											   , SoundID(land_id.integer())
											   , SoundID(attack_id.integer())
											   , SoundID(hit_id.integer())
											   , SoundID(dead_id.integer())
											   , volume.real()
											   , self_id
											   , entity_system}
		);

		return 0.0;
	}
};

class UseCharacterVisualsCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	const auto spr_id = command_system.exec_next();
    	const auto self_id = entity_system.previous_entity_id();

		entity_system.set_entity_component(entity_system.previous_entity_id(), all_systems, rendering_system
				, CharacterVisuals<EntitySystemT>{SpritesheetID(spr_id.integer()), self_id, resource_system, entity_system});

		return 0.0;
	}
};

class UseHealthVisualsCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	const auto spr_id = command_system.exec_next();
    	const auto repeat_x = command_system.exec_next();
    	const auto self_id = entity_system.previous_entity_id();

		entity_system.set_entity_component(entity_system.previous_entity_id(), all_systems, rendering_system
				, HealthVisuals<EntitySystemT>{self_id, SpritesheetID(spr_id.integer()), uint16_t(repeat_x.integer()), entity_system});

		return 0.0;
	}
};

class UseMenuItemVisualsCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	const auto spr_id = command_system.exec_next();
    	const auto self_id = entity_system.previous_entity_id();

		entity_system.set_entity_component(entity_system.previous_entity_id(), all_systems, rendering_system
				, MenuItemVisuals<EntitySystemT>{self_id, SpritesheetID(spr_id.integer()), entity_system});

		return 0.0;
	}
};

template<>
template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
CommandReturnValue UseComponentCommand<StaticVisuals>::operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
{
	const auto spr_id = command_system.exec_next();
	const auto sprite = command_system.exec_next();

	set_component(entity_system, rendering_system, all_systems, {SpritesheetID(spr_id.integer()), int(sprite.integer())});

	return 0.0;
}

class UseTiledVisualsCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	const auto spr_id = command_system.exec_next();
    	const auto tile_w = command_system.exec_next();
    	const auto tile_h = command_system.exec_next();
    	const auto self_id = entity_system.previous_entity_id();

		entity_system.set_entity_component(entity_system.previous_entity_id(), all_systems, rendering_system
				, TiledVisuals<EntitySystemT>{SpritesheetID(spr_id.integer()), tile_w.real(), tile_h.real(), self_id, entity_system});

		return 0.0;
	}
};

#endif /* COMMANDS_USE_COMPONENT_COMMAND_H_ */
