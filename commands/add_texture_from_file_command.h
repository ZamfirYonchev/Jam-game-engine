/*
 * add_texture_from_file_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_TEXTURE_FROM_FILE_COMMAND_H_
#define COMMANDS_ADD_TEXTURE_FROM_FILE_COMMAND_H_

#include <string>
#include "../systems/resource_system.h"
#include "../systems/rendering_system.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class AddTextureFromFileCommand
{
public:
    AddTextureFromFileCommand(const std::string& file) : m_file(file) {}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	resource_system.addNewTextureFromFile(m_file, rendering_system.renderer());
    }

private:
    std::string m_file;
};


#endif /* COMMANDS_ADD_TEXTURE_FROM_FILE_COMMAND_H_ */
