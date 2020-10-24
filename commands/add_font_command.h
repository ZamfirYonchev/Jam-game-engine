/*
 * add_font_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_FONT_COMMAND_H_
#define COMMANDS_ADD_FONT_COMMAND_H_

#include <string>
#include "../systems/resource_system.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class AddFontCommand
{
public:
	AddFontCommand(const std::string& file, int size)
	: m_file(file)
	, m_size(size)
	{}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	resource_system.addNewFont(m_file, m_size);
    }

private:
    std::string m_file;
    int m_size;
};


#endif /* COMMANDS_ADD_FONT_COMMAND_H_ */
