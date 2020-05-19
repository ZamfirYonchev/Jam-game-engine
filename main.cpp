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
		std::ifstream file;
		std::string token;
		file.open("settings.txt");

		while(file.peek() != EOF)
		{
			file >> token;

			if(token == "ResolutionX")
			{
				file >> globals().resolution_x;
				std::cout << "Set ResolutionX to " << globals().resolution_x << std::endl;
			}
			else if(token == "ResolutionY")
			{
				file >> globals().resolution_y;
				std::cout << "Set ResolutionY to " << globals().resolution_y << std::endl;
			}
			else if(token == "ResolutionBPP")
			{
				file >> globals().resolution_bpp;
				std::cout << "Set ResolutionBPP to " << globals().resolution_bpp << std::endl;
			}
			else if(token == "Fullscreen")
			{
				file >> globals().fullscreen;
				std::cout << "Set Fullscreen to " << globals().fullscreen << std::endl;
			}
			else if(token == "Level")
			{
				file >> globals().level_name;
				std::cout << "Set level to " << globals().level_name << std::endl;
			}
			else
				std::cout << "Unknown setting " << token << std::endl;
		}

		file.close();

		SdlWindow sdl;
		sdl.init_video(globals().resolution_x
					 , globals().resolution_y
					 , globals().resolution_bpp
					 , globals().fullscreen
					 , true);

		int32_t start_frame_time;
		int32_t last_frame_time;
		int32_t frame_diff;
		int32_t number_of_frames = 0;

		entity_system().clear();
		control_system().clear();
		movement_system().clear();
		collision_system().clear();
		damage_system().clear();
		rendering_system().clear();
		resource_system().clear();
		command_queue().flush_commands();

		command_queue().push(std::make_unique<ExecuteFileCleanCommand>(globals().level_name, sdl.renderer()));

		start_frame_time = SDL_GetTicks();
		last_frame_time = SDL_GetTicks();

		do
		{
			frame_diff = clip(int32_t(SDL_GetTicks()-last_frame_time), 1, 100);
			last_frame_time = SDL_GetTicks();

			input_handler().process_input();
			command_queue().process(frame_diff);
			entity_system().clean_removed_entites();

			if(globals().app_paused == false)
			{
				control_system().update(frame_diff);
				movement_system().update(frame_diff);
				collision_system().update(frame_diff);
				damage_system().update(frame_diff);
			}

			rendering_system().render_entities(frame_diff, globals().app_paused, sdl.renderer());

			++number_of_frames;
			SDL_Delay(10);
		} while(globals().app_running && globals().app_needs_reload == false);

		globals().app_needs_reload = false;
		std::cout << "FPS = " << 1000.0*number_of_frames / (SDL_GetTicks()-start_frame_time) << std::endl;

	} while(globals().app_running);

	return 0;
}

