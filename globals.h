/*
 * globals.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "types.h"
#include <string>

struct Globals
{
	Globals() : app_running(true)
    		  , app_needs_reload(false)
    		  , app_paused(false)
    		  , fullscreen(false)
			  , show_hitboxes(false)
    		  , resolution_x(640)
    		  , resolution_y(480)
    		  , access_spritesheet_id(-1)
    		  , access_procedure_id(-1)
			  , level_name("levels/menu.txt")
			  {}

    bool app_running, app_needs_reload, app_paused, fullscreen, show_hitboxes;
    uint16_t resolution_x, resolution_y;
    SpritesheetID access_spritesheet_id;
    ProcedureID access_procedure_id;
    std::string level_name;
};

#endif /* GLOBALS_H_ */
