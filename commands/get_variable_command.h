/*
 * get_variable_command.h
 *
 *  Created on: Jan 11, 2021
 *      Author: zamfi
 */

#ifndef COMMANDS_GET_VARIABLE_COMMAND_H_
#define COMMANDS_GET_VARIABLE_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"
#include "../utilities.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;

class GetVariableCommand
{
public:
	GetVariableCommand(std::string_view name) : m_hash{hash(name.data())} {}
	GetVariableCommand() : m_hash{0} {}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	if(m_hash == 0)
    	{
    		const auto name = command_system.exec_next();
    		return globals(name.string());
    	}
    	else
    		return globals(m_hash);
	}

private:
    HashT m_hash;
};

#endif /* COMMANDS_GET_VARIABLE_COMMAND_H_ */
