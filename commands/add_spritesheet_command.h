/*
 * add_spritesheet_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_SPRITESHEET_COMMAND_H_
#define COMMANDS_ADD_SPRITESHEET_COMMAND_H_

#include "command.h"

class AddSpritesheetCommand : public Command
{
public:
    AddSpritesheetCommand(int idle_start, int idle_size
                        , int walk_start, int walk_size
                        , int jump_start, int jump_size
                        , int fall_start, int fall_size
						, int attack_start, int attack_size
						, int hit_start, int hit_size
						, int dead_start, int dead_size
                        , double scale_factor
                        ) : m_idle_start(idle_start), m_idle_size(idle_size)
                          , m_walk_start(walk_start), m_walk_size(walk_size)
                          , m_jump_start(jump_start), m_jump_size(jump_size)
                          , m_fall_start(fall_start), m_fall_size(fall_size)
						  , m_attack_start(attack_start), m_attack_size(attack_size)
						  , m_hit_start(hit_start), m_hit_size(hit_size)
                          , m_dead_start(dead_start), m_dead_size(dead_size)
                          , m_scale_factor(scale_factor)
                        {}

    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<AddSpritesheetCommand>(m_idle_start, m_idle_size
                                                          , m_walk_start, m_walk_size
                                                          , m_jump_start, m_jump_size
                                                          , m_fall_start, m_fall_size
                                                          , m_attack_start, m_attack_size
                                                          , m_hit_start, m_hit_size
                                                          , m_dead_start, m_dead_size
                                                          , m_scale_factor
                                                            );
                         }

private:
    int m_idle_start, m_idle_size;
    int m_walk_start, m_walk_size;
    int m_jump_start, m_jump_size;
    int m_fall_start, m_fall_size;
    int m_attack_start, m_attack_size;
    int m_hit_start, m_hit_size;
    int m_dead_start, m_dead_size;
    double m_scale_factor;
};

#endif /* COMMANDS_ADD_SPRITESHEET_COMMAND_H_ */
