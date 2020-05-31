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

#include "systems/entity_system.h"
#include "systems/resource_system.h"
#include "systems/control_system.h"
#include "systems/movement_system.h"
#include "systems/collision_system.h"
#include "systems/damage_system.h"
#include "systems/rendering_system.h"
#include "input_handler.h"
#include "command_queue.h"

InputHandler& input_handler();
CommandQueue& command_queue();
EntitySystem& entity_system();
ResourceSystem& resource_system();
ControlSystem& control_system();
MovementSystem& movement_system();
CollisionSystem& collision_system();
DamageSystem& damage_system();
RenderingSystem& rendering_system();

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

Globals& globals();

#endif /* GLOBALS_H_ */
