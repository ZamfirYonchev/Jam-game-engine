/*
 * use_character_visuals_command.h
 *
 *  Created on: Nov 26, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_CHARACTER_VISUALS_COMMAND_H_
#define COMMANDS_USE_CHARACTER_VISUALS_COMMAND_H_

#include "command.h"
#include "../types.h"

class UseCharacterVisualsCommand : public Command
{
public:
	UseCharacterVisualsCommand(SpritesheetID spr_id)
	: m_spr_id(spr_id)
	{}

    void execute() const;
    Command* clone() { return new UseCharacterVisualsCommand(m_spr_id); }
private:
    SpritesheetID m_spr_id;
};

#endif /* COMMANDS_USE_CHARACTER_VISUALS_COMMAND_H_ */
