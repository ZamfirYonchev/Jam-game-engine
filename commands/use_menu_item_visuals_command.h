/*
 * use_menu_item_visuals_command.h
 *
 *  Created on: Nov 26, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_MENU_ITEM_VISUALS_COMMAND_H_
#define COMMANDS_USE_MENU_ITEM_VISUALS_COMMAND_H_

#include "command.h"
#include "../types.h"
#include "../components/menu_item_visuals.h"

class UseMenuItemVisualsCommand : public Command
{
public:
	UseMenuItemVisualsCommand(SpritesheetID spr_id)
	: m_spr_id(spr_id)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<UseMenuItemVisualsCommand>(m_spr_id); }
private:
    SpritesheetID m_spr_id;
};


#endif /* COMMANDS_USE_MENU_ITEM_VISUALS_COMMAND_H_ */
