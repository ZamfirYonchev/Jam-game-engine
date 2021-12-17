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
#include <forward_list>
#include <memory>
#include <iostream>
#include "owning_string_view.h"

// helper type for the visitor
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

struct CommandValue
{
	explicit CommandValue() : value{0.0} {} // @suppress("Symbol is not resolved")
	explicit CommandValue(const double v) : value{v} {} // @suppress("Symbol is not resolved")
	explicit CommandValue(const int32_t v) : value{v} {} // @suppress("Symbol is not resolved")
	explicit CommandValue(std::string v) : value{std::move(v)} {} // @suppress("Symbol is not resolved")
	explicit CommandValue(std::string_view v) : CommandValue{std::string{v}} {} // @suppress("Symbol is not resolved")
	explicit CommandValue(const char* v) : CommandValue{std::string{v}} {} // @suppress("Symbol is not resolved")

    bool holds_real() const { return std::holds_alternative<double>(value); }
    bool holds_integer() const { return std::holds_alternative<int32_t>(value); }
    bool holds_string() const { return std::holds_alternative<std::string>(value); }

    owning_string_view string_view() const &
    {
        return std::visit(overloaded { // @suppress("Invalid arguments") // @suppress("Type cannot be resolved")
            [](const double arg) { return owning_string_view{std::to_string(arg)}; },
            [](const int32_t arg) { return owning_string_view{std::to_string(arg)}; },
            [](const std::string& arg) { return owning_string_view{arg}; },
            }, value);
    }

    std::string string() &&
    {
        return std::visit(overloaded { // @suppress("Invalid arguments") // @suppress("Type cannot be resolved")
            [](const double arg) { return std::to_string(arg); },
            [](const int32_t arg) { return std::to_string(arg); },
            [](std::string& arg) { return std::move(arg); },
            }, value);
    }

    int32_t integer() const
    {
        return std::visit(overloaded { // @suppress("Invalid arguments") // @suppress("Type cannot be resolved")
            [](const double arg) { return static_cast<int32_t>(arg); },
			[](const int32_t arg) { return arg; },
            [](const std::string arg) { return static_cast<int32_t>(arg.size()); },
            }, value);
    }

    bool boolean() const
    {
        return std::visit(overloaded { // @suppress("Invalid arguments") // @suppress("Type cannot be resolved")
            [](const double arg) { return arg != 0.0; },
			[](const int32_t arg) { return arg != 0; },
            [](const std::string arg) { return arg != ""; },
            }, value);
    }

    double real() const
    {
        return std::visit(overloaded { // @suppress("Invalid arguments") // @suppress("Type cannot be resolved")
            [](const double arg) { return arg; },
			[](const int32_t arg) { return double(arg); },
            [](const std::string arg) { return static_cast<double>(arg.size()); },
            }, value);
    }

    std::variant<double, int32_t, std::string> value;
};

#endif /* COMMAND_VALUE_H_ */
