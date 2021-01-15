/*
 * command_return_value.h
 *
 *  Created on: Jan 1, 2021
 *      Author: zamfi
 */

#ifndef COMMANDS_COMMAND_RETURN_VALUE_H_
#define COMMANDS_COMMAND_RETURN_VALUE_H_

#include <variant>
#include <string>
#include "../types.h"

// helper type for the visitor
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

struct CommandReturnValue
{
	explicit CommandReturnValue() : value{0.0} {} // @suppress("Symbol is not resolved")
	explicit CommandReturnValue(const int64_t v) : value{v} {} // @suppress("Symbol is not resolved")
	explicit CommandReturnValue(const double v) : value{v} {} // @suppress("Symbol is not resolved")
	explicit CommandReturnValue(std::string v) : value{std::move(v)} {} // @suppress("Symbol is not resolved")

    int64_t operator=(const int64_t v) { value = v; return v; }
    double operator=(const double v) { value = v; return v; }
    std::string_view operator=(std::string v)
    {
    	value = std::move(v); return std::get<std::string>(value);
    }

    bool holds_string() const { return std::holds_alternative<std::string>(value); }
    bool holds_integer() const { return std::holds_alternative<int64_t>(value); }
    bool holds_real() const { return std::holds_alternative<double>(value); }

    std::string string() const
    {
        return std::visit(overloaded { // @suppress("Invalid arguments") // @suppress("Type cannot be resolved")
            [](const int64_t arg) { return std::to_string(arg); },
            [](const double arg) { return std::to_string(arg); },
            [](const std::string& arg) { return arg; },
            }, value);
    }

    int64_t integer() const
    {
        return std::visit(overloaded { // @suppress("Invalid arguments") // @suppress("Type cannot be resolved")
            [](const int64_t arg) { return arg; },
            [](const double arg) { return static_cast<int64_t>(arg); },
            [](const std::string& arg) { return static_cast<int64_t>(arg.size()); },
            }, value);
    }

    bool boolean() const
    {
        return std::visit(overloaded { // @suppress("Invalid arguments") // @suppress("Type cannot be resolved")
            [](const int64_t arg) { return arg != 0; },
            [](const double arg) { return arg != 0.0; },
            [](const std::string& arg) { return arg != ""; },
            }, value);
    }

    double real() const
    {
        return std::visit(overloaded { // @suppress("Invalid arguments") // @suppress("Type cannot be resolved")
            [](const int64_t arg) { return static_cast<double>(arg); },
            [](const double arg) { return arg; },
            [](const std::string& arg) { return static_cast<double>(arg.size()); },
            }, value);
    }

    std::variant<int64_t, double, std::string> value;
};

#endif /* COMMANDS_COMMAND_RETURN_VALUE_H_ */
