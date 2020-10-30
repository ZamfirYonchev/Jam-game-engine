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
#include "../optional_ref.h"
#include <utility>
#include <optional>

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

template<typename EntitySystemT, typename AllSystemsT>
class CommandSystem
{
public:
	using CommandT = std::function<void(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystem& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals)>;
	using OptionalCommandT = std::optional<CommandT>;
	using ParserT = std::function<CommandT(std::istream&)>;

	CommandSystem(EntitySystemT& entity_system, AllSystemsT& all_systems)
	: m_entity_system(entity_system)
	, m_all_systems(all_systems)
	{}

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
            const auto cmd = std::move(m_commands.front());
            m_commands.pop_front();
            cmd(m_entity_system, resource_system, input_system, *this, rendering_system, m_all_systems, globals);
        }
    }

    void process_stream(std::istream& input)
    {
        auto next_cmd_it = std::begin(m_commands);

        while(input.good())
        {
        	const std::string token { [&](){ std::string result; input >> result; return result; }() }; // @suppress("Invalid arguments")
            if(input.eof())
                break;

            std::cout << "Token is '" << token << "'\n";


            if(token[0] == '#')
            {
            	std::string line;
                std::getline(input, line);
                std::cout << "Reading comment: " << token << line << '\n';
            }
            else
            {
            	const auto it = m_command_parsers.find(hash(token.c_str()));
            	if(it != cend(m_command_parsers))
            	{
            		CommandT command = (it->second)(input);
                    if(input.fail())
                    {
                        std::cerr << "Parsing error: Parameters of token " << token << std::endl;
                        break;
                    }

                    insert_before(next_cmd_it, command);
            	}
            	else
            		std::cerr << "Trying to parse a non-existing command " << token << std::endl;
            }
        }
    }

    void push(const CommandT& cmd)
    {
		m_commands.push_back(cmd);
    }

    void insert_next(const CommandT& cmd)
    {
		m_commands.push_front(cmd);
    }

    void insert_before(const typename std::list<CommandT>::iterator it, const CommandT& cmd)
    {
    	m_commands.insert(it, cmd);
    }

    OptionalCommandT pop_next()
    {
    	if(m_commands.size() > 0)
    	{
    		const OptionalCommandT cmd {std::move(m_commands.front())};
            m_commands.pop_front();
            return cmd;
    	}
    	else
    		return std::nullopt;
    }

    void clear()
    {
    	flush_commands();
        clear_procedures();
        m_commands.clear();
        m_command_parsers.clear();
    }

    void flush_commands()
    {
        for(auto& cmd  : m_commands)
        	cmd = NullCommand{};
    }

    void register_command(const std::string name, const ParserT& function)
    {
    	const auto str_hash = hash(name.c_str());
    	const auto it = m_command_parsers.find(str_hash);
    	if(it != cend(m_command_parsers))
    	{
    		std::cerr << "Command " << name << " already registered. Overwriting...\n";
    		it->second = function;
    	}
    	else
    		m_command_parsers[str_hash] = function;
    }

    void unregister_command(const std::string name)
    {
    	const auto it = m_command_parsers.find(hash(name.c_str()));
    	if(it == cend(m_command_parsers))
    		std::cerr << "Trying to remove non-existing command " << name << ".\n";
    	else
    		m_command_parsers.erase(it);
    }

    ProcedureID addNewProcedure()
    {
    	const ProcedureID proc_id = static_cast<ProcedureID>(m_procedures.size());
        m_procedures.emplace_back();
        return proc_id;
    }

    optional_ref<ProcedureCommand<CommandSystem>> procedure(const ProcedureID id)
    {
        if(0 <= id && id < static_cast<ProcedureID>(m_procedures.size()))
        	return optional_ref<ProcedureCommand<CommandSystem>>(m_procedures[id]);
		else
			return optional_ref<ProcedureCommand<CommandSystem>>();
    }

    void clear_procedures()
    {
        m_procedures.clear();
    }

    std::list<std::pair<EntityID, ProcedureID>>& procedure_calls()
	{
    	return m_procedure_calls;
	}

private:
	std::list<std::pair<EntityID, ProcedureID>> m_procedure_calls;
    std::list<CommandT> m_commands;
    std::unordered_map<unsigned long, ParserT> m_command_parsers;
    std::vector<ProcedureCommand<CommandSystem>> m_procedures;
    EntitySystemT& m_entity_system;
    AllSystemsT& m_all_systems;
};


#endif /* SYSTEMS_COMMAND_SYSTEM_H_ */
