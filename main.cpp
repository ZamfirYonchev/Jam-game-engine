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
#include "commands/add_procedure_command.h"
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

#include <list>
#include <utility>
#include <string>
#include <random>
#include <array>

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
		CommandSystem<ES, AS> command_system {entity_system, all_systems};
		using CS = decltype(command_system);

		std::mt19937 gen {std::random_device{}()};

	    command_system.register_command("DebugMessage",
			[](std::istream& input){
				double severity;
				std::string line;
				input >> severity;
				std::getline(input, line);
				return DebugMessageCommand{line, DebugMessageCommand::Severity(severity)};
			});

		command_system.register_command("SetLevel",
			[](std::istream& input){
				std::string str;
				input >> str;
				return SetLevelCommand{str};
			});

		command_system.register_command("FixViewWidth",
			[](std::istream& input){
				return FixViewWidthCommand{};
			});

		command_system.register_command("SelectEntity",
			[](std::istream& input){
				double id;
				input >> id;
				return SelectEntityCommand{EntityID(id)};
			});

		command_system.register_command("ExtendProcedure",
			[](std::istream& input)
			{
				double id, num_of_cmds;
				input >> id >> num_of_cmds;
				if(id < 0)
				{
					std::cerr << "ExtendProcedure: procedure id must be >= 0\n";
					return CS::CommandT{NullCommand{}};
				}
				else if(num_of_cmds < 0)
				{
					std::cerr << "ExtendProcedure: number of commands must be >= 0\n";
					return CS::CommandT{NullCommand{}};
				}
				else
					return CS::CommandT{ExtendProcedureCommand{ProcedureID(id), int(num_of_cmds)}};
			});

		command_system.register_command("ClearProcedure",
			[](std::istream& input)
			{
				double id;
				input >> id;
				if(id < 0)
				{
					std::cerr << "ClearProcedure: procedure id must be >= 0\n";
					return CS::CommandT{NullCommand{}};
				}
				else
					return CS::CommandT{ClearProcedureCommand{ProcedureID(id)}};
			});

		command_system.register_command("Pause",
			[](std::istream& input){
				double pause;
				input >> pause;
				return PauseCommand{bool(pause)};
			});

		command_system.register_command("Quit",
			[](std::istream& input){
				return QuitCommand{};
			});

		command_system.register_command("ClearAllEntities",
			[](std::istream& input){
				return ClearAllEntitiesCommand{};
			});

		command_system.register_command("ClearAllTextures",
			[](std::istream& input){
				return ClearAllTexturesCommand{};
			});

		command_system.register_command("ClearAllSpritesheets",
			[](std::istream& input){
				return ClearAllSpritesheetsCommand{};
			});

		command_system.register_command("ClearAllProcedures",
			[](std::istream& input){
				return ClearAllProceduresCommand{};
			});

		command_system.register_command("ExecuteFile",
			[](std::istream& input){
				std::string str;
				input >> str;
				return ExecuteFileCommand{str};
			});

		command_system.register_command("ExecuteFileClean",
			[](std::istream& input){
				std::string str;
				input >> str;
				return ExecuteFileCleanCommand{str};
			});

		command_system.register_command("CallProcedure",
			[](std::istream& input)
			{
				double id;
				input >> id;
				if(id < 0)
				{
					std::cerr << "CallProcedure: procedure id must be >= 0\n";
					return CS::CommandT{NullCommand{}};
				}
				else
					return CS::CommandT{CallProcedureCommand{ProcedureID(id)}};
			});

		command_system.register_command("AddFont",
			[](std::istream& input){
				double font_size;
				std::string str;
				input >> font_size >> str;
				return AddFontCommand{str, int(font_size)};
			});

		command_system.register_command("AddTextureFromFile",
			[](std::istream& input){
				std::string str;
				input >> str;
				return AddTextureFromFileCommand{str};
			});

		command_system.register_command("AddTextureFromString",
			[](std::istream& input)
			{
				double id, r, g, b;
				std::string str;
				input >> id >> r >> g >> b;
				std::getline(input, str);
				if(id < 0)
				{
					std::cerr << "AddTextureFromString: font id must be >= 0\n";
					return CS::CommandT{NullCommand{}};
				}
				else
					return CS::CommandT{AddTextureFromStringCommand{str, FontID(id), uint8_t(r), uint8_t(g), uint8_t(b)}};
			});

		command_system.register_command("AddSpritesheet",
			[](std::istream& input){
				double idle_start, idle_size
					 , walk_start, walk_size
					 , jump_start, jump_size
					 , fall_start, fall_size
					 , attack_start, attack_size
					 , hit_start, hit_size
					 , dead_start, dead_size
					 , scale_factor;
				input >> idle_start >> idle_size
					  >> walk_start >> walk_size
					  >> jump_start >> jump_size
					  >> fall_start >> fall_size
					  >> attack_start >> attack_size
					  >> hit_start >> hit_size
				  	  >> dead_start >> dead_size
					  >> scale_factor;
				return AddSpritesheetCommand{
												Spritesheet
													{ uint8_t(idle_start), uint8_t(idle_size)
													, uint8_t(walk_start), uint8_t(walk_size)
													, uint8_t(jump_start), uint8_t(jump_size)
													, uint8_t(fall_start), uint8_t(fall_size)
													, uint8_t(attack_start), uint8_t(attack_size)
													, uint8_t(hit_start), uint8_t(hit_size)
													, uint8_t(dead_start), uint8_t(dead_size)
													, scale_factor
													}
											};
			});

		command_system.register_command("AddSprite",
			[](std::istream& input)
			{
				double spr_id, tex_id, x, y, w, h;
				input >> spr_id >> tex_id >> x >> y >> w >> h;
				if(spr_id < 0)
				{
					std::cerr << "AddSprite: spritesheet id must be >= 0\n";
					return CS::CommandT{NullCommand{}};
				}
				else if(tex_id < 0)
				{
					std::cerr << "AddSprite: texture id must be >= 0\n";
					return CS::CommandT{NullCommand{}};
				}
				else
					return CS::CommandT{AddSpriteCommand{SpritesheetID(spr_id), TextureID(tex_id), int(x), int(y), int(w), int(h)}};
			});

		command_system.register_command("AddProcedure",
			[](std::istream& input)
			{
				double num_of_cmds;
				input >> num_of_cmds;
				if(num_of_cmds < 0)
				{
					std::cerr << "AddProcedure: number of commands must be >= 0\n";
					return CS::CommandT{NullCommand{}};
				}
				else
					return CS::CommandT{AddProcedureCommand{size_t(num_of_cmds)}};
			});

		command_system.register_command("AddSound",
			[](std::istream& input){
				std::string file;
				double repeat;
				input >> file >> repeat;
				return AddSoundCommand{file, int(repeat)};
			});

		command_system.register_command("AddMusic",
			[](std::istream& input){
				std::string file;
				input >> file;
				return AddMusicCommand{file};
			});

		command_system.register_command("AddEntity",
			[](std::istream& input){
				return AddEntityCommand{};
			});

		command_system.register_command("RemoveEntity",
			[](std::istream& input){
				return RemoveEntityCommand{};
			});

		command_system.register_command("ModifyPosition",
			[](std::istream& input){
				double x, y, w, h;
				input >> x >> y >> w >> h;
				return ModifyPositionCommand{x, y, w, h};
			});

		command_system.register_command("ModifyControl",
			[](std::istream& input){
				double vertical, attack, walk, look_dir;
				input >> vertical >> attack >> walk >> look_dir;
				return ModifyControlCommand{vertical, attack, walk, look_dir};
			});

		command_system.register_command("ModifyMovement",
			[](std::istream& input){
				double mass, friction_x, friction_y, vx, vy, fx, fy, gravity_affected;
				input >> mass >> friction_x >> friction_y >> vx >> vy >> fx >> fy >> gravity_affected;
				return ModifyMovementCommand{mass, friction_x, friction_y, vx, vy, fx, fy, gravity_affected};
			});

		command_system.register_command("ModifyCollision",
			[](std::istream& input){
				double state, standing_on, on_collision_damage, elasticity;
				input >> state >> standing_on >> on_collision_damage >> elasticity;
				return ModifyCollisionCommand{state, standing_on, on_collision_damage, elasticity};
			});

		command_system.register_command("ModifyInteraction",
			[](std::istream& input){
				double group, value, trigger_group, proc_id_self, on_exit_proc_id_self, proc_id_other;
				input >> group >> value >> trigger_group >> proc_id_self >> on_exit_proc_id_self >> proc_id_other;
				return ModifyInteractionCommand{group, value, trigger_group, proc_id_self, on_exit_proc_id_self, proc_id_other};
			});

		command_system.register_command("ModifyHealth",
			[](std::istream& input){
				double max_hp, hp, hp_change;
				input >> max_hp >> hp >> hp_change;
				return ModifyHealthCommand{max_hp, hp, hp_change};
			});

		command_system.register_command("ModifyVisuals",
			[](std::istream& input){
				double repeat_x, repeat_y, spr_id, layer;
				input >> repeat_x >> repeat_y >> spr_id >> layer;
				return ModifyVisualsCommand{repeat_x, repeat_y, spr_id, layer};
			});

		command_system.register_command("UseNullPosition",
			[](std::istream& input){
				return UseComponentCommand<NullPosition>{};
			});

		command_system.register_command("UseAbsolutePosition",
			[](std::istream& input){
				double x, y, w, h;
				input >> x >> y >> w >> h;
				return UseComponentCommand<AbsolutePosition>{x, y, w, h};
			});

		command_system.register_command("UseAttachedPosition",
			[&](std::istream& input){
				double id, x, y, w, h;
				input >> id >> x >> y >> w >> h;
				return UseComponentCommand<AttachedPosition<decltype(entity_system)>>{id, x, y, w, h, entity_system};
			});

		command_system.register_command("UseBuildPosition",
			[&](std::istream& input){
				double id;
				input >> id;
				return UseComponentCommand<BuildPosition<decltype(entity_system)>>{EntityID{}, EntityID(id), 0.0, 0.0, entity_system};
			});

		command_system.register_command("UseNullControl",
			[](std::istream& input){
				return UseComponentCommand<NullControl>{};
			});

		command_system.register_command("UseConstantControl",
			[](std::istream& input){
				double move_decision, vertical_decision, look_dir;
				input >> move_decision >> vertical_decision >> look_dir;
				return UseComponentCommand<ConstantControl>{move_decision, vertical_decision, Control::LookDir(look_dir)};
			});

		command_system.register_command("UseInputControl",
			[&](std::istream& input){
				double proc_id, cooldown, stability_control;
				input >> proc_id >> cooldown >> stability_control;
				return UseComponentCommand<InputControl<decltype(entity_system)>>{ProcedureID(proc_id), cooldown, EntityID{}, bool(stability_control), entity_system, input_system};
			});

		command_system.register_command("UseInputSelectControl",
			[&](std::istream& input){
				double select, max, proc_id;
				input >> select >> max >> proc_id;
				return UseComponentCommand<InputSelectControl>{int(select), int(max), ProcedureID(proc_id), input_system};
			});

		command_system.register_command("UseChaseAIControl",
			[&](std::istream& input){
				double target_id, proc_id, cooldown, range;
				input >> target_id >> proc_id >> cooldown >> range;
				return UseComponentCommand<ChaseAIControl<decltype(entity_system)>>{EntityID{}, EntityID(target_id), ProcedureID(proc_id), cooldown, range, entity_system};
			});

		command_system.register_command("UseGuideControl",
			[&](std::istream& input){
				double target_id, range;
				input >> target_id >> range;
				return UseComponentCommand<GuideControl<decltype(entity_system)>>{EntityID{}, EntityID(target_id), range, entity_system};
			});

		command_system.register_command("UseParticleControl",
			[&](std::istream& input){
				double random_factor, directed_factor, direction_angle;
				input >> random_factor >> directed_factor >> direction_angle;
				return UseComponentCommand<ParticleControl>{gen, random_factor, directed_factor, direction_angle};
			});

		command_system.register_command("UseNullMovement",
			[](std::istream& input){
				return UseComponentCommand<NullMovement>{};
			});

		command_system.register_command("UseFullMovement",
			[](std::istream& input){
				double mass, friction_x, friction_y, move_force, jump_force, gravity_affected;
				input >> mass >> friction_x >> friction_y >> move_force >> jump_force >> gravity_affected;
				return UseComponentCommand<FullMovement>{mass, friction_x, friction_y, move_force, jump_force, bool(gravity_affected)};
			});

		command_system.register_command("UseInstantMovement",
			[](std::istream& input){
				double mass, friction_x, friction_y, move_force;
				input >> mass >> friction_x >> friction_y >> move_force;
				return UseComponentCommand<InstantMovement>{mass, friction_x, friction_y, move_force};
			});

		command_system.register_command("UseNullCollision",
			[](std::istream& input){
				return UseComponentCommand<NullCollision>{};
			});

		command_system.register_command("UseBasicCollision",
			[](std::istream& input){
				double state, elasticity;
				input >> state >> elasticity;
				return UseComponentCommand<BasicCollision>{Collision::CollisionState(state), elasticity};
			});

		command_system.register_command("UseDamageCollision",
			[](std::istream& input){
				double state, damage;
				input >> state >> damage;
				return UseComponentCommand<DamageCollision>{Collision::CollisionState(state), damage};
			});

		command_system.register_command("UseNullInteraction",
			[](std::istream& input){
				return UseComponentCommand<NullInteraction>{};
			});

		command_system.register_command("UseNormalInteraction",
			[](std::istream& input){
				double groups;
				input >> groups;
				return UseComponentCommand<NormalInteraction>{int32_t(groups)};
			});

		command_system.register_command("UseTriggerInteraction",
			[](std::istream& input){
				double group, proc_id_self, proc_id_other, proc_id_self_exit;
				input >> group >> proc_id_self >> proc_id_other >> proc_id_self_exit;
				return UseComponentCommand<TriggerInteraction>{int8_t(group), ProcedureID(proc_id_self), ProcedureID(proc_id_other), ProcedureID(proc_id_self_exit)};
			});

		command_system.register_command("UseFullInteraction",
			[](std::istream& input){
				double groups, trigger_group, proc_id_self, proc_id_other, proc_id_self_exit;
				input >> groups >> trigger_group >> proc_id_self >> proc_id_other >> proc_id_self_exit;
				return UseComponentCommand<FullInteraction>{int32_t(groups), int8_t(trigger_group), ProcedureID(proc_id_self), ProcedureID(proc_id_other), ProcedureID(proc_id_self_exit)};
			});

		command_system.register_command("UseNullHealth",
			[](std::istream& input){
				return UseComponentCommand<NullHealth>{};
			});

		command_system.register_command("UseAttachedHealth",
			[&](std::istream& input){
				double attached_id, offset_hp, offset_max_hp;
				input >> attached_id >> offset_hp >> offset_max_hp;
				return UseComponentCommand<AttachedHealth<decltype(entity_system)>>{ProcedureID(attached_id), offset_hp, offset_max_hp, entity_system};
			});

		command_system.register_command("UseCharacterHealth",
			[](std::istream& input){
				double hp, max_hp;
				input >> hp >> max_hp;
				return UseComponentCommand<CharacterHealth>{hp, max_hp};
			});

		command_system.register_command("UseTimedHealth",
			[](std::istream& input){
				double ttl, proc_id;
				input >> ttl >> proc_id;
				return UseComponentCommand<TimedHealth>{ttl, ProcedureID(proc_id)};
			});

		command_system.register_command("UseNullVisuals",
			[](std::istream& input){
				return UseComponentCommand<NullVisuals>{};
			});

		command_system.register_command("UseCharacterVisuals",
			[&](std::istream& input){
				double spr_id;
				input >> spr_id;
				return UseComponentCommand<CharacterVisuals<ES>>{spr_id, EntityID{}, resource_system, entity_system};
			});

		command_system.register_command("UseTiledVisuals",
			[&](std::istream& input){
				double spr_id, w, h;
				input >> spr_id >> w >> h;
				return UseComponentCommand<TiledVisuals<decltype(entity_system)>>{spr_id, w, h, EntityID{}, entity_system};
			});

		command_system.register_command("UseStaticVisuals",
			[](std::istream& input){
				double spr_id, sprite;
				input >> spr_id >> sprite;
				return UseComponentCommand<StaticVisuals>{spr_id, sprite};
			});

		command_system.register_command("UseHealthVisuals",
			[&](std::istream& input){
				double spr_id, repeat_x;
				input >> spr_id >> repeat_x;
				return UseComponentCommand<HealthVisuals<decltype(entity_system)>>{EntityID{}, spr_id, repeat_x, entity_system};
			});

		command_system.register_command("UseMenuItemVisuals",
			[&](std::istream& input){
				double spr_id;
				input >> spr_id;
				return UseComponentCommand<MenuItemVisuals<decltype(entity_system)>>{spr_id, EntityID{}, entity_system};
			});

		command_system.register_command("UseNullSounds",
			[&](std::istream& input){
				return UseComponentCommand<NullSounds>{};
			});

		command_system.register_command("UseCharacterSounds",
			[&](std::istream& input){
				double idle_id, walk_id, jump_id, fall_id, land_id, attack_id, hit_id, dead_id, volume;
				input >> idle_id >> walk_id >> jump_id >> fall_id >> land_id >> attack_id >> hit_id >> dead_id >> volume;
				return UseComponentCommand<CharacterSounds<ES>>{SoundID(idle_id), SoundID(walk_id), SoundID(jump_id), SoundID(fall_id), SoundID(land_id), SoundID(attack_id), SoundID(hit_id), SoundID(dead_id), volume, EntityID{}, entity_system};
			});

		command_system.register_command("ReusePosition",
			[](std::istream& input){
				double id;
				input >> id;
				return ReuseComponentCommand<Position>{EntityID(id)};
			});

		command_system.register_command("ReuseControl",
			[](std::istream& input){
				double id;
				input >> id;
				return ReuseComponentCommand<Control>{EntityID(id)};
			});

		command_system.register_command("ReuseMovement",
			[](std::istream& input){
				double id;
				input >> id;
				return ReuseComponentCommand<Movement>{EntityID(id)};
			});

		command_system.register_command("ReuseCollision",
			[](std::istream& input){
				double id;
				input >> id;
				return ReuseComponentCommand<Collision>{EntityID(id)};
			});

		command_system.register_command("ReuseInteraction",
			[](std::istream& input){
				double id;
				input >> id;
				return ReuseComponentCommand<Interaction>{EntityID(id)};
			});

		command_system.register_command("ReuseHealth",
			[](std::istream& input){
				double id;
				input >> id;
				return ReuseComponentCommand<Health>{EntityID(id)};
			});

		command_system.register_command("ReuseVisuals",
			[](std::istream& input){
				double id;
				input >> id;
				return ReuseComponentCommand<Visuals>{EntityID(id)};
			});

		command_system.register_command("ExportEntities",
			[](std::istream& input){
				std::string file;
				input >> file;
				return ExportEntitiesCommand{file};
			});

		command_system.register_command("FinalizeBuild",
			[](std::istream& input){
				return FinalizeBuildCommand{};
			});

		command_system.register_command("PlaySound",
			[](std::istream& input){
				double sound_id, channel;
				input >> sound_id >> channel;

				if(sound_id < 0)
				{
					std::cerr << "PlaySound: sound id must be >= 0\n";
					return CS::CommandT{NullCommand{}};
				}
				else
					return CS::CommandT{PlaySoundCommand{SoundID(sound_id), int(channel)}};
			});

		command_system.register_command("PlayMusic",
			[](std::istream& input){
				double id, loops;
				input >> id >> loops;

				if(id < 0)
				{
					std::cerr << "PlayMusic: music id must be >= 0\n";
					return CS::CommandT{NullCommand{}};
				}
				else
					return CS::CommandT{PlayMusicCommand{MusicID(id), int(loops)}};
			});


		command_system.push(ExecuteFileCleanCommand{globals.level_name});

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

