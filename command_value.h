/*
 * command_value.h
 *
 *  Created on: Dec 12, 2021
 *      Author: zamfi
 */

#ifndef COMMAND_VALUE_H_
#define COMMAND_VALUE_H_


#include <variant>
#include <string>
#include "cinttypes"

// helper type for the visitor
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

struct CommandValue
{
	explicit CommandValue() : value{0.0} {} // @suppress("Symbol is not resolved")
	explicit CommandValue(const double v) : value{v} {} // @suppress("Symbol is not resolved")
	explicit CommandValue(const int32_t v, int) : value{double(v)} {} // @suppress("Symbol is not resolved")
	explicit CommandValue(std::string v) : value{std::move(v)} {} // @suppress("Symbol is not resolved")
	explicit CommandValue(const char* v) : CommandValue{std::string{v}} {} // @suppress("Symbol is not resolved")

    bool holds_string() const { return std::holds_alternative<std::string>(value); }
    bool holds_number() const { return std::holds_alternative<double>(value); }

    std::string string() const
    {
        return std::visit(overloaded { // @suppress("Invalid arguments") // @suppress("Type cannot be resolved")
            [](const double arg) { return std::to_string(arg); },
            [](const std::string& arg) { return arg; },
            }, value);
    }

    int integer() const
    {
        return std::visit(overloaded { // @suppress("Invalid arguments") // @suppress("Type cannot be resolved")
            [](const double arg) { return static_cast<int>(arg); },
            [](const std::string& arg) { return static_cast<int>(arg.size()); },
            }, value);
    }

    bool boolean() const
    {
        return std::visit(overloaded { // @suppress("Invalid arguments") // @suppress("Type cannot be resolved")
            [](const double arg) { return arg != 0.0; },
            [](const std::string& arg) { return arg != ""; },
            }, value);
    }

    double real() const
    {
        return std::visit(overloaded { // @suppress("Invalid arguments") // @suppress("Type cannot be resolved")
            [](const double arg) { return arg; },
            [](const std::string& arg) { return static_cast<double>(arg.size()); },
            }, value);
    }

    std::variant<double, std::string> value;
};

#endif /* COMMAND_VALUE_H_ */
