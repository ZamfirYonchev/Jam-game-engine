/*
 * read_component_command.h
 *
 *  Created on: Jan 21, 2021
 *      Author: zamfi
 */

#ifndef COMMANDS_READ_COMPONENT_COMMAND_H_
#define COMMANDS_READ_COMPONENT_COMMAND_H_

#include "../command_value.h"
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

template<typename CommandSystemT, typename EntitySystemT>
class ReadPositionCommand
{
public:
	CommandSystemT& command_system;
	EntitySystemT& entity_system;

	ReadPositionCommand(CommandSystemT& _command_system, EntitySystemT& _entity_system)
	: command_system{_command_system}
	, entity_system{_entity_system}
	{}

	CommandValue operator()() const
	{
		const auto source_id = command_system.exec_next().integer();
		const auto x_modifier = command_system.exec_next().real();
		const auto y_modifier = command_system.exec_next().real();
		const auto w_modifier = command_system.exec_next().real();
		const auto h_modifier = command_system.exec_next().real();

		const Position& position = entity_system.template entity_component<Position>(source_id);

		return CommandValue
				{position.x()*x_modifier
			   + position.y()*y_modifier
			   + position.w()*w_modifier
			   + position.h()*h_modifier
				};
	}
};

template<typename CommandSystemT, typename EntitySystemT>
class ReadControlCommand
{
public:
	CommandSystemT& command_system;
	EntitySystemT& entity_system;

	ReadControlCommand(CommandSystemT& _command_system, EntitySystemT& _entity_system)
	: command_system{_command_system}
	, entity_system{_entity_system}
	{}

	CommandValue operator()() const
	{
		const auto source_id = command_system.exec_next().integer();
		const auto dec_x_modifier = command_system.exec_next().real();
		const auto dec_y_modifier = command_system.exec_next().real();
		const auto dec_attack_modifier = command_system.exec_next().real();
		const auto look_dir_modifier = command_system.exec_next().real();
		const auto proc_id_modifier = command_system.exec_next().real();

		const Control& control = entity_system.template entity_component<Control>(source_id);

		return CommandValue
				{control.decision_walk()*dec_x_modifier
			   + control.decision_vertical()*dec_y_modifier
			   + control.decision_attack()*dec_attack_modifier
			   + double(control.look_dir())*look_dir_modifier
			   + control.attack_proc_id()*proc_id_modifier
				};
	}
};

template<typename CommandSystemT, typename EntitySystemT>
class ReadMovementCommand
{
public:
	CommandSystemT& command_system;
	EntitySystemT& entity_system;

	ReadMovementCommand(CommandSystemT& _command_system, EntitySystemT& _entity_system)
	: command_system{_command_system}
	, entity_system{_entity_system}
	{}

	CommandValue operator()() const
	{
		const auto source_id = command_system.exec_next().integer();
		const auto mass_modifier = command_system.exec_next().real();
		const auto fric_x_modifier = command_system.exec_next().real();
		const auto fric_y_modifier = command_system.exec_next().real();
		const auto vx_modifier = command_system.exec_next().real();
		const auto vy_modifier = command_system.exec_next().real();
		const auto fx_modifier = command_system.exec_next().real();
		const auto fy_modifier = command_system.exec_next().real();
		const auto gravity_modifier = command_system.exec_next().real();

		const Movement& movement = entity_system.template entity_component<Movement>(source_id);

		return CommandValue
				{movement.mass()*mass_modifier
			   + movement.friction_x()*fric_x_modifier
			   + movement.friction_y()*fric_y_modifier
			   + movement.vx()*vx_modifier
			   + movement.vy()*vy_modifier
			   + movement.fx()*fx_modifier
			   + movement.fy()*fy_modifier
			   + movement.gravity_affected()*gravity_modifier
				};
	}
};

template<typename CommandSystemT, typename EntitySystemT>
class ReadCollisionCommand
{
public:
	CommandSystemT& command_system;
	EntitySystemT& entity_system;

	ReadCollisionCommand(CommandSystemT& _command_system, EntitySystemT& _entity_system)
	: command_system{_command_system}
	, entity_system{_entity_system}
	{}

	CommandValue operator()() const
	{
		const auto source_id = command_system.exec_next().integer();
		const auto state_modifier = command_system.exec_next().real();
		const auto standing_on_modifier = command_system.exec_next().real();
		const auto damage_modifier = command_system.exec_next().real();
		const auto elasticity_modifier = command_system.exec_next().real();

		const Collision& collision = entity_system.template entity_component<Collision>(source_id);

		return CommandValue
				{double(collision.solid())*state_modifier
			   + double(collision.standing_on())*standing_on_modifier
			   + collision.on_collision_damage()*damage_modifier
			   + collision.elasticity()*elasticity_modifier
				};
	}
};

template<typename CommandSystemT, typename EntitySystemT>
class ReadInteractionCommand
{
public:
	CommandSystemT& command_system;
	EntitySystemT& entity_system;

	ReadInteractionCommand(CommandSystemT& _command_system, EntitySystemT& _entity_system)
	: command_system{_command_system}
	, entity_system{_entity_system}
	{}

	CommandValue operator()() const
	{
		const auto source_id = command_system.exec_next().integer();
		const auto group_vector_modifier = command_system.exec_next().real();
		const auto trigger_group_modifier = command_system.exec_next().real();
		const auto proc_id_self_modifier = command_system.exec_next().real();
		const auto proc_id_other_modifier = command_system.exec_next().real();
		const auto on_exit_proc_id_self_modifier = command_system.exec_next().real();

		const Interaction& interaction = entity_system.template entity_component<Interaction>(source_id);

		return (group_vector_modifier == 1.0
			 && trigger_group_modifier == 0.0
			 && proc_id_self_modifier == 0.0
			 && proc_id_other_modifier == 0.0
			 && on_exit_proc_id_self_modifier == 0.0
			   )
			   ?
				CommandValue{interaction.group_vector()}
			   :
				CommandValue
				{interaction.group_vector()*group_vector_modifier
			   + interaction.proc_id_self()*proc_id_self_modifier
			   + interaction.proc_id_other()*proc_id_other_modifier
			   + interaction.on_exit_proc_id_self()*on_exit_proc_id_self_modifier
				};
	}
};

template<typename CommandSystemT, typename EntitySystemT>
class ReadHealthCommand
{
public:
	CommandSystemT& command_system;
	EntitySystemT& entity_system;

	ReadHealthCommand(CommandSystemT& _command_system, EntitySystemT& _entity_system)
	: command_system{_command_system}
	, entity_system{_entity_system}
	{}

	CommandValue operator()() const
	{
		const auto source_id = command_system.exec_next().integer();
		const auto hp_modifier = command_system.exec_next().real();
		const auto max_hp_modifier = command_system.exec_next().real();
		const auto proc_id_modifier = command_system.exec_next().real();

		const Health& health = entity_system.template entity_component<Health>(source_id);

		return CommandValue
				{health.hp()*hp_modifier
			   + health.max_hp()*max_hp_modifier
			   + health.on_death_exec()*proc_id_modifier
				};
	}
};


template<typename CommandSystemT, typename EntitySystemT>
class ReadSoundsCommand
{
public:
	CommandSystemT& command_system;
	EntitySystemT& entity_system;

	ReadSoundsCommand(CommandSystemT& _command_system, EntitySystemT& _entity_system)
	: command_system{_command_system}
	, entity_system{_entity_system}
	{}

	CommandValue operator()() const
	{
		const auto source_id = command_system.exec_next().integer();
		const auto sound_id_modifier = command_system.exec_next().real();
		const auto changed_modifier = command_system.exec_next().real();

		const Sounds& sounds = entity_system.template entity_component<Sounds>(source_id);

		return CommandValue
				{sounds.id()*sound_id_modifier
			   + sounds.changed()*changed_modifier
				};
	}
};

template<typename CommandSystemT, typename EntitySystemT>
class ReadVisualsCommand
{
public:
	CommandSystemT& command_system;
	EntitySystemT& entity_system;

	ReadVisualsCommand(CommandSystemT& _command_system, EntitySystemT& _entity_system)
	: command_system{_command_system}
	, entity_system{_entity_system}
	{}

	CommandValue operator()() const
	{
		const auto source_id = command_system.exec_next().integer();
		const auto repeat_x_modifier = command_system.exec_next().real();
		const auto repeat_y_modifier = command_system.exec_next().real();
		const auto layer_modifier = command_system.exec_next().real();

		const Visuals& visuals = entity_system.template entity_component<Visuals>(source_id);

		return CommandValue
				{visuals.repeat_x()*repeat_x_modifier
			   + visuals.repeat_y()*repeat_y_modifier
			   + double(visuals.layer())*layer_modifier
				};
	}
};

#endif /* COMMANDS_READ_COMPONENT_COMMAND_H_ */
