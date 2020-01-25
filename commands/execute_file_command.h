/*
 * execute_file_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_EXECUTE_FILE_COMMAND_H_
#define COMMANDS_EXECUTE_FILE_COMMAND_H_

#include "command.h"
#include <string>
#include <SDL2/SDL.h>

class ExecuteFileCommand : public Command
{
public:
    ExecuteFileCommand(const std::string& filename, SDL_Renderer* renderer)
    : m_filename(filename)
	, m_renderer(renderer)
    {}

    void execute() const;
    Command* clone() { return new ExecuteFileCommand(m_filename, m_renderer); }

private:
    std::string m_filename;
    SDL_Renderer* m_renderer;
};


#endif /* COMMANDS_EXECUTE_FILE_COMMAND_H_ */
