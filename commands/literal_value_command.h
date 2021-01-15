/*
 * literal_value_command.h
 *
 *  Created on: Dec 31, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_LITERAL_VALUE_COMMAND_H_
#define COMMANDS_LITERAL_VALUE_COMMAND_H_

#include "command_return_value.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class LiteralValueCommand
{
public:
	LiteralValueCommand(const double value) : m_value{value} {}
	LiteralValueCommand(const int64_t value) : m_value{value} {}
	LiteralValueCommand(std::string_view value) : m_value{std::string{value}} {}
	LiteralValueCommand(const CommandReturnValue& value) : m_value{value} {}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
		return m_value;
	}

private:
    const CommandReturnValue m_value;
};

#endif /* COMMANDS_LITERAL_VALUE_COMMAND_H_ */
