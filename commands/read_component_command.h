/*
 * read_component_command.h
 *
 *  Created on: Jan 21, 2021
 *      Author: zamfi
 */

#ifndef COMMANDS_READ_COMPONENT_COMMAND_H_
#define COMMANDS_READ_COMPONENT_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"
#include "../types.h"
#include "../components/position.h"
#include "../components/control.h"
#include "../components/movement.h"
#include "../components/collision.h"
#include "../components/interaction.h"
#include "../components/health.h"
#include "../components/sounds.h"
#include "../components/visuals.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;

template<typename ComponentT>
class ReadComponentCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	return CommandReturnValue{0.0};
	}
};

template<>
template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
CommandReturnValue ReadComponentCommand<Position>::operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
{
	const auto source_id = command_system.exec_next();
	const auto x_modifier = command_system.exec_next();
	const auto y_modifier = command_system.exec_next();
	const auto w_modifier = command_system.exec_next();
	const auto h_modifier = command_system.exec_next();

	const Position& position = entity_system.entity_component(source_id.integer(), Position::null);

	return CommandReturnValue
			{position.x()*x_modifier.real()
		   + position.y()*y_modifier.real()
		   + position.w()*w_modifier.real()
		   + position.h()*h_modifier.real()
			};
}

template<>
template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
CommandReturnValue ReadComponentCommand<Control>::operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
{
	const auto source_id = command_system.exec_next();
	const auto dec_x_modifier = command_system.exec_next();
	const auto dec_y_modifier = command_system.exec_next();
	const auto dec_attack_modifier = command_system.exec_next();
	const auto look_dir_modifier = command_system.exec_next();
	const auto proc_id_modifier = command_system.exec_next();

	const Control& control = entity_system.entity_component(source_id.integer(), Control::null);

	return CommandReturnValue
			{control.decision_walk()*dec_x_modifier.real()
		   + control.decision_vertical()*dec_y_modifier.real()
		   + control.decision_attack()*dec_attack_modifier.real()
		   + double(control.look_dir())*look_dir_modifier.real()
		   + control.attack_proc_id()*proc_id_modifier.real()
			};
}

template<>
template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
CommandReturnValue ReadComponentCommand<Movement>::operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
{
	const auto source_id = command_system.exec_next();
	const auto mass_modifier = command_system.exec_next();
	const auto fric_x_modifier = command_system.exec_next();
	const auto fric_y_modifier = command_system.exec_next();
	const auto vx_modifier = command_system.exec_next();
	const auto vy_modifier = command_system.exec_next();
	const auto fx_modifier = command_system.exec_next();
	const auto fy_modifier = command_system.exec_next();
	const auto gravity_modifier = command_system.exec_next();

	const Movement& movement = entity_system.entity_component(source_id.integer(), Movement::null);

	return CommandReturnValue
			{movement.mass()*mass_modifier.real()
		   + movement.friction_x()*fric_x_modifier.real()
		   + movement.friction_y()*fric_y_modifier.real()
		   + movement.vx()*vx_modifier.real()
		   + movement.vy()*vy_modifier.real()
		   + movement.fx()*fx_modifier.real()
		   + movement.fy()*fy_modifier.real()
		   + movement.gravity_affected()*gravity_modifier.real()
			};
}

template<>
template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
CommandReturnValue ReadComponentCommand<Collision>::operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
{
	const auto source_id = command_system.exec_next();
	const auto state_modifier = command_system.exec_next();
	const auto standing_on_modifier = command_system.exec_next();
	const auto damage_modifier = command_system.exec_next();
	const auto elasticity_modifier = command_system.exec_next();

	const Collision& collision = entity_system.entity_component(source_id.integer(), Collision::null);

	return CommandReturnValue
			{double(collision.state())*state_modifier.real()
		   + double(collision.standing_on())*standing_on_modifier.real()
		   + collision.on_collision_damage()*damage_modifier.real()
		   + collision.elasticity()*elasticity_modifier.real()
			};
}

template<>
template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
CommandReturnValue ReadComponentCommand<Interaction>::operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
{
	const auto source_id = command_system.exec_next();
	const auto group_vector_modifier = command_system.exec_next();
	const auto trigger_group_modifier = command_system.exec_next();
	const auto proc_id_self_modifier = command_system.exec_next();
	const auto proc_id_other_modifier = command_system.exec_next();
	const auto on_exit_proc_id_self_modifier = command_system.exec_next();

	const Interaction& interaction = entity_system.entity_component(source_id.integer(), Interaction::null);

	return (group_vector_modifier.real() == 1.0 &&
			(trigger_group_modifier.real()
		   + proc_id_self_modifier.real()
		   + proc_id_other_modifier.real()
		   + on_exit_proc_id_self_modifier.real()
		   ) == 0)
		   ?
			CommandReturnValue{static_cast<int64_t>(interaction.group_vector())}
		   :
			CommandReturnValue
			{interaction.group_vector()*group_vector_modifier.real()
		   + interaction.proc_id_self()*proc_id_self_modifier.real()
		   + interaction.proc_id_other()*proc_id_other_modifier.real()
		   + interaction.on_exit_proc_id_self()*on_exit_proc_id_self_modifier.real()
			};
}

template<>
template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
CommandReturnValue ReadComponentCommand<Health>::operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
{
	const auto source_id = command_system.exec_next();
	const auto hp_modifier = command_system.exec_next();
	const auto max_hp_modifier = command_system.exec_next();
	const auto proc_id_modifier = command_system.exec_next();

	const Health& health = entity_system.entity_component(source_id.integer(), Health::null);

	return CommandReturnValue
			{health.hp()*hp_modifier.real()
		   + health.max_hp()*max_hp_modifier.real()
		   + health.on_death_exec()*proc_id_modifier.real()
			};
}


template<>
template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
CommandReturnValue ReadComponentCommand<Sounds>::operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
{
	const auto source_id = command_system.exec_next();
	const auto sound_id_modifier = command_system.exec_next();
	const auto changed_modifier = command_system.exec_next();

	const Sounds& sounds = entity_system.entity_component(source_id.integer(), Sounds::null);

	return CommandReturnValue
			{sounds.id()*sound_id_modifier.real()
		   + sounds.changed()*changed_modifier.real()
			};
}

template<>
template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
CommandReturnValue ReadComponentCommand<Visuals>::operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
{
	const auto source_id = command_system.exec_next();
	const auto repeat_x_modifier = command_system.exec_next();
	const auto repeat_y_modifier = command_system.exec_next();
	const auto layer_modifier = command_system.exec_next();

	const Visuals& visuals = entity_system.entity_component(source_id.integer(), Visuals::null);

	return CommandReturnValue
			{visuals.repeat_x()*repeat_x_modifier.real()
		   + visuals.repeat_y()*repeat_y_modifier.real()
		   + double(visuals.layer())*layer_modifier.real()
			};
}

#endif /* COMMANDS_READ_COMPONENT_COMMAND_H_ */
