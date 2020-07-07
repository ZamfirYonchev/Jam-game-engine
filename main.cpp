/*
 * main.cpp
 *
 *  Created on: Nov 7, 2019
 *      Author: zamfi
 */

//zamfir.yonchev @ gmail.com

#include "sdl_window.h"
#include <SDL2/SDL.h>
#include <fstream>
#include "globals.h"
#include "math_ext.h"
#include "commands/execute_file_clean_command.h"

int main(int argc, char** argv)
{
	do
	{
		std::ifstream file;
		file.open("settings.txt");

		while(file.peek() != EOF)
		{
			const std::string token { [&](){ std::string result; file >> result; return result; }() }; // @suppress("Invalid arguments")

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
					 , globals().fullscreen
					 , true);

		Time start_frame_time;
		Time last_frame_time;
		Time frame_diff = Time{10}; //TODO: first frame difference
		int32_t number_of_frames = 0;

		command_queue().push(std::make_unique<ExecuteFileCleanCommand>(globals().level_name, sdl.renderer()));

		start_frame_time = static_cast<Time>((SDL_GetTicks()));
		last_frame_time = static_cast<Time>((SDL_GetTicks()));

		do
		{
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

			SDL_Delay(max(10-frame_diff, 0));
			frame_diff = Time(clip(int32_t(SDL_GetTicks()-last_frame_time), 1, 100));
			last_frame_time = Time(SDL_GetTicks());
			++number_of_frames;

			if(globals().app_running == false || globals().app_needs_reload)
			{
				resource_system().clear(); //cleanup textures otherwise when SdlWindow is destroyed we get a memory leak
				control_system().clear();
				movement_system().clear();
				collision_system().clear();
				damage_system().clear();
				rendering_system().clear();
				command_queue().flush_commands(true);
				entity_system().clear();

				break;
			}
		} while(1);

		std::cout << "FPS = " << 1000.0*number_of_frames / (SDL_GetTicks()-start_frame_time) << std::endl;
		globals().app_needs_reload = false;

	} while(globals().app_running);

	return 0;
}

