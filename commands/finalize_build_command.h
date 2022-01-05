/*
 * finalize_build_command.h
 *
 *  Created on: Oct 24, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_FINALIZE_BUILD_COMMAND_H_
#define COMMANDS_FINALIZE_BUILD_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include "../types.h"
#include "../components/absolute_position.h"

template<typename EntitySystemT, typename AllSystemsT, typename PositionT>
class FinalizeBuildCommand
{
public:
	EntitySystemT& entity_system;
	AllSystemsT& all_systems;
	Globals& globals;

	FinalizeBuildCommand(EntitySystemT& _entity_system, AllSystemsT& _all_systems, Globals& _globals)
	: entity_system{_entity_system}
	, all_systems{_all_systems}
	, globals{_globals}
	{}

    CommandValue operator()() const
	{
    	const EntityID selected_entity = globals(Globals::selected_entity).integer();
		const auto& position = entity_system.template entity_component<PositionT>(selected_entity);
		int8_t change;
		const auto& component = entity_system.set_entity_component( selected_entity
												  	  	  	  	  , PositionT
																	{ AbsolutePosition
																	  { position.x()
																	  , position.y()
																	  , position.w()
																	  , position.h()
																	  }
																	}
																  , change
																  );

		all_systems.component_updated(component, selected_entity, change);

		return globals(Globals::selected_entity);
	}
};

#endif /* COMMANDS_FINALIZE_BUILD_COMMAND_H_ */
