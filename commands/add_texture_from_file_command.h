/*
 * add_texture_from_file_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_TEXTURE_FROM_FILE_COMMAND_H_
#define COMMANDS_ADD_TEXTURE_FROM_FILE_COMMAND_H_

#include "command.h"
#include <string>
#include <SDL2/SDL.h>

class AddTextureFromFileCommand : public Command
{
public:
    AddTextureFromFileCommand(const std::string& file, SDL_Renderer* renderer) : m_file(file), m_renderer(renderer) {}
    void execute() const;
    Command* clone() { return new AddTextureFromFileCommand(m_file, m_renderer); }

private:
    std::string m_file;
    SDL_Renderer* m_renderer;
};


#endif /* COMMANDS_ADD_TEXTURE_FROM_FILE_COMMAND_H_ */
