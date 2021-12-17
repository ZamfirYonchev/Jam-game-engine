/*
 * literal_value_command.h
 *
 *  Created on: Dec 31, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_LITERAL_VALUE_COMMAND_H_
#define COMMANDS_LITERAL_VALUE_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"

class LiteralValueCommand
{
public:
	explicit LiteralValueCommand(const double value) : m_value{value} {}
	explicit LiteralValueCommand(const int32_t value) : m_value{double(value)} {}
	explicit LiteralValueCommand(std::string_view value) : m_value{std::string{value}} {}
	explicit LiteralValueCommand(const CommandValue& value) : m_value{value} {} // @suppress("Symbol is not resolved")

    CommandValue operator()() const
	{
		return m_value;
	}

private:
    const CommandValue m_value;
};

#endif /* COMMANDS_LITERAL_VALUE_COMMAND_H_ */
