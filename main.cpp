/*
 * main.cpp
 *
 *  Created on: Nov 7, 2019
 *      Author: zamfi
 */

//zamfir.yonchev @ gmail.com

#include "sdl_window.h"
#include <SDL2/SDL.h>
#include "file_parser.h"
#include "globals.h"
#include "math_ext.h"
#include "components/static_visuals.h"
#include "components/absolute_position.h"
#include "components/character_visuals.h"
#include "components/basic_collision.h"
#include "components/full_movement.h"
#include "components/input_control.h"
#include "commands/execute_file_clean_command.h"
#include "components/damage_collision.h"
#include "components/character_health.h"
#include "components/tiled_visuals.h"
#include "commands/select_entity_command.h"
#include "commands/modify_position_command.h"
#include "components/trigger_interaction.h"
#include "commands/call_procedure_command.h"
#include "components/normal_interaction.h"
#include "components/attached_position.h"
#include "commands/modify_movement_command.h"
#include "commands/use_timed_health_command.h"
#include "commands/add_entity_command.h"
#include "components/guide_control.h"
#include "components/instant_movement.h"

int main(int argc, char** argv)
{
	do
	{
		FileParser file;
		std::string token;
		file.open("settings.txt");

		try
		{
			while(file.read().peek() != EOF)
			{
				file.read() >> token;

				if(token == "ResolutionX")
				{
					file.read() >> globals.resolution_x;
					std::cout << "Set ResolutionX to " << globals.resolution_x << std::endl;
				}
				else if(token == "ResolutionY")
				{
					file.read() >> globals.resolution_y;
					std::cout << "Set ResolutionY to " << globals.resolution_y << std::endl;
				}
				else if(token == "ResolutionBPP")
				{
					file.read() >> globals.resolution_bpp;
					std::cout << "Set ResolutionBPP to " << globals.resolution_bpp << std::endl;
				}
				else if(token == "Fullscreen")
				{
					file.read() >> globals.fullscreen;
					std::cout << "Set Fullscreen to " << globals.fullscreen << std::endl;
				}
				else if(token == "Level")
				{
					file.read() >> globals.level_name;
					std::cout << "Set level to " << globals.level_name << std::endl;
				}
				else
					std::cout << "Unknown setting " << token << std::endl;
			}
	    }
	    catch(std::ifstream::failure& except)
	    {
	    	//error message
	    }

	    file.close();

		SdlWindow sdl;
		sdl.init_video(globals.resolution_x
					 , globals.resolution_y
					 , globals.resolution_bpp
					 , globals.fullscreen
					 , true);

		int32_t last_frame_time;
		int32_t frame_diff;
		int32_t number_of_frames = 0;

		globals.entity_system.clear();
        globals.control_system.clear();
        globals.movement_system.clear();
        globals.collision_system.clear();
        globals.damage_system.clear();
        globals.rendering_system.clear();
        globals.resource_system.clear();
        globals.command_queue.flush_commands();

        globals.command_queue.push(std::make_unique<ExecuteFileCleanCommand>(globals.level_name, sdl.renderer()));

/*
## new code
AddEntity #6: moving platform
UseAbsolutePosition 200 0 200 100
UseBasicCollision 2
UseTiledVisuals 2 6 3
UseFullMovement 0 0.05 0 0 1
UseNormalInteraction 0
ModifyInteraction 1 1 0 0 0

		globals.resource_system.addNewProcedure();
		globals.resource_system.procedure(2)->add_command(new SelectEntityCommand(6));
		globals.resource_system.procedure(2)->add_command(new ModifyMovementCommand(0, 0, 0, 0.05, 0));

		globals.resource_system.addNewProcedure();
		globals.resource_system.procedure(3)->add_command(new SelectEntityCommand(6));
		globals.resource_system.procedure(3)->add_command(new ModifyMovementCommand(0, 0, 0, 0.005, 0));

		globals.entity_system.add_new_entity();
		globals.entity_system.entity(globals.entity_system.last_id())->set_position(new AbsolutePosition(400, 0, 100, 100));
		globals.entity_system.entity(globals.entity_system.last_id())->set_collision(new BasicCollision(Collision::TRANSPARENT));
		globals.entity_system.entity(globals.entity_system.last_id())->set_interaction(new TriggerInteraction(0, -1, 2));

		globals.entity_system.add_new_entity();
		globals.entity_system.entity(globals.entity_system.last_id())->set_position(new AbsolutePosition(250, 0, 1, 1));
		globals.entity_system.entity(globals.entity_system.last_id())->set_collision(new BasicCollision(Collision::TRANSPARENT));
		globals.entity_system.entity(globals.entity_system.last_id())->set_interaction(new TriggerInteraction(1, -1, 3));

		globals.entity_system.add_new_entity();
		globals.entity_system.entity(globals.entity_system.last_id())->set_position(new AbsolutePosition(600, 300, 200, 100));
		globals.entity_system.entity(globals.entity_system.last_id())->set_collision(new BasicCollision(Collision::SOLID));
		globals.entity_system.entity(globals.entity_system.last_id())->set_visuals(new TiledVisuals(2, 6, 3));

		globals.resource_system.addNewProcedure();
		globals.resource_system.procedure(4)->add_command(new AddEntityCommand());
		globals.resource_system.procedure(4)->add_command(new UseTimedHealthCommand(10, 5));
		globals.resource_system.procedure(4)->add_command(new SelectEntityCommand(0));
		globals.resource_system.procedure(4)->add_command(new ModifyPositionCommand(-5, 0, 0, 0));

		globals.resource_system.addNewProcedure();
		globals.resource_system.procedure(5)->add_command(new UseTimedHealthCommand(10, 6));
		globals.resource_system.procedure(5)->add_command(new SelectEntityCommand(0));
		globals.resource_system.procedure(5)->add_command(new ModifyPositionCommand(5, 5, 0, 0));

		globals.resource_system.addNewProcedure();
		globals.resource_system.procedure(6)->add_command(new UseTimedHealthCommand(10, 7));
		globals.resource_system.procedure(6)->add_command(new SelectEntityCommand(0));
		globals.resource_system.procedure(6)->add_command(new ModifyPositionCommand(0, -10, 0, 0));

		globals.resource_system.addNewProcedure();
		globals.resource_system.procedure(7)->add_command(new UseTimedHealthCommand(10, 8));
		globals.resource_system.procedure(7)->add_command(new SelectEntityCommand(0));
		globals.resource_system.procedure(7)->add_command(new ModifyPositionCommand(5, 5, 0, 0));

		globals.resource_system.addNewProcedure();
		globals.resource_system.procedure(8)->add_command(new SelectEntityCommand(0));
		globals.resource_system.procedure(8)->add_command(new ModifyPositionCommand(-5, 0, 0, 0));
*/
		last_frame_time = SDL_GetTicks();

		do
		{
			frame_diff = clip(int32_t(SDL_GetTicks()-last_frame_time), 1, 100);
			last_frame_time = SDL_GetTicks();

			globals.input_handler.process_input();
			globals.command_queue.process(frame_diff);
            globals.entity_system.clean_removed_entites();

			if(globals.app_paused == false)
			{
				globals.control_system.update(frame_diff);
				globals.movement_system.update(frame_diff);
				globals.collision_system.update(frame_diff);
				globals.damage_system.update(frame_diff);
			}

			globals.rendering_system.render_entities(frame_diff, globals.app_paused, sdl.renderer());

			++number_of_frames;
			SDL_Delay(10);
		} while(globals.app_running && globals.app_needs_reload == false);

		globals.app_needs_reload = false;

	} while(globals.app_running);

	return 0;
}

