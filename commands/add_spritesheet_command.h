/*
 * add_spritesheet_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_SPRITESHEET_COMMAND_H_
#define COMMANDS_ADD_SPRITESHEET_COMMAND_H_

#include "command_return_value.h"
#include "../spritesheet.h"
#include "../systems/resource_system.h"
#include "../globals.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

//TODO to remove
class AddSpritesheetCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
        const auto idle_start = command_system.exec_next();
    	const auto idle_size = command_system.exec_next();
    	const auto walk_start = command_system.exec_next();
    	const auto walk_size = command_system.exec_next();
    	const auto jump_start = command_system.exec_next();
    	const auto jump_size = command_system.exec_next();
    	const auto fall_start = command_system.exec_next();
    	const auto fall_size = command_system.exec_next();
    	const auto attack_start = command_system.exec_next();
    	const auto attack_size = command_system.exec_next();
    	const auto hit_start = command_system.exec_next();
    	const auto hit_size = command_system.exec_next();
    	const auto dead_start = command_system.exec_next();
    	const auto dead_size = command_system.exec_next();
    	const auto scale_factor = command_system.exec_next();

		globals.access_spritesheet_id = resource_system.addNewSpritesheet({uint8_t(idle_start.integer())
																		 , uint8_t(idle_size.integer())
																		 , uint8_t(walk_start.integer())
																		 , uint8_t(walk_size.integer())
																		 , uint8_t(jump_start.integer())
																		 , uint8_t(jump_size.integer())
																		 , uint8_t(fall_start.integer())
																		 , uint8_t(fall_size.integer())
																		 , uint8_t(attack_start.integer())
																		 , uint8_t(attack_size.integer())
																		 , uint8_t(hit_start.integer())
																		 , uint8_t(hit_size.integer())
																		 , uint8_t(dead_start.integer())
																		 , uint8_t(dead_size.integer())
																		 , scale_factor.real()
																		 });
    	return CommandReturnValue{static_cast<int64_t>(globals.access_spritesheet_id)};
    }
};

#endif /* COMMANDS_ADD_SPRITESHEET_COMMAND_H_ */
