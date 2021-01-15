/*
 * set_variable_command.h
 *
 *  Created on: Dec 28, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_SET_VARIABLE_COMMAND_H_
#define COMMANDS_SET_VARIABLE_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"
#include "../utilities.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class SetVariableCommand
{
public:
	SetVariableCommand(std::string_view name) : m_hash{hash(name.data())} {}
	SetVariableCommand() : m_hash{0} {}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	if(m_hash == 0)
    	{
    		const auto name = command_system.exec_next();
    		globals.destination_variable_hash = hash(name.string().c_str());
    	}
    	else
        	globals.destination_variable_hash = m_hash;

    	return CommandReturnValue{0.0};
	}

private:
    HashT m_hash;
};

#endif /* COMMANDS_SET_VARIABLE_COMMAND_H_ */
