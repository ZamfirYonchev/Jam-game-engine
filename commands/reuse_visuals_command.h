/*
 * reuse_visuals_command.h
 *
 *  Created on: Jun 30, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_REUSE_VISUALS_COMMAND_H_
#define COMMANDS_REUSE_VISUALS_COMMAND_H_

#include "command.h"
#include "../components/visuals.h"
#include "../types.h"
#include <SDL2/SDL.h>

class ReuseVisualsCommand : public Command
{
public:
	ReuseVisualsCommand(const EntityID& source_id, SDL_Renderer* renderer)
	: m_source_id(source_id)
	, m_renderer(renderer)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<ReuseVisualsCommand>(m_source_id, m_renderer); }
private:
    EntityID m_source_id;
    SDL_Renderer* m_renderer;
};

#endif /* COMMANDS_REUSE_VISUALS_COMMAND_H_ */
