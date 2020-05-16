/*
 * execute_file_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "execute_file_command.h"
#include "../file_parser.h"
#include "null_command.h"
#include "debug_message_command.h"
#include "set_level_command.h"
#include "select_entity_command.h"
#include "extend_procedure_command.h"
#include "clear_procedure_command.h"
#include "pause_command.h"
#include "quit_command.h"
#include "clear_all_entities_command.h"
#include "clear_all_textures_command.h"
#include "clear_all_spritesheets_command.h"
#include "clear_all_procedures_command.h"
#include "execute_file_clean_command.h"
#include "call_procedure_command.h"
#include "add_font_command.h"
#include "add_texture_from_file_command.h"
#include "add_texture_from_string_command.h"
#include "add_spritesheet_command.h"
#include "add_sprite_command.h"
#include "add_procedure_command.h"
#include "add_character_command.h"
#include "add_platform_command.h"
#include "add_projectile_command.h"
#include "add_zone_command.h"
#include "add_visual_object_command.h"
#include "add_entity_command.h"
#include "remove_entity_command.h"
#include "modify_position_command.h"
#include "modify_control_command.h"
#include "modify_movement_command.h"
#include "modify_collision_command.h"
#include "modify_interaction_command.h"
#include "modify_health_command.h"
#include "modify_visuals_command.h"
#include "use_null_position_command.h"
#include "use_absolute_position_command.h"
#include "use_attached_position_command.h"
#include "use_null_control_command.h"
#include "use_constant_control_command.h"
#include "use_input_control_command.h"
#include "use_input_select_control_command.h"
#include "use_chase_ai_control_command.h"
#include "use_guide_control_command.h"
#include "use_null_movement_command.h"
#include "use_full_movement_command.h"
#include "use_instant_movement_command.h"
#include "use_null_collision_command.h"
#include "use_basic_collision_command.h"
#include "use_damage_collision_command.h"
#include "use_null_interaction_command.h"
#include "use_normal_interaction_command.h"
#include "use_trigger_interaction_command.h"
#include "use_full_interaction_command.h"
#include "use_null_health_command.h"
#include "use_character_health_command.h"
#include "use_timed_health_command.h"
#include "use_attached_health_command.h"
#include "use_null_visuals_command.h"
#include "use_character_visuals_command.h"
#include "use_tiled_visuals_command.h"
#include "use_static_visuals_command.h"
#include "use_health_visuals_command.h"
#include "use_menu_item_visuals_command.h"

void ExecuteFileCommand::execute() const
{
    FileParser file(m_filename);
    std::string token;
    std::string line;
    std::unique_ptr<Command> command;
    double vars[15];

    try
    {
		while(file.read().good())
		{
			file.read() >> token;
			if(file.read().eof())
				break;

			std::cout << "Token is '" << token << "'" << std::endl;
			if(token[0] == '#')
			{
				std::getline(file.read(), line);
				std::cout << "Reading comment: " << token << line << std::endl;
			}
			else if(token == "Null")
			{
				command = std::move(std::make_unique<NullCommand>());
			}
			else if(token == "DebugMessage")
			{
				file.read() >> vars[0];
				std::getline(file.read(), line);
				command = std::move(std::make_unique<DebugMessageCommand>(line, DebugMessageCommand::Severity(vars[0])));
			}
			else if(token == "SetLevel")
			{
				file.read() >> line;
				command = std::move(std::make_unique<SetLevelCommand>(line));
			}
			else if(token == "SelectEntity")
			{
				file.read() >> vars[0];
				command = std::move(std::make_unique<SelectEntityCommand>(EntityID(vars[0])));
			}
			else if(token == "ExtendProcedure")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				command = std::move(std::make_unique<ExtendProcedureCommand>(ProcedureID(vars[0]), int(vars[1])));
			}
			else if(token == "ClearProcedure")
			{
				file.read() >> vars[0];
				command = std::move(std::make_unique<ClearProcedureCommand>(ProcedureID(vars[0])));
			}
			else if(token == "Pause")
			{
				file.read() >> vars[0];
				command = std::move(std::make_unique<PauseCommand>(bool(vars[0])));
			}
			else if(token == "Quit")
			{
				command = std::move(std::make_unique<QuitCommand>());
			}
			else if(token == "ClearAllEntities")
			{
				command = std::move(std::make_unique<ClearAllEntitiesCommand>());
			}
			else if(token == "ClearAllTextures")
			{
				command = std::move(std::make_unique<ClearAllTexturesCommand>());
			}
			else if(token == "ClearAllSpritesheets")
			{
				command = std::move(std::make_unique<ClearAllSpritesheetsCommand>());
			}
			else if(token == "ClearAllProcedures")
			{
				command = std::move(std::make_unique<ClearAllProceduresCommand>());
			}
			else if(token == "ExecuteFile")
			{
				file.read() >> line;
				command = std::move(std::make_unique<ExecuteFileCommand>(line, m_renderer));
			}
			else if(token == "ExecuteFileClean")
			{
				file.read() >> line;
				command = std::move(std::make_unique<ExecuteFileCleanCommand>(line, m_renderer));
			}
			else if(token == "CallProcedure")
			{
				file.read() >> vars[0];
				command = std::move(std::make_unique<CallProcedureCommand>(ProcedureID(vars[0])));
			}
			else if(token == "AddFont")
			{
				file.read() >> vars[0];
				file.read() >> line;
				command = std::move(std::make_unique<AddFontCommand>(line, int(vars[0])));
			}
			else if(token == "AddTextureFromFile")
			{
				file.read() >> line;
				command = std::move(std::make_unique<AddTextureFromFileCommand>(line, m_renderer));
			}
			else if(token == "AddTextureFromString")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				file.read() >> vars[2];
				file.read() >> vars[3];
				std::getline(file.read(), line);
				command = std::move(std::make_unique<AddTextureFromStringCommand>(line, FontID(vars[0]), uint8_t(vars[1]), uint8_t(vars[2]), uint8_t(vars[3]), m_renderer));
			}
			else if(token == "AddSpritesheet")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				file.read() >> vars[2];
				file.read() >> vars[3];
				file.read() >> vars[4];
				file.read() >> vars[5];
				file.read() >> vars[6];
				file.read() >> vars[7];
				file.read() >> vars[8];
				file.read() >> vars[9];
				file.read() >> vars[10];
				file.read() >> vars[11];
				file.read() >> vars[12];
				file.read() >> vars[13];
				file.read() >> vars[14];
				command = std::move(std::make_unique<AddSpritesheetCommand>(int(vars[0]), int(vars[1])
												  , int(vars[2]), int(vars[3])
												  , int(vars[4]), int(vars[5])
												  , int(vars[6]), int(vars[7])
												  , int(vars[8]), int(vars[9])
												  , int(vars[10]), int(vars[11])
												  , int(vars[12]), int(vars[13])
												  , double(vars[14])
													));
			}
			else if(token == "AddSprite")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				file.read() >> vars[2];
				file.read() >> vars[3];
				file.read() >> vars[4];
				file.read() >> vars[5];
				command = std::move(std::make_unique<AddSpriteCommand>(SpritesheetID(vars[0]), TextureID(vars[1]), vars[2], vars[3], vars[4], vars[5]));
			}
			else if(token == "AddProcedure")
			{
				file.read() >> vars[0];
				command = std::move(std::make_unique<AddProcedureCommand>(int(vars[0])));
			}
			else if(token == "AddCharacter")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				file.read() >> vars[2];
				file.read() >> vars[3];
				file.read() >> vars[4];
				file.read() >> vars[5];
				command = std::move(std::make_unique<AddCharacterCommand>(vars[0], vars[1], vars[2], vars[3], vars[4], SpritesheetID(vars[5])));
			}
			else if(token == "AddPlatform")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				file.read() >> vars[2];
				file.read() >> vars[3];
				file.read() >> vars[4];
				file.read() >> vars[5];
				file.read() >> vars[6];
				command = std::move(std::make_unique<AddPlatformCommand>(vars[0], vars[1], vars[2], vars[3], SpritesheetID(vars[4]), vars[5], vars[6]));
			}
			else if(token == "AddProjectile")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				file.read() >> vars[2];
				file.read() >> vars[3];
				file.read() >> vars[4];
				command = std::move(std::make_unique<AddProjectileCommand>(vars[0], vars[1], vars[2], vars[3], SpritesheetID(vars[4])));
			}
			else if(token == "AddZone")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				file.read() >> vars[2];
				file.read() >> vars[3];
				file.read() >> vars[4];
				file.read() >> vars[5];
				file.read() >> vars[6];
				file.read() >> vars[7];
				command = std::move(std::make_unique<AddZoneCommand>(vars[0], vars[1], vars[2], vars[3], int8_t(vars[4]), ProcedureID(vars[5]), ProcedureID(vars[6]), ProcedureID(vars[7])));
			}
			else if(token == "AddVisualObject")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				file.read() >> vars[2];
				file.read() >> vars[3];
				file.read() >> vars[4];
				file.read() >> vars[5];
				command = std::move(std::make_unique<AddVisualObjectCommand>(vars[0], vars[1], vars[2], vars[3], SpritesheetID(vars[4]), int(vars[5])));
			}
			else if(token == "AddEntity")
			{
				command = std::move(std::make_unique<AddEntityCommand>());
			}
			else if(token == "RemoveEntity")
			{
				command = std::move(std::make_unique<RemoveEntityCommand>());
			}
			else if(token == "ModifyPosition")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				file.read() >> vars[2];
				file.read() >> vars[3];
				command = std::move(std::make_unique<ModifyPositionCommand>(vars[0], vars[1], vars[2], vars[3]));
			}
			else if(token == "ModifyControl")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				file.read() >> vars[2];
				file.read() >> vars[3];
				file.read() >> vars[4];
				command = std::move(std::make_unique<ModifyControlCommand>(vars[0], vars[1], vars[2], vars[3], vars[4]));
			}
			else if(token == "ModifyMovement")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				file.read() >> vars[2];
				file.read() >> vars[3];
				file.read() >> vars[4];
				command = std::move(std::make_unique<ModifyMovementCommand>(vars[0], vars[1], vars[2], vars[3], vars[4]));
			}
			else if(token == "ModifyCollision")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				file.read() >> vars[2];
				command = std::move(std::make_unique<ModifyCollisionCommand>(vars[0], vars[1], vars[2]));
			}
			else if(token == "ModifyInteraction")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				file.read() >> vars[2];
				file.read() >> vars[3];
				file.read() >> vars[4];
				file.read() >> vars[5];
				command = std::move(std::make_unique<ModifyInteractionCommand>(vars[0], vars[1], vars[2], vars[3], vars[4], vars[5]));
			}
			else if(token == "ModifyHealth")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				file.read() >> vars[2];
				command = std::move(std::make_unique<ModifyHealthCommand>(vars[0], vars[1], vars[2]));
			}
			else if(token == "ModifyVisuals")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				file.read() >> vars[2];
				file.read() >> vars[3];
				file.read() >> vars[4];
				command = std::move(std::make_unique<ModifyVisualsCommand>(vars[0], vars[1], vars[2], vars[3], vars[4]));
			}
			else if(token == "UseNullPosition")
			{
				command = std::move(std::make_unique<UseNullPositionCommand>());
			}
			else if(token == "UseAbsolutePosition")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				file.read() >> vars[2];
				file.read() >> vars[3];
				command = std::move(std::make_unique<UseAbsolutePositionCommand>(AbsolutePosition(vars[0], vars[1], vars[2], vars[3])));
			}
			else if(token == "UseAttachedPosition")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				file.read() >> vars[2];
				file.read() >> vars[3];
				file.read() >> vars[4];
				command = std::move(std::make_unique<UseAttachedPositionCommand>(EntityID(vars[0]), vars[1], vars[2], vars[3], vars[4]));
			}
			else if(token == "UseNullControl")
			{
				command = std::move(std::make_unique<UseNullControlCommand>());
			}
			else if(token == "UseConstantControl")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				file.read() >> vars[2];
				file.read() >> vars[3];
				command = std::move(std::make_unique<UseConstantControlCommand>(int8_t(vars[0]), bool(vars[1]), bool(vars[2]), Control::LookDir(vars[3])));
			}
			else if(token == "UseInputControl")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				command = std::move(std::make_unique<UseInputControlCommand>(ProcedureID(vars[0]), vars[1]));
			}
			else if(token == "UseInputSelectControl")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				file.read() >> vars[2];
				command = std::move(std::make_unique<UseInputSelectControlCommand>(int(vars[0]), int(vars[1]), ProcedureID(vars[2])));
			}
			else if(token == "UseChaseAIControl")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				file.read() >> vars[2];
				file.read() >> vars[3];
				command = std::move(std::make_unique<UseChaseAIControlCommand>(EntityID(vars[0]), ProcedureID(vars[1]), vars[2], vars[3]));
			}
			else if(token == "UseGuideControl")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				file.read() >> vars[2];
				file.read() >> vars[3];
				command = std::move(std::make_unique<UseGuideControlCommand>(EntityID(vars[0]), ProcedureID(vars[1]), vars[2], vars[3]));
			}
			else if(token == "UseNullMovement")
			{
				command = std::move(std::make_unique<UseNullMovementCommand>());
			}
			else if(token == "UseFullMovement")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				file.read() >> vars[2];
				file.read() >> vars[3];
				file.read() >> vars[4];
				command = std::move(std::make_unique<UseFullMovementCommand>(vars[0], vars[1], vars[2], vars[3], bool(vars[4])));
			}
			else if(token == "UseInstantMovement")
			{
				file.read() >> vars[0];
				command = std::move(std::make_unique<UseInstantMovementCommand>(vars[0]));
			}
			else if(token == "UseNullCollision")
			{
				command = std::move(std::make_unique<UseNullCollisionCommand>());
			}
			else if(token == "UseBasicCollision")
			{
				file.read() >> vars[0];
				command = std::move(std::make_unique<UseBasicCollisionCommand>(Collision::CollisionState(vars[0])));
			}
			else if(token == "UseDamageCollision")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				command = std::move(std::make_unique<UseDamageCollisionCommand>(Collision::CollisionState(vars[0]), vars[1]));
			}
			else if(token == "UseNullInteraction")
			{
				command = std::move(std::make_unique<UseNullInteractionCommand>());
			}
			else if(token == "UseNormalInteraction")
			{
				file.read() >> vars[0];
				command = std::move(std::make_unique<UseNormalInteractionCommand>(int32_t(vars[0])));
			}
			else if(token == "UseTriggerInteraction")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				file.read() >> vars[2];
				file.read() >> vars[3];
				command = std::move(std::make_unique<UseTriggerInteractionCommand>(int8_t(vars[0]), ProcedureID(vars[1]), ProcedureID(vars[2]), ProcedureID(vars[3])));
			}
			else if(token == "UseFullInteraction")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				file.read() >> vars[2];
				file.read() >> vars[3];
				file.read() >> vars[4];
				command = std::move(std::make_unique<UseFullInteractionCommand>(int32_t(vars[0]), int8_t(vars[1]), ProcedureID(vars[2]), ProcedureID(vars[3]), ProcedureID(vars[4])));
			}
			else if(token == "UseNullHealth")
			{
				command = std::move(std::make_unique<UseNullHealthCommand>());
			}
			else if(token == "UseAttachedHealth")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				file.read() >> vars[2];
				command = std::move(std::make_unique<UseAttachedHealthCommand>(EntityID(vars[0]), vars[1], vars[2]));
			}
			else if(token == "UseCharacterHealth")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				command = std::move(std::make_unique<UseCharacterHealthCommand>(vars[0], vars[1]));
			}
			else if(token == "UseTimedHealth")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				command = std::move(std::make_unique<UseTimedHealthCommand>(vars[0], ProcedureID(vars[1])));
			}
			else if(token == "UseNullVisuals")
			{
				command = std::move(std::make_unique<UseNullVisualsCommand>());
			}
			else if(token == "UseCharacterVisuals")
			{
				file.read() >> vars[0];
				command = std::move(std::make_unique<UseCharacterVisualsCommand>(SpritesheetID(vars[0])));
			}
			else if(token == "UseTiledVisuals")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				file.read() >> vars[2];
				command = std::move(std::make_unique<UseTiledVisualsCommand>(SpritesheetID(vars[0]), uint16_t(vars[1]), uint16_t(vars[2])));
			}
			else if(token == "UseStaticVisuals")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				command = std::move(std::make_unique<UseStaticVisualsCommand>(SpritesheetID(vars[0]), int(vars[1])));
			}
			else if(token == "UseHealthVisuals")
			{
				file.read() >> vars[0];
				file.read() >> vars[1];
				command = std::move(std::make_unique<UseHealthVisualsCommand>(SpritesheetID(vars[0]), uint16_t(vars[1])));
			}
			else if(token == "UseMenuItemVisuals")
			{
				file.read() >> vars[0];
				command = std::move(std::make_unique<UseMenuItemVisualsCommand>(SpritesheetID(vars[0])));
			}
			else
			{
				std::cout << "Error while parsing file " << m_filename << ": Unknown token " << token << std::endl;
			}

			if(file.read().fail())
			{
				std::cerr << "Error while parsing file " << m_filename << ": Parameters of token " << token << std::endl;
			}
			else
			{
				if(command) globals.command_queue.push(std::move(command));
			}
		}
    }
    catch(std::ifstream::failure& except)
    {
    	//error message
    }
}

