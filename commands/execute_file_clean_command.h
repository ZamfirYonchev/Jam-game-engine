/*
 * execute_file_clean_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_EXECUTE_FILE_CLEAN_COMMAND_H_
#define COMMANDS_EXECUTE_FILE_CLEAN_COMMAND_H_

#include "command.h"
#include <string>
#include <SDL2/SDL.h>

class ExecuteFileCleanCommand : public Command
{
public:
    ExecuteFileCleanCommand(const std::string& filename, SDL_Renderer* renderer)
    : m_filename(filename)
	, m_renderer(renderer)
    {}

    void execute() const;
    Command* clone() { return new ExecuteFileCleanCommand(m_filename, m_renderer); }

private:
    std::string m_filename;
    SDL_Renderer* m_renderer;
};


#endif /* COMMANDS_EXECUTE_FILE_CLEAN_COMMAND_H_ */
