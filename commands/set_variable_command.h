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

class SetVariableCommand
{
public:
	SetVariableCommand(const HashT name_hash) : m_hash{name_hash} {}
	SetVariableCommand() : m_hash{0} {}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	HashT name_hash = m_hash;
    	if(m_hash == 0)
    	{
    		const auto name = command_system.exec_next();
    		name_hash = hash(name.string().c_str());
    	}

    	const CommandReturnValue result = command_system.exec_next();
    	globals(name_hash) = result;

    	return result;
	}

private:
    HashT m_hash;
};

#endif /* COMMANDS_SET_VARIABLE_COMMAND_H_ */
