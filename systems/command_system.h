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
#include <sstream>
#include <vector>
#include "../commands/procedure.h"
#include "../commands/debug_message_command.h"
#include "../commands/select_entity_command.h"
#include "../commands/call_procedure_command.h"
#include "../commands/set_fixed_variable_command.h"
#include "../commands/get_fixed_variable_command.h"
#include "../commands/literal_value_command.h"
#include "../commands/extend_procedure_command.h"
#include "../types.h"
#include <utility>
#include "../command_value.h"
#include "../globals.h"
#include <iomanip>

class CommandSystem
{
public:
	using CommandT = std::function<CommandValue()>;

    CommandSystem(Globals& globals)
	: m_globals{globals}
	{
		initialize_default_procedures();
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

    void process()
    {
		parse(m_external_commands);
		m_external_commands.clear();
		m_external_commands.str(""); //clear buffer

        while(m_commands.size() > 0) exec_next();
    }

    void push(const CommandT& cmd)
    {
		m_commands.push_back(cmd);
    }

    void parse(std::istream& input)
    {
    	std::list<CommandT> commands;
    	auto procedure_size_insert_it = end(commands);

    	input >> std::ws;

        while(input.good())
        {
        	const char next_char = input.peek();

        	switch(next_char)
        	{
        		case '#':
        		{
                	std::string line;
                    std::getline(input, line);
                    if(m_globals(Globals::app_debug_level).integer() >= int(Severity::DEBUG))
                    	std::cout << "PARSER: Reading comment: " << line << '\n';
        		}
				break;

        		case '@':
        		{
                	std::string var_name;
                	input.get(); //extract the @ char
                	input >> var_name;
                	commands.push_back(SetFixedVariableCommand{*this, m_globals, hash(var_name.c_str())});

                    if(m_globals(Globals::app_debug_level).integer() >= int(Severity::DEBUG))
                    	std::cout << "PARSER: Setting variable \"" << var_name << "\"\n";
        		}
				break;

        		case '*':
        		{
                	std::string var_name;
                	input.get(); //extract the * char
                	input >> var_name;
                	commands.push_back(GetFixedVariableCommand{*this, m_globals, var_name});

                	if(m_globals(Globals::app_debug_level).integer() >= int(Severity::DEBUG))
                    	std::cout << "PARSER: Reading variable \"" << var_name << "\"\n";
        		}
				break;

        		case '"':
        		case '\'':
        		{
                	std::string str;
                	input >> std::quoted(str, next_char);
                	commands.push_back(LiteralValueCommand{str});

                	if(m_globals(Globals::app_debug_level).integer() >= int(Severity::DEBUG))
                		std::cout << "PARSER: Reading string \"" << str << "\"\n";
        		}
				break;

        		case '(':
        		{
                	std::string str;
                	input.get(); //extract the ( char
                	std::getline(input, str, ')');
                	commands.push_back(CallProcedureCommand{*this, m_globals, str});

                	if(m_globals(Globals::app_debug_level).integer() >= int(Severity::DEBUG))
                		std::cout << "PARSER: Calling command \"" << str << "\"\n";
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
                    	if(m_globals(Globals::app_debug_level).integer() >= int(Severity::DEBUG))
                    		std::cout << "PARSER: Reading scalar " << value << '\n';
                    	commands.push_back(LiteralValueCommand{value});
                	}
        		}
				break;

        		case '{':
        		{
                	input.get(); //extract the { char
                	commands.push_back(ExtendProcedureCommand{*this});
                	commands.push_back(LiteralValueCommand{int32_t(m_procedures.size())});

                	//reserve space for procedure size
                	procedure_size_insert_it = commands.insert(end(commands), NullCommand{});

                	m_procedures.emplace_back();

                	if(m_globals(Globals::app_debug_level).integer() >= int(Severity::DEBUG))
                		std::cout << "PARSER: Declaring new procedure\n";
        		}
				break;

        		case '}':
        		{
                	input.get(); //extract the } char

                	if(procedure_size_insert_it != end(commands))
                	{
                		const auto proc_size = std::distance(procedure_size_insert_it, end(commands)) - 1;
						*procedure_size_insert_it = LiteralValueCommand{int32_t(proc_size)};
						procedure_size_insert_it = end(commands);

	                	if(m_globals(Globals::app_debug_level).integer() >= int(Severity::DEBUG))
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

                	if(m_globals(Globals::app_debug_level).integer() >= int(Severity::DEBUG))
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

    CommandValue exec_next()
    {
    	return pop_next()();
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

    Procedure<CommandSystem>& procedure(const ProcedureID id)
    {
    	const ProcedureID proc_id = std::max(0, id*(1 - (id >= static_cast<ProcedureID>(m_procedures.size()))));
		return m_procedures[proc_id];
    }

    void clear_procedures()
    {
        m_procedures.clear();
        initialize_default_procedures();
    }

    std::stringstream& external_commands()
	{
    	return m_external_commands;
	}

private:
    void initialize_default_procedures()
    {
        m_procedures.emplace_back(); //insert an empty procedure at id 0
    }

    std::stringstream m_external_commands;
    std::list<CommandT> m_commands;
    std::unordered_map<HashT, CommandT> m_command_prototypes;
    std::vector<Procedure<CommandSystem>> m_procedures;

    Globals& m_globals;
};


#endif /* SYSTEMS_COMMAND_SYSTEM_H_ */
