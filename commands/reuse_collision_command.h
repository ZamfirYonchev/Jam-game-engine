/*
 * reuse_collision_command.h
 *
 *  Created on: Jun 30, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_REUSE_COLLISION_COMMAND_H_
#define COMMANDS_REUSE_COLLISION_COMMAND_H_

#include "command.h"
#include "../components/collision.h"
#include "../types.h"
#include <SDL2/SDL.h>

class ReuseCollisionCommand : public Command
{
public:
	ReuseCollisionCommand(const EntityID& source_id, SDL_Renderer* renderer)
	: m_source_id(source_id)
	, m_renderer(renderer)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<ReuseCollisionCommand>(m_source_id, m_renderer); }
private:
    EntityID m_source_id;
    SDL_Renderer* m_renderer;
};


#endif /* COMMANDS_REUSE_COLLISION_COMMAND_H_ */
