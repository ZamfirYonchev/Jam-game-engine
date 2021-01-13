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
#include "utilities.h"
#include "types.h"
#include <optional>

struct Globals
{
	Globals() : app_running(true)
    		  , app_needs_reload(false)
    		  , app_paused(false)
    		  , fullscreen(false)
			  , audio(false)
			  , show_hitboxes(false)
    		  , resolution_x(640)
    		  , resolution_y(480)
			  , sound_channels(4)
    		  , access_spritesheet_id(-1)
    		  , access_procedure_id(-1)
			  , level_name("levels/menu.txt")
			  , destination_variable_hash(std::nullopt)
			  {}

    bool app_running, app_needs_reload, app_paused, fullscreen, audio, show_hitboxes;
    int resolution_x, resolution_y;
    int sound_channels;
    SpritesheetID access_spritesheet_id;
    ProcedureID access_procedure_id;
    std::string level_name;
    std::optional<HashT> destination_variable_hash;
};

#endif /* GLOBALS_H_ */
