/*
 * use_component_command.h
 *
 *  Created on: Jul 1, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_COMPONENT_COMMAND_H_
#define COMMANDS_USE_COMPONENT_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include "../types.h"
#include "../components/visuals.h"

template< typename EntitySystemT
		, typename AllSystemsT
		, typename RenderingSystemT
		, typename CommandSystemT
		>
struct UseComponentCommandGenerator
{
	EntitySystemT& entity_system;
	AllSystemsT& all_systems;
	RenderingSystemT& rendering_system;
	CommandSystemT& command_system;
	Globals& globals;

	UseComponentCommandGenerator
	( EntitySystemT& _entity_system
	, AllSystemsT& _all_systems
	, RenderingSystemT& _rendering_system
	, CommandSystemT& _command_system
	, Globals& _globals
	)
	: entity_system{_entity_system}
	, all_systems{_all_systems}
	, rendering_system{_rendering_system}
	, command_system{_command_system}
	, globals{_globals}
	{}

	template<typename ComponentT, typename ConcreteComponentT, typename... Ts>
	auto make(Ts&&... ts)
	{
		return [&]()
			   {
					const EntityID selected_entity = globals(Globals::selected_entity).integer();
					int8_t change;
					const auto& component = entity_system.set_entity_component( selected_entity
																			  , ComponentT
																			    { ConcreteComponentT
																				  {std::forward<Ts>(ts)...}
																			    }
																			  , change
																			  );

					all_systems.component_updated(component, selected_entity, change);
					rendering_system.component_updated(component, selected_entity, change);

			    	return CommandValue{selected_entity};
			   };
	}
};

#endif /* COMMANDS_USE_COMPONENT_COMMAND_H_ */
