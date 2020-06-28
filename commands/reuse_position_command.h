/*
 * reuse_position_command.h
 *
 *  Created on: Jun 28, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_REUSE_POSITION_COMMAND_H_
#define COMMANDS_REUSE_POSITION_COMMAND_H_


#include "command.h"
#include "../components/position.h"
#include "../types.h"
#include <SDL2/SDL.h>

class ReusePositionCommand : public Command
{
public:
	ReusePositionCommand(const EntityID& source_id, SDL_Renderer* renderer)
	: m_source_id(source_id)
	, m_renderer(renderer)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<ReusePositionCommand>(m_source_id, m_renderer); }
private:
    EntityID m_source_id;
    SDL_Renderer* m_renderer;
};




#endif /* COMMANDS_REUSE_POSITION_COMMAND_H_ */
