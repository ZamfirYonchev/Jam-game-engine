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
#include "commands/fix_view_width_command.h"
#include "commands/select_entity_command.h"
#include "commands/extend_procedure_command.h"
#include "commands/execute_file_command.h"
#include "commands/execute_file_clean_command.h"
#include "commands/clear_procedure_command.h"
#include "commands/pause_command.h"
#include "commands/reload_command.h"
#include "commands/quit_command.h"
#include "commands/clear_all_entities_command.h"
#include "commands/clear_all_textures_command.h"
#include "commands/clear_all_animations_command.h"
#include "commands/clear_all_procedures_command.h"
#include "commands/call_procedure_command.h"
#include "commands/add_font_command.h"
#include "commands/add_sound_command.h"
#include "commands/add_music_command.h"
#include "commands/add_texture_from_file_command.h"
#include "commands/add_texture_from_string_command.h"
#include "commands/add_animation_command.h"
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
#include "commands/read_component_command.h"

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
#include "commands/literal_value_command.h"
#include "globals.h"
#include "utilities.h"

#include <list>
#include <utility>
#include <string>
#include <random>
#include <array>

int main(int argc, char** argv)
{
	Globals globals;
	globals(Globals::app_resolution_x) = CommandReturnValue{800.0};
	globals(Globals::app_resolution_y) = CommandReturnValue{600.0};
	globals(Globals::app_fullscreen) = CommandReturnValue{0.0};
	globals(Globals::app_enable_audio) = CommandReturnValue{0.0};
	globals(Globals::app_sound_channels) = CommandReturnValue{2.0};
	globals(Globals::app_window_title) = CommandReturnValue{"Jam engine"};
	globals(Globals::app_running) = CommandReturnValue{1.0};
	globals(Globals::app_paused) = CommandReturnValue{0.0};
	globals(Globals::app_needs_reload) = CommandReturnValue{0.0};
	globals(Globals::app_show_hitboxes) = CommandReturnValue{0.0};
	globals(Globals::app_current_level) = CommandReturnValue{"init.jel"};
	globals(Globals::app_debug_level) = CommandReturnValue{0.0};

	do
	{
		SdlWindow sdl;
		EntitySystem<Position,Control,Movement,Collision,Interaction,Health,Visuals,Sounds> entity_system;
		using ES = decltype(entity_system);
		ResourceSystem resource_system;
		InputSystem input_system;
		RenderingSystem rendering_system;

		ControlSystem<ES> control_system {entity_system};
		MovementSystem<ES> movement_system {entity_system};
		CollisionSystem<ES> collision_system {entity_system};
		DamageSystem<ES> damage_system {entity_system};
		SoundSystem<ES> sound_system {entity_system, resource_system, globals};

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
		command_system.register_command("FixViewWidth", FixViewWidthCommand{});
		command_system.register_command("SelectEntity", SelectEntityCommand{});
		command_system.register_command("Select", SelectEntityCommand{});
		command_system.register_command("ExtendProcedure", ExtendProcedureCommand{});
		command_system.register_command("ClearProcedure", ClearProcedureCommand{});
		command_system.register_command("Pause", PauseCommand{});
		command_system.register_command("Reload", ReloadCommand{});
		command_system.register_command("Quit", QuitCommand{});
		command_system.register_command("ClearAllEntities", ClearAllTexturesCommand{});
		command_system.register_command("ClearAllAnimations", ClearAllAnimationsCommand{});
		command_system.register_command("ClearAllProcedures", ClearAllProceduresCommand{});
		command_system.register_command("ExecuteFile", ExecuteFileCommand{});
		command_system.register_command("ExecuteFileClean", ExecuteFileCleanCommand{});
		command_system.register_command("CallProcedure", CallProcedureCommand{});
		command_system.register_command("Call", CallProcedureCommand{});
		command_system.register_command("AddFont", AddFontCommand{});
		command_system.register_command("AddTextureFromFile", AddTextureFromFileCommand{});
		command_system.register_command("AddTextureFromString", AddTextureFromStringCommand{});
		command_system.register_command("AddAnimation", AddAnimationCommand{});
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
		command_system.register_command("ReadPosition", ReadComponentCommand<Position>{});
		command_system.register_command("ReadControl", ReadComponentCommand<Control>{});
		command_system.register_command("ReadMovement", ReadComponentCommand<Movement>{});
		command_system.register_command("ReadCollision", ReadComponentCommand<Collision>{});
		command_system.register_command("ReadInteraction", ReadComponentCommand<Interaction>{});
		command_system.register_command("ReadHealth", ReadComponentCommand<Health>{});
		command_system.register_command("ReadSounds", ReadComponentCommand<Sounds>{});
		command_system.register_command("ReadVisuals", ReadComponentCommand<Visuals>{});

		//this will load the data from the init.jel file and potentially give new values to the globals
		command_system.push(ExecuteFileCleanCommand{});
		command_system.push(LiteralValueCommand{globals(Globals::app_current_level)});
		command_system.process(resource_system, rendering_system, input_system);

		//this will schedule the loading of the level which should be set in init.jel
		command_system.push(ExecuteFileCleanCommand{});
		command_system.push(LiteralValueCommand{globals(Globals::app_current_level)});

		int res_x = globals(Globals::app_resolution_x).integer();
		int res_y = globals(Globals::app_resolution_y).integer();
		const std::string title = globals(Globals::app_window_title).string();

		sdl.init_video(res_x
					 , res_y
					 , globals(Globals::app_fullscreen).boolean()
					 , true
					 , globals(Globals::app_enable_audio).boolean()
					 , globals(Globals::app_sound_channels).integer()
					 , title.c_str()
					 );

		globals(Globals::app_resolution_x) = CommandReturnValue{res_x, 0};
		globals(Globals::app_resolution_y) = CommandReturnValue{res_y, 0};

		rendering_system.set_renderer(sdl.renderer());
		rendering_system.set_resolution_x(res_x);
		rendering_system.set_resolution_y(res_y);

		const Time update_time_delta = 10; //100 Updates per second
		int32_t number_of_frames = 0;
		const Time start_frame_time = Time(SDL_GetTicks());
		Time last_update_time = start_frame_time;
		Time last_render_time = start_frame_time;

		do
		{
			input_system.process_input(globals, command_system.procedure_calls());
			command_system.process(resource_system, rendering_system, input_system);
			entity_system.clean_removed_entites(all_systems);

			const bool app_paused = globals(Globals::app_paused).boolean();
			const bool show_hitboxes = globals(Globals::app_show_hitboxes).boolean();

			if(SDL_GetTicks()-last_update_time >= update_time_delta)
			{
				last_update_time += update_time_delta;
				all_systems.update(update_time_delta, globals, command_system.procedure_calls());
				input_system.clear_toggle_inputs();
			}

			if(SDL_GetTicks()-last_render_time > 0)
			{
				const Time diff = SDL_GetTicks()-last_render_time;
				last_render_time = SDL_GetTicks();
				rendering_system.render_entities(diff, entity_system, resource_system, app_paused, show_hitboxes);
			}

			++number_of_frames;

		} while(globals(Globals::app_running).boolean() && globals(Globals::app_needs_reload).boolean() == false);

		std::cout << "FPS = " << 1000.0*number_of_frames / (SDL_GetTicks()-start_frame_time) << std::endl;
		globals(Globals::app_needs_reload) = CommandReturnValue{0.0};

	} while(globals(Globals::app_running).boolean());

	return 0;
}

