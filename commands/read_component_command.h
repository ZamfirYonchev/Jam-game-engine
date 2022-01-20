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

template<typename CommandSystemT, typename EntitySystemT, typename PositionT>
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
		const EntityID source_id = command_system.exec_next();
		const double x_modifier = command_system.exec_next();
		const double y_modifier = command_system.exec_next();
		const double w_modifier = command_system.exec_next();
		const double h_modifier = command_system.exec_next();

		const auto& position = entity_system.template entity_component<PositionT>(source_id);

		return CommandValue
				{position.x()*x_modifier
			   + position.y()*y_modifier
			   + position.w()*w_modifier
			   + position.h()*h_modifier
				};
	}
};

template<typename CommandSystemT, typename EntitySystemT, typename ControlT>
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
		const EntityID source_id = command_system.exec_next();
		const double dec_x_modifier = command_system.exec_next();
		const double dec_y_modifier = command_system.exec_next();
		const double dec_attack_modifier = command_system.exec_next();
		const double look_dir_modifier = command_system.exec_next();
		const double proc_id_modifier = command_system.exec_next();

		const auto& control = entity_system.template entity_component<ControlT>(source_id);

		return CommandValue
				{control.decision_walk()*dec_x_modifier
			   + control.decision_vertical()*dec_y_modifier
			   + control.decision_attack()*dec_attack_modifier
			   + double(control.look_dir())*look_dir_modifier
			   + control.attack_proc_id()*proc_id_modifier
				};
	}
};

template<typename CommandSystemT, typename EntitySystemT, typename MovementT>
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
		const EntityID source_id = command_system.exec_next();
		const double mass_modifier = command_system.exec_next();
		const double fric_x_modifier = command_system.exec_next();
		const double fric_y_modifier = command_system.exec_next();
		const double vx_modifier = command_system.exec_next();
		const double vy_modifier = command_system.exec_next();
		const double fx_modifier = command_system.exec_next();
		const double fy_modifier = command_system.exec_next();
		const double gravity_modifier = command_system.exec_next();

		const auto& movement = entity_system.template entity_component<MovementT>(source_id);

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

template<typename CommandSystemT, typename EntitySystemT, typename CollisionT>
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
		const EntityID source_id = command_system.exec_next();
		const double state_modifier = command_system.exec_next();
		const double standing_on_modifier = command_system.exec_next();
		const double damage_modifier = command_system.exec_next();
		const double elasticity_modifier = command_system.exec_next();

		const auto& collision = entity_system.template entity_component<CollisionT>(source_id);

		return CommandValue
				{double(collision.solid())*state_modifier
			   + double(collision.standing_on())*standing_on_modifier
			   + collision.on_collision_damage()*damage_modifier
			   + collision.elasticity()*elasticity_modifier
				};
	}
};

template<typename CommandSystemT, typename EntitySystemT, typename InteractionT>
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
		const EntityID source_id = command_system.exec_next();
		const double group_vector_modifier = command_system.exec_next();
		const double trigger_group_modifier = command_system.exec_next();
		const double proc_id_self_modifier = command_system.exec_next();
		const double proc_id_other_modifier = command_system.exec_next();
		const double on_exit_proc_id_self_modifier = command_system.exec_next();

		const auto& interaction = entity_system.template entity_component<InteractionT>(source_id);

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

template<typename CommandSystemT, typename EntitySystemT, typename HealthT>
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
		const EntityID source_id = command_system.exec_next();
		const double hp_modifier = command_system.exec_next();
		const double max_hp_modifier = command_system.exec_next();
		const double proc_id_modifier = command_system.exec_next();

		const auto& health = entity_system.template entity_component<HealthT>(source_id);

		return CommandValue
				{health.hp()*hp_modifier
			   + health.max_hp()*max_hp_modifier
			   + health.on_death_exec()*proc_id_modifier
				};
	}
};


template<typename CommandSystemT, typename EntitySystemT, typename SoundsT>
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
		const EntityID source_id = command_system.exec_next();
		const double sound_id_modifier = command_system.exec_next();
		const double changed_modifier = command_system.exec_next();

		const auto& sounds = entity_system.template entity_component<SoundsT>(source_id);

		return CommandValue
				{sounds.id()*sound_id_modifier
			   + sounds.changed()*changed_modifier
				};
	}
};

template<typename CommandSystemT, typename EntitySystemT, typename VisualsT>
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
		const EntityID source_id = command_system.exec_next();
		const double repeat_x_modifier = command_system.exec_next();
		const double repeat_y_modifier = command_system.exec_next();
		const double layer_modifier = command_system.exec_next();

		const auto& visuals = entity_system.template entity_component<VisualsT>(source_id);

		return CommandValue
				{visuals.repeat_x()*repeat_x_modifier
			   + visuals.repeat_y()*repeat_y_modifier
			   + double(visuals.layer())*layer_modifier
				};
	}
};

#endif /* COMMANDS_READ_COMPONENT_COMMAND_H_ */
