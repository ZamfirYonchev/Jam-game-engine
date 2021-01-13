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
#include "systems/rendering_system.h"
#include "systems/entity_system.h"
#include "systems/resource_system.h"
#include "systems/command_system.h"
#include "systems/input_system.h"
#include <iostream>
#include <istream>

#include "systems/control_system.h"
#include "systems/movement_system.h"
#include "systems/collision_system.h"
#include "systems/damage_system.h"
#include "systems/sound_system.h"
#include "systems/all_systems.h"

#include "commands/null_command.h"
#include "commands/debug_message_command.h"
#include "commands/set_level_command.h"
#include "commands/fix_view_width_command.h"
#include "commands/select_entity_command.h"
#include "commands/extend_procedure_command.h"
#include "commands/execute_file_command.h"
#include "commands/execute_file_clean_command.h"
#include "commands/clear_procedure_command.h"
#include "commands/pause_command.h"
#include "commands/quit_command.h"
#include "commands/clear_all_entities_command.h"
#include "commands/clear_all_textures_command.h"
#include "commands/clear_all_spritesheets_command.h"
#include "commands/clear_all_procedures_command.h"
#include "commands/call_procedure_command.h"
#include "commands/add_font_command.h"
#include "commands/add_sound_command.h"
#include "commands/add_music_command.h"
#include "commands/add_texture_from_file_command.h"
#include "commands/add_texture_from_string_command.h"
#include "commands/add_spritesheet_command.h"
#include "commands/add_sprite_command.h"
#include "commands/add_entity_command.h"
#include "commands/remove_entity_command.h"
#include "commands/modify_position_command.h"
#include "commands/modify_control_command.h"
#include "commands/modify_movement_command.h"
#include "commands/modify_collision_command.h"
#include "commands/modify_interaction_command.h"
#include "commands/modify_health_command.h"
#include "commands/modify_visuals_command.h"
#include "commands/use_component_command.h"
#include "commands/reuse_component_command.h"
#include "commands/export_entities_command.h"
#include "commands/finalize_build_command.h"
#include "commands/play_sound_command.h"
#include "commands/play_music_command.h"

#include "components/absolute_position.h"
#include "components/attached_position.h"
#include "components/build_position.h"
#include "components/null_position.h"
#include "components/constant_control.h"
#include "components/absolute_position.h"
#include "components/attached_position.h"
#include "components/null_position.h"
#include "components/chase_ai_control.h"
#include "components/constant_control.h"
#include "components/guide_control.h"
#include "components/input_control.h"
#include "components/input_select_control.h"
#include "components/particle_control.h"
#include "components/null_control.h"
#include "components/full_movement.h"
#include "components/instant_movement.h"
#include "components/null_movement.h"
#include "components/basic_collision.h"
#include "components/damage_collision.h"
#include "components/null_collision.h"
#include "components/full_interaction.h"
#include "components/normal_interaction.h"
#include "components/trigger_interaction.h"
#include "components/null_interaction.h"
#include "components/attached_health.h"
#include "components/character_health.h"
#include "components/timed_health.h"
#include "components/null_health.h"
#include "components/character_visuals.h"
#include "components/health_visuals.h"
#include "components/menu_item_visuals.h"
#include "components/static_visuals.h"
#include "components/tiled_visuals.h"
#include "components/null_visuals.h"
#include "components/character_sounds.h"
#include "components/null_sounds.h"

#include "commands/set_variable_command.h"
#include "commands/get_variable_command.h"

#include <list>
#include <utility>
#include <string>
#include <random>
#include <array>
#include "commands/literal_value_command.h"

int main(int argc, char** argv)
{
	Globals globals;

	do
	{
		std::ifstream file;
		file.open("settings.txt");

		while(file.peek() != EOF)
		{
			const std::string token { [&](){ std::string result; file >> result; return result; }() }; // @suppress("Invalid arguments")

			if(token == "ResolutionX")
			{
				file >> globals.resolution_x;
				std::cout << "Set ResolutionX to " << globals.resolution_x << std::endl;
			}
			else if(token == "ResolutionY")
			{
				file >> globals.resolution_y;
				std::cout << "Set ResolutionY to " << globals.resolution_y << std::endl;
			}
			else if(token == "Fullscreen")
			{
				file >> globals.fullscreen;
				std::cout << "Set Fullscreen to " << globals.fullscreen << std::endl;
			}
			else if(token == "EnableAudio")
			{
				file >> globals.audio;
				std::cout << "Set Audio to " << globals.audio << std::endl;
			}
			else if(token == "Level")
			{
				file >> globals.level_name;
				std::cout << "Set level to " << globals.level_name << std::endl;
			}
			else
				std::cout << "Unknown setting " << token << std::endl;
		}

		file.close();


		SdlWindow sdl;
		sdl.init_video(globals.resolution_x
					 , globals.resolution_y
					 , globals.fullscreen
					 , true
					 , globals.audio
					 , globals.sound_channels);


		EntitySystem<Position,Control,Movement,Collision,Interaction,Health,Visuals,Sounds> entity_system;
		using ES = decltype(entity_system);
		ResourceSystem resource_system;
		InputSystem input_system;
		RenderingSystem rendering_system {sdl.renderer()};

		ControlSystem<ES> control_system {entity_system};
		MovementSystem<ES> movement_system {entity_system};
		CollisionSystem<ES> collision_system {entity_system};
		DamageSystem<ES> damage_system {entity_system};
		SoundSystem<ES> sound_system {entity_system, resource_system};

		AllSystems<ControlSystem<ES>,MovementSystem<ES>,CollisionSystem<ES>,DamageSystem<ES>, SoundSystem<ES>> all_systems
		{ control_system
		, movement_system
		, collision_system
		, damage_system
		, sound_system
		};

		using AS = decltype(all_systems);
		CommandSystem<ES, AS> command_system {entity_system, resource_system, input_system, rendering_system, all_systems, globals};
		//using CS = decltype(command_system);

		std::mt19937 gen {std::random_device{}()};

	    command_system.register_command("Set", SetVariableCommand{});
	    command_system.register_command("Val", GetVariableCommand{});
	    command_system.register_command("DebugMessage", DebugMessageCommand{});
		command_system.register_command("SetLevel", SetLevelCommand{});
		command_system.register_command("FixViewWidth", FixViewWidthCommand{});
		command_system.register_command("SelectEntity", SelectEntityCommand{});
		command_system.register_command("Select", SelectEntityCommand{});
		command_system.register_command("ExtendProcedure", ExtendProcedureCommand{});
		command_system.register_command("ClearProcedure", ClearProcedureCommand{});
		command_system.register_command("Pause", PauseCommand{});
		command_system.register_command("Quit", QuitCommand{});
		command_system.register_command("ClearAllEntities", ClearAllTexturesCommand{});
		command_system.register_command("ClearAllSpritesheets", ClearAllSpritesheetsCommand{});
		command_system.register_command("ClearAllProcedures", ClearAllProceduresCommand{});
		command_system.register_command("ExecuteFile", ExecuteFileCommand{});
		command_system.register_command("ExecuteFileClean", ExecuteFileCleanCommand{});
		command_system.register_command("CallProcedure", CallProcedureCommand{});
		command_system.register_command("Call", CallProcedureCommand{});
		command_system.register_command("AddFont", AddFontCommand{});
		command_system.register_command("AddTextureFromFile", AddTextureFromFileCommand{});
		command_system.register_command("AddTextureFromString", AddTextureFromStringCommand{});
		command_system.register_command("AddSpritesheet", AddSpritesheetCommand{});
		command_system.register_command("AddSprite", AddSpriteCommand{});
		command_system.register_command("AddSound", AddSoundCommand{});
		command_system.register_command("AddMusic", AddMusicCommand{});
		command_system.register_command("AddEntity", AddEntityCommand{});
		command_system.register_command("RemoveEntity", RemoveEntityCommand{});
		command_system.register_command("ModifyPosition", ModifyPositionCommand{});
		command_system.register_command("ModifyControl", ModifyControlCommand{});
		command_system.register_command("ModifyMovement", ModifyMovementCommand{});
		command_system.register_command("ModifyCollision", ModifyCollisionCommand{});
		command_system.register_command("ModifyInteraction", ModifyInteractionCommand{});
		command_system.register_command("ModifyHealth", ModifyHealthCommand{});
		command_system.register_command("ModifyVisuals", ModifyVisualsCommand{});
		command_system.register_command("UseNullPosition", UseComponentCommand<NullPosition>{});
		command_system.register_command("UseAbsolutePosition", UseComponentCommand<AbsolutePosition>{});
		command_system.register_command("UseAttachedPosition", UseComponentCommand<AttachedPosition<ES>>{});
		command_system.register_command("UseBuildPosition", UseBuildPositionCommand{});
		command_system.register_command("UseNullControl", UseComponentCommand<NullControl>{});
		command_system.register_command("UseConstantControl",UseComponentCommand<ConstantControl>{});
		command_system.register_command("UseInputControl", UseInputControlCommand{});
		command_system.register_command("UseInputSelectControl", UseComponentCommand<InputSelectControl>{});
		command_system.register_command("UseChaseAIControl", UseChaseAIControlCommand{});
		command_system.register_command("UseGuideControl", UseGuideControlCommand{});
		command_system.register_command("UseParticleControl", UseParticleControlCommand{gen});
		command_system.register_command("UseNullMovement", UseComponentCommand<NullMovement>{});
		command_system.register_command("UseFullMovement", UseComponentCommand<FullMovement>{});
		command_system.register_command("UseInstantMovement", UseComponentCommand<InstantMovement>{});
		command_system.register_command("UseNullCollision", UseComponentCommand<NullCollision>{});
		command_system.register_command("UseBasicCollision", UseComponentCommand<BasicCollision>{});
		command_system.register_command("UseDamageCollision", UseComponentCommand<DamageCollision>{});
		command_system.register_command("UseNullInteraction", UseComponentCommand<NullInteraction>{});
		command_system.register_command("UseNormalInteraction", UseComponentCommand<NormalInteraction>{});
		command_system.register_command("UseTriggerInteraction", UseComponentCommand<TriggerInteraction>{});
		command_system.register_command("UseFullInteraction", UseComponentCommand<FullInteraction>{});
		command_system.register_command("UseNullHealth", UseComponentCommand<NullHealth>{});
		command_system.register_command("UseAttachedHealth", UseAttachedHealthCommand{});
		command_system.register_command("UseCharacterHealth", UseComponentCommand<CharacterHealth>{});
		command_system.register_command("UseTimedHealth", UseComponentCommand<TimedHealth>{});
		command_system.register_command("UseNullVisuals", UseComponentCommand<NullVisuals>{});
		command_system.register_command("UseCharacterVisuals", UseCharacterVisualsCommand{});
		command_system.register_command("UseTiledVisuals", UseTiledVisualsCommand{});
		command_system.register_command("UseStaticVisuals", UseComponentCommand<StaticVisuals>{});
		command_system.register_command("UseHealthVisuals", UseHealthVisualsCommand{});
		command_system.register_command("UseMenuItemVisuals", UseMenuItemVisualsCommand{});
		command_system.register_command("UseNullSounds", UseComponentCommand<NullSounds>{});
		command_system.register_command("UseCharacterSounds", UseCharacterSoundsCommand{});
		command_system.register_command("ReusePosition", ReuseComponentCommand<Position>{});
		command_system.register_command("ReuseControl", ReuseComponentCommand<Control>{});
		command_system.register_command("ReuseMovement", ReuseComponentCommand<Movement>{});
		command_system.register_command("ReuseCollision", ReuseComponentCommand<Collision>{});
		command_system.register_command("ReuseInteraction", ReuseComponentCommand<Interaction>{});
		command_system.register_command("ReuseHealth", ReuseComponentCommand<Health>{});
		command_system.register_command("ReuseVisuals", ReuseComponentCommand<Visuals>{});
		command_system.register_command("ExportEntities", ExportEntitiesCommand{});
		command_system.register_command("FinalizeBuild", FinalizeBuildCommand{});
		command_system.register_command("PlaySound", PlaySoundCommand{});
		command_system.register_command("PlayMusic", PlayMusicCommand{});

		command_system.push(ExecuteFileCleanCommand{});
		command_system.push(LiteralValueCommand{globals.level_name});

		const double update_time_delta = 10; //100 Updates per second
		int32_t number_of_frames = 0;
		const Time start_frame_time = Time(SDL_GetTicks());
		Time last_update_time = start_frame_time;

		do
		{
			input_system.process_input(globals);
			command_system.process(resource_system, rendering_system, input_system, globals);
			entity_system.clean_removed_entites(all_systems);

			if((SDL_GetTicks()-last_update_time) >= update_time_delta)
			{
				last_update_time += update_time_delta;
				if(globals.app_paused == false)
					all_systems.update(update_time_delta, command_system.procedure_calls());

				input_system.clear_toggle_inputs();
			}

			rendering_system.render_entities(update_time_delta, entity_system, resource_system, globals);

			++number_of_frames;

		} while(globals.app_running == true && globals.app_needs_reload == false);

		std::cout << "FPS = " << 1000.0*number_of_frames / (SDL_GetTicks()-start_frame_time) << std::endl;
		globals.app_needs_reload = false;

	} while(globals.app_running);

	return 0;
}

