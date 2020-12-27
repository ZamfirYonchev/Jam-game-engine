/*
 * add_sound_command.h
 *
 *  Created on: Nov 13, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_SOUND_COMMAND_H_
#define COMMANDS_ADD_SOUND_COMMAND_H_

#include <string>
#include "../systems/resource_system.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class AddSoundCommand
{
public:
	AddSoundCommand(const std::string& file, const int repeat)
	: m_file(file)
	, m_repeat(repeat)
	{}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	resource_system.addNewSound(m_file, m_repeat);
    }

private:
    std::string m_file;
    int m_repeat;
};


#endif /* COMMANDS_ADD_SOUND_COMMAND_H_ */
