/*
 * command_system.h
 *
 *  Created on: Oct 7, 2020
 *      Author: zamfi
 */

#ifndef SYSTEMS_COMMAND_SYSTEM_H_
#define SYSTEMS_COMMAND_SYSTEM_H_

#include <unordered_map>
#include <list>
#include <functional>
#include "../utilities.h"
#include "../commands/null_command.h"
#include <iostream>
#include <string>
#include <vector>
#include "../commands/procedure_command.h"
#include "../commands/select_entity_command.h"
#include "../commands/call_procedure_command.h"
#include "../commands/set_variable_command.h"
#include "../optional_ref.h"
#include <utility>
#include <optional>
#include "../commands/command_return_value.h"
#include "../commands/get_variable_command.h"
#include "../commands/literal_value_command.h"
#include "../commands/extend_procedure_command.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

template<typename EntitySystemT, typename AllSystemsT>
class CommandSystem
{
public:
	using CommandT = std::function<CommandReturnValue(CommandSystem& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals)>;
	using ParserT = std::function<CommandT(std::istream&)>;

    CommandSystem(EntitySystemT& entity_system
    			, ResourceSystem& resource_system
    			, InputSystem& input_system
    			, RenderingSystem& rendering_system
    			, AllSystemsT& all_systems
    			, Globals& globals
				)
	: m_procedure_calls{}
    , m_commands{}
	, m_entity_system{entity_system}
	, m_resource_system{resource_system}
	, m_input_system{input_system}
	, m_rendering_system{rendering_system}
	, m_all_systems{all_systems}
	, m_globals{globals}
	{
		m_procedures.emplace_back(); //insert one empty procedure with id 0
	}

    CommandSystem(const CommandSystem& ) = delete;
    CommandSystem& operator=(const CommandSystem& ) = delete;

    CommandSystem(CommandSystem&& rhs) noexcept = default;

    CommandSystem& operator=(CommandSystem&& rhs) noexcept
    {
    	clear();
    	m_commands = std::move(rhs.m_commands);
    	return *this;
    }

    int size() const { return m_commands.size(); }

    const CommandReturnValue& variable(const HashT name_hash) const
    {
    	if(m_variables.find(name_hash) == cend(m_variables))
    		std::cerr << "Accessing an uninitialized variable at " << std::hex << name_hash << std::dec << std::endl;

    	return m_variables[name_hash];
    }

    CommandReturnValue set_variable(const HashT name_hash, const CommandReturnValue& value)
    {
    	return std::exchange(m_variables[name_hash], value);
    }

    void process(ResourceSystem& resource_system, RenderingSystem& rendering_system, InputSystem& input_system, Globals& globals)
    {
    	while(m_procedure_calls.size() > 0)
    	{
    		const auto& pair = m_procedure_calls.front();
    		m_commands.emplace_back(SelectEntityCommand{pair.first});
    		m_commands.emplace_back(CallProcedureCommand{pair.second});
    		m_procedure_calls.pop_front();
    	}

        while(m_commands.size() > 0)
        {
            const bool update_variable = globals.destination_variable_hash.has_value();
            const CommandReturnValue result = exec_next();
            if(update_variable)
            {
            	std::cout << "PARSER: Updating variable to " << result.real() << '\n';
            	m_variables[*globals.destination_variable_hash] = result;
            	globals.destination_variable_hash = std::nullopt;
            }
        }
    }

    void process_stream(std::istream& input)
    {
    	std::list<CommandT> commands;
    	auto procedure_size_insert_it = end(m_commands);

        while(input.good())
        {
        	const char next_char = input.peek();

        	switch(next_char)
        	{
        		case '#':
        		{
                	std::string line;
                    std::getline(input, line);
                    std::cout << "PARSER: Reading comment: " << line << '\n';
        		}
				break;

        		case '@':
        		{
                	std::string var_name;
                	input.get(); //extract the @ char
                	input >> var_name;
                	commands.push_back(SetVariableCommand{var_name});
                    std::cout << "PARSER: Setting variable \"" << var_name << "\"\n";
        		}
				break;

        		case '*':
        		{
                	std::string var_name;
                	input.get(); //extract the * char
                	input >> var_name;
                    std::cout << "PARSER: Reading variable \"" << var_name << "\"\n";
                	commands.push_back(GetVariableCommand{var_name});
        		}
				break;

        		case '"':
        		{
                	std::string str;
                	input.get(); //extract the " char
                	std::getline(input, str, '"');
                    std::cout << "PARSER: Reading string \"" << str << "\"\n";
                	commands.push_back(LiteralValueCommand{str});
        		}
				break;

        		case '(':
        		{
                	std::string str;
                	input.get(); //extract the ( char
                	std::getline(input, str, ')');
                    std::cout << "PARSER: Calling command \"" << str << "\"\n";
                	commands.push_back(CallProcedureCommand{str});
        		}
				break;

        		case '-': case '0': case '1': case '2': case '3': case '4':
        		case '5': case '6': case '7': case '8': case '9':
        		{
                	double value;
                	input >> value;

                	if(input.fail())
                		std::cerr << "Error trying to read scalar value beginning with " << next_char << std::endl;
                	else
                	{
    					std::cout << "PARSER: Reading scalar " << value << '\n';
                    	commands.push_back(LiteralValueCommand{value});
                	}
        		}
				break;

        		case '{':
        		{
                	input.get(); //extract the { char
                    std::cout << "PARSER: Declaring new procedure\n";
                	commands.push_back(ExtendProcedureCommand{});
                	commands.push_back(LiteralValueCommand{int64_t(m_procedures.size())});
                	commands.push_back(NullCommand{}); //reserve space for procedure size

                    procedure_size_insert_it = std::prev(commands.end());

                	m_procedures.emplace_back();
        		}
				break;

        		case '}':
        		{
                	input.get(); //extract the } char

                	if(procedure_size_insert_it != end(m_commands))
                	{
                		const auto proc_size = std::distance(procedure_size_insert_it, end(commands)) - 1;
						*procedure_size_insert_it = LiteralValueCommand{proc_size};
						procedure_size_insert_it = end(m_commands);
	                    std::cout << "PARSER: Closing procedure\n";
                	}
                	else
                	{
                		std::cerr << "Missing {\n";
                	}
        		}
				break;

        		default:
        		{
                	std::string token;
                	input >> token;
                	std::cout << "PARSER: Reading command " << token << '\n';

                	const auto it = m_command_prototypes.find(hash(token.c_str()));
                	if(it != cend(m_command_prototypes))
                    	commands.push_back(it->second);
                	else
                		std::cerr << "Trying to execute a non-registered command " << token << std::endl;
        		}
				break;
        	}

            input >> std::ws; //consume whitespaces
        }

        std::copy(cbegin(commands), cend(commands), std::inserter(m_commands, begin(m_commands)));
    }

    void insert_front(const CommandT& cmd)
    {
		m_commands.push_front(cmd);
    }

    void push(const CommandT& cmd)
    {
		m_commands.push_back(cmd);
    }

    CommandT pop_next()
    {
    	if(m_commands.size() > 0)
    	{
    		const CommandT cmd {std::move(m_commands.front())};
            m_commands.pop_front();
            return cmd;
    	}
    	else
    		return NullCommand{};
    }

    CommandReturnValue exec_next()
    {
    	return pop_next()(*this, m_entity_system, m_resource_system, m_input_system, m_rendering_system, m_all_systems, m_globals);
    }

    void clear()
    {
    	flush_commands();
        clear_procedures();
        m_commands.clear();
        m_command_prototypes.clear();
    }

    void flush_commands()
    {
        for(auto& cmd  : m_commands)
        	cmd = NullCommand{};
    }

    void register_command(std::string_view name, const CommandT& function)
    {
    	const auto str_hash = hash(name.data());
    	const auto it = m_command_prototypes.find(str_hash);
    	if(it != cend(m_command_prototypes))
    	{
    		std::cerr << "Command " << name << " already registered. Overwriting...\n";
    		it->second = function;
    	}
    	else
    		m_command_prototypes[str_hash] = function;
    }

    void unregister_command(std::string_view name)
    {
    	const auto it = m_command_prototypes.find(hash(name.data()));
    	if(it == cend(m_command_prototypes))
    		std::cerr << "Trying to remove non-existing command " << name << ".\n";
    	else
    		m_command_prototypes.erase(it);
    }

    ProcedureCommand<CommandSystem>& procedure(const ProcedureID id)
    {
    	const ProcedureID proc_id = std::max(0, id*(1 - (id >= static_cast<ProcedureID>(m_procedures.size()))));
		return m_procedures[proc_id];
    }

    void clear_procedures()
    {
        m_procedures.clear();
        m_procedures.emplace_back(); //insert an empty procedure at id 0
    }

    std::list<std::pair<EntityID, ProcedureID>>& procedure_calls()
	{
    	return m_procedure_calls;
	}

private:
	std::list<std::pair<EntityID, ProcedureID>> m_procedure_calls;
    std::list<CommandT> m_commands;
    std::unordered_map<HashT, CommandT> m_command_prototypes;
    std::vector<ProcedureCommand<CommandSystem>> m_procedures;

    mutable std::unordered_map<HashT, CommandReturnValue> m_variables;

	EntitySystemT& m_entity_system;
	ResourceSystem& m_resource_system;
    InputSystem& m_input_system;
    RenderingSystem& m_rendering_system;
    AllSystemsT& m_all_systems;
    Globals& m_globals;
};


#endif /* SYSTEMS_COMMAND_SYSTEM_H_ */
