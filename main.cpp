/*
 * main.cpp
 *
 *  Created on: Nov 7, 2019
 *      Author: zamfi
 */

//zamfir.yonchev @ gmail.com

#include "sdl_window.h"
#include "math_ext.h"
#include "commands/execute_file_command.h"
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
//#include "systems/movement_collision_system.h"

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
#include "commands/pause_all_sounds_command.h"

#include "components/absolute_position.h"
#include "components/attached_position.h"
#include "components/build_position.h"
#include "components/attached_directional_position.h"
#include "components/null_position.h"
#include "components/constant_control.h"
#include "components/chase_ai_control.h"
#include "components/guide_control.h"
#include "components/input_control.h"
#include "components/input_select_control.h"
#include "components/particle_control.h"
#include "components/timed_control.h"
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
#include "components/attached_interaction.h"
#include "components/null_interaction.h"
#include "components/attached_health.h"
#include "components/character_health.h"
#include "components/timed_health.h"
#include "components/null_health.h"
#include "components/character_visuals.h"
#include "components/flying_character_visuals.h"
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
#include "command_value_extractor.h"

#include <list>
#include <utility>
#include <string>
#include <random>
#include <array>
#include <variant>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
	Globals globals;
	globals(Globals::app_resolution_x) = CommandValue{800};
	globals(Globals::app_resolution_y) = CommandValue{600};
	globals(Globals::app_fullscreen) = CommandValue{false};
	globals(Globals::app_enable_audio) = CommandValue{false};
	globals(Globals::app_sound_channels) = CommandValue{2};
	globals(Globals::app_window_title) = CommandValue{"Jam engine"};
	globals(Globals::app_running) = CommandValue{true};
	globals(Globals::app_paused) = CommandValue{false};
	globals(Globals::app_needs_reload) = CommandValue{false};
	globals(Globals::app_show_hitboxes) = CommandValue{false};
	globals(Globals::app_current_level) = CommandValue{"init.jel"};
	globals(Globals::app_debug_level) = CommandValue{0};

	do
	{
		CommandSystem command_system {globals};
		using CS = decltype(command_system);

		command_system.register_command("ExecuteFile", ExecuteFileCommand{command_system});

		//this will load the data from the init.jel file and potentially give new values to the globals
		if(globals(Globals::app_current_level).string_view() == "init.jel")
		{
			command_system.external_commands() << "ExecuteFile 'init.jel'\n";
			command_system.process();
		}

		//this will schedule the loading of the level which should be set in init.jel
		command_system.external_commands() << "ExecuteFile '" << globals(Globals::app_current_level).string_view() << "'\n";

		bool sdl_initialized;
		SdlWindow sdl
				  { globals(Globals::app_resolution_x).integer()
				  , globals(Globals::app_resolution_y).integer()
				  , globals(Globals::app_fullscreen).boolean()
				  , globals(Globals::app_enable_audio).boolean()
				  , globals(Globals::app_sound_channels).integer()
				  , globals(Globals::app_window_title).string_view()
				  , sdl_initialized
				  };

		if(sdl_initialized == false)
		{
			std::cerr << "Exiting..." << std::endl;
			return -1;
		}

		globals(Globals::app_resolution_x) = CommandValue{sdl.res_width()};
		globals(Globals::app_resolution_y) = CommandValue{sdl.res_height()};

		EntitySystem<Position,Control,Movement,Collision,Interaction,Health,Visuals,Sounds> entity_system;
		using ES = decltype(entity_system);
		ResourceSystem resource_system;
		InputSystem input_system;

		ControlSystem<ES> control_system {entity_system, globals, command_system.external_commands()};
		MovementSystem<ES> movement_system {entity_system, globals};
		CollisionSystem<ES> collision_system {entity_system, globals, command_system.external_commands()};
		//MovementCollisionSystem<ES> movement_collision_system {entity_system, globals, command_system.external_commands()};
		DamageSystem<ES> damage_system {entity_system, globals, command_system.external_commands()};
		SoundSystem<ES> sound_system {entity_system, resource_system, globals};
		RenderingSystem<ES, ResourceSystem> rendering_system
			{ entity_system
			, resource_system
			, globals
			, sdl
			};

		using RS = decltype(rendering_system);

		AllSystems all_systems
		{ control_system
		, movement_system
		, collision_system
		//, movement_collision_system
		, damage_system
		, sound_system
		};

		using AS = decltype(all_systems);

		std::mt19937 rand_gen {std::random_device{}()};

		UseComponentCommandGenerator<ES, AS, RS, CS> use_command_gen
													 { entity_system
													 , all_systems
													 , rendering_system
													 , command_system
													 , globals
													 };

        CommandValueExtractor<CommandSystem> command_value_extractor{command_system};

		ES::ComponentAccessor<Position> position_accessor{entity_system};
		ES::ComponentAccessor<Control> control_accessor{entity_system};
		ES::ComponentAccessor<Movement> movement_accessor{entity_system};
		ES::ComponentAccessor<Collision> collision_accessor{entity_system};
		ES::ComponentAccessor<Interaction> interaction_accessor{entity_system};
		ES::ComponentAccessor<Health> health_accessor{entity_system};
		ES::ComponentAccessor<Sounds> sounds_accessor{entity_system};
		ES::ComponentAccessor<Visuals> visuals_accessor{entity_system};
		const auto current_id_accessor = [&](){ return EntityID(globals(Globals::selected_entity).integer()); };

	    command_system.register_command("Set", SetVariableCommand{command_system, globals});
	    command_system.register_command("Val", GetVariableCommand{command_system, globals});
	    command_system.register_command("DebugMessage", DebugMessageCommand{command_system, globals});
		command_system.register_command("FixViewWidth", FixViewWidthCommand{entity_system, command_system, globals});
		command_system.register_command("SelectEntity", SelectEntityCommand{command_system, globals});
		command_system.register_command("Select", SelectEntityCommand{command_system, globals});
		command_system.register_command("ExtendProcedure", ExtendProcedureCommand{command_system});
		command_system.register_command("ClearProcedure", ClearProcedureCommand{command_system});
		command_system.register_command("Pause", PauseCommand{command_system, globals});
		command_system.register_command("Reload", ReloadCommand{globals});
		command_system.register_command("Quit", QuitCommand{globals});
		command_system.register_command("ClearAllTextures", ClearAllTexturesCommand{resource_system});
		command_system.register_command("ClearAllEntities", ClearAllEntitiesCommand{entity_system, all_systems});
		command_system.register_command("ClearAllAnimations", ClearAllAnimationsCommand{resource_system});
		command_system.register_command("ClearAllProcedures", ClearAllProceduresCommand{command_system});
		command_system.register_command("ExecuteFileClean", ExecuteFileCleanCommand{entity_system, command_system, all_systems, rendering_system, resource_system});
		command_system.register_command("CallProcedure", CallProcedureCommand{command_system, globals});
		command_system.register_command("Call", CallProcedureCommand{command_system, globals});
		command_system.register_command("AddFont", AddFontCommand{command_system, resource_system});
		command_system.register_command("AddTextureFromFile", AddTextureFromFileCommand{command_system, rendering_system, resource_system});
		command_system.register_command("AddTextureFromString", AddTextureFromStringCommand{command_system, rendering_system, resource_system});
		command_system.register_command("AddAnimation", AddAnimationCommand{command_system, resource_system});
		command_system.register_command("AddSprite", AddSpriteCommand{command_system, resource_system});
		command_system.register_command("AddSound", AddSoundCommand{command_system, resource_system, globals});
		command_system.register_command("AddMusic", AddMusicCommand{command_system, resource_system, globals});
		command_system.register_command("AddEntity", AddEntityCommand{entity_system, globals});
		command_system.register_command("RemoveEntity", RemoveEntityCommand{entity_system, globals});
		command_system.register_command("ModifyPosition", ModifyPositionCommand{command_system, entity_system, globals});
		command_system.register_command("ModifyControl", ModifyControlCommand{command_system, entity_system, globals});
		command_system.register_command("ModifyMovement", ModifyMovementCommand{command_system, entity_system, globals});
		command_system.register_command("ModifyCollision", ModifyCollisionCommand{command_system, entity_system, globals});
		command_system.register_command("ModifyInteraction", ModifyInteractionCommand{command_system, entity_system, globals});
		command_system.register_command("ModifyHealth", ModifyHealthCommand{command_system, entity_system, globals});
		command_system.register_command("ModifyVisuals", ModifyVisualsCommand{command_system, entity_system, rendering_system, globals});
		command_system.register_command("UseNullPosition", use_command_gen.make<Position, NullPosition>());
		command_system.register_command("UseAbsolutePosition", use_command_gen.make<Position, AbsolutePosition>(command_value_extractor));
		command_system.register_command("UseAttachedPosition", use_command_gen.make<Position, AttachedPosition>(command_value_extractor, position_accessor));
		command_system.register_command("UseBuildPosition", use_command_gen.make<Position, BuildPosition>(command_value_extractor, position_accessor));
		command_system.register_command("UseAttachedDirectionalPosition", use_command_gen.make<Position, AttachedDirectionalPosition>(command_value_extractor, position_accessor, control_accessor));
		command_system.register_command("UseNullControl", use_command_gen.make<Control, NullControl>());
		command_system.register_command("UseConstantControl", use_command_gen.make<Control, ConstantControl>(command_value_extractor));
		command_system.register_command("UseInputControl", use_command_gen.make<Control, InputControl>(command_value_extractor, input_system, current_id_accessor, movement_accessor));
		command_system.register_command("UseInputSelectControl", use_command_gen.make<Control, InputSelectControl>(command_value_extractor, input_system));
		command_system.register_command("UseChaseAIControl", use_command_gen.make<Control, ChaseAIControl>(command_value_extractor, current_id_accessor, position_accessor));
		command_system.register_command("UseGuideControl", use_command_gen.make<Control, GuideControl>(command_value_extractor, current_id_accessor, position_accessor));
		command_system.register_command("UseParticleControl", use_command_gen.make<Control, ParticleControl>(command_value_extractor, rand_gen));
		command_system.register_command("UseTimedControl", use_command_gen.make<Control, TimedControl>(command_value_extractor));
		command_system.register_command("UseNullMovement", use_command_gen.make<Movement, NullMovement>());
		command_system.register_command("UseFullMovement", use_command_gen.make<Movement, FullMovement>(command_value_extractor));
		command_system.register_command("UseInstantMovement", use_command_gen.make<Movement, InstantMovement>(command_value_extractor));
		command_system.register_command("UseNullCollision", use_command_gen.make<Collision, NullCollision>());
		command_system.register_command("UseBasicCollision", use_command_gen.make<Collision, BasicCollision>(command_value_extractor));
		command_system.register_command("UseDamageCollision", use_command_gen.make<Collision, DamageCollision>(command_value_extractor));
		command_system.register_command("UseNullInteraction", use_command_gen.make<Interaction, NullInteraction>());
		command_system.register_command("UseNormalInteraction", use_command_gen.make<Interaction, NormalInteraction>(command_value_extractor));
		command_system.register_command("UseTriggerInteraction", use_command_gen.make<Interaction, TriggerInteraction>(command_value_extractor));
		command_system.register_command("UseFullInteraction", use_command_gen.make<Interaction, FullInteraction>(command_value_extractor));
		command_system.register_command("UseAttachedInteraction", use_command_gen.make<Interaction, AttachedInteraction>(command_value_extractor, interaction_accessor));
		command_system.register_command("UseNullHealth", use_command_gen.make<Health, NullHealth>());
		command_system.register_command("UseAttachedHealth", use_command_gen.make<Health, AttachedHealth>(command_value_extractor, health_accessor));
		command_system.register_command("UseCharacterHealth", use_command_gen.make<Health, CharacterHealth>(command_value_extractor));
		command_system.register_command("UseTimedHealth", use_command_gen.make<Health, TimedHealth>(command_value_extractor));
		command_system.register_command("UseNullSounds", use_command_gen.make<Sounds, NullSounds>());
		command_system.register_command("UseCharacterSounds", use_command_gen.make<Sounds, CharacterSounds>(command_value_extractor, current_id_accessor, control_accessor, movement_accessor, collision_accessor, health_accessor));
		command_system.register_command("UseNullVisuals", use_command_gen.make<Visuals, NullVisuals>());
		command_system.register_command("UseCharacterVisuals", use_command_gen.make<Visuals, CharacterVisuals>(command_value_extractor, resource_system, current_id_accessor, control_accessor, movement_accessor, collision_accessor, health_accessor));
		command_system.register_command("UseFlyingCharacterVisuals", use_command_gen.make<Visuals, FlyingCharacterVisuals>(command_value_extractor, resource_system, current_id_accessor, control_accessor, collision_accessor, health_accessor));
		command_system.register_command("UseTiledVisuals", use_command_gen.make<Visuals, TiledVisuals>(command_value_extractor, resource_system, current_id_accessor, position_accessor));
		command_system.register_command("UseStaticVisuals", use_command_gen.make<Visuals, StaticVisuals>(command_value_extractor));
		command_system.register_command("UseHealthVisuals", use_command_gen.make<Visuals, HealthVisuals>(command_value_extractor, resource_system, current_id_accessor, health_accessor));
		command_system.register_command("UseMenuItemVisuals", use_command_gen.make<Visuals, MenuItemVisuals>(command_value_extractor, resource_system, current_id_accessor, control_accessor));
		command_system.register_command("UseAnimationVisuals", use_command_gen.make<Visuals, AnimationVisuals>(command_value_extractor, resource_system));
		command_system.register_command("ReusePosition", ReuseComponentCommand<Position, CommandSystem, ES>{command_system, entity_system});
		command_system.register_command("ReuseControl", ReuseComponentCommand<Control, CommandSystem, ES>{command_system, entity_system});
		command_system.register_command("ReuseMovement", ReuseComponentCommand<Movement, CommandSystem, ES>{command_system, entity_system});
		command_system.register_command("ReuseCollision", ReuseComponentCommand<Collision, CommandSystem, ES>{command_system, entity_system});
		command_system.register_command("ReuseInteraction", ReuseComponentCommand<Interaction, CommandSystem, ES>{command_system, entity_system});
		command_system.register_command("ReuseHealth", ReuseComponentCommand<Health, CommandSystem, ES>{command_system, entity_system});
		command_system.register_command("ReuseSounds", ReuseComponentCommand<Sounds, CommandSystem, ES>{command_system, entity_system});
		command_system.register_command("ReuseVisuals", ReuseComponentCommand<Visuals, CommandSystem, ES>{command_system, entity_system});
		command_system.register_command("ExportEntities", ExportEntitiesCommand{command_system, entity_system});
		command_system.register_command("FinalizeBuild", FinalizeBuildCommand{entity_system, all_systems, globals});
		command_system.register_command("PlaySound", PlaySoundCommand{command_system, resource_system, globals});
		command_system.register_command("PlayMusic", PlayMusicCommand{command_system, resource_system, globals});
		command_system.register_command("PauseAllSounds", PauseAllSoundsCommand{command_system, globals});
		command_system.register_command("ReadPosition", ReadPositionCommand{command_system, entity_system});
		command_system.register_command("ReadControl", ReadControlCommand{command_system, entity_system});
		command_system.register_command("ReadMovement", ReadMovementCommand{command_system, entity_system});
		command_system.register_command("ReadCollision", ReadCollisionCommand{command_system, entity_system});
		command_system.register_command("ReadInteraction", ReadInteractionCommand{command_system, entity_system});
		command_system.register_command("ReadHealth", ReadHealthCommand{command_system, entity_system});
		command_system.register_command("ReadSounds", ReadSoundsCommand{command_system, entity_system});
		command_system.register_command("ReadVisuals", ReadVisualsCommand{command_system, entity_system});

		const Time update_time_delta = 10; //100 Updates per second
		int32_t number_of_frames = 0;
		const Time start_frame_time = Time(SDL_GetTicks());
		Time last_update_time = start_frame_time;
		Time last_render_time = start_frame_time;

		do
		{
			input_system.process_input(globals, command_system.external_commands());
			command_system.process();
			entity_system.clean_removed_entites(all_systems);

			if(SDL_GetTicks()-last_update_time >= update_time_delta)
			{
				last_update_time += update_time_delta;
				all_systems.update(update_time_delta);
				input_system.clear_toggle_inputs();
			}

			if(SDL_GetTicks()-last_render_time > 0)
			{
				const Time diff = SDL_GetTicks()-last_render_time;
				last_render_time = SDL_GetTicks();
				rendering_system.update(diff);
				++number_of_frames;
			}

		} while(globals(Globals::app_running).boolean() && globals(Globals::app_needs_reload).boolean() == false);

		std::cout << "FPS = " << 1000.0*number_of_frames / (SDL_GetTicks()-start_frame_time) << std::endl;
		globals(Globals::app_needs_reload) = CommandValue{false};

	} while(globals(Globals::app_running).boolean());

	return 0;
}

