/*
 * set_level_command.h
 *
 *  Created on: Dec 9, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_SET_LEVEL_COMMAND_H_
#define COMMANDS_SET_LEVEL_COMMAND_H_

#include <string>
#include "../globals.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class SetLevelCommand
{
public:
	SetLevelCommand(const std::string& level)
	: m_level(level)
	{}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
		globals.level_name = m_level;
	}

private:
    std::string m_level;
};




#endif /* COMMANDS_SET_LEVEL_COMMAND_H_ */
