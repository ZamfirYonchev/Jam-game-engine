/*
 * execute_file_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "execute_file_command.h"
#include "../file_parser.h"
#include "../globals.h"
#include "null_command.h"
#include "debug_message_command.h"
#include "set_level_command.h"
#include "fix_view_width_command.h"
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
#include "reuse_position_command.h"
#include "../utilities.h"

void ExecuteFileCommand::execute() const
{
	std::ifstream file(m_filename);
	std::cout << "Parsing file " << m_filename << std::endl;
    process_stream(file, m_renderer, false);
}

void ExecuteFileCommand::process_stream(std::istream& input, SDL_Renderer* renderer, bool insert_mode)
{
    std::string line;
    std::unique_ptr<Command> command;
    double vars[15];

    while(input.good())
    {
    	const std::string token { [&](){ std::string result; input >> result; return result; }() };
        if(input.eof())
            break;

        std::cout << "Token is '" << token << "'" << std::endl;
        if(token[0] == '#')
        {
            std::getline(input, line);
            std::cout << "Reading comment: " << token << line << std::endl;
        }
        else
        	switch(hash(token.c_str()))
        	{
			case hash("Null"):
				command = std::make_unique<NullCommand>();
				break;

			case hash("DebugMessage"):
				input >> vars[0];
				std::getline(input, line);
				command = std::make_unique<DebugMessageCommand>(line, DebugMessageCommand::Severity(vars[0]));
				break;

			case hash("SetLevel"):
				input >> line;
				command = std::make_unique<SetLevelCommand>(line);
				break;

			case hash("FixViewWidth"):
				command = std::make_unique<FixViewWidthCommand>();
				break;

			case hash("SelectEntity"):
				input >> vars[0];
				command = std::make_unique<SelectEntityCommand>(EntityID(vars[0]));
				break;

			case hash("ExtendProcedure"):
				input >> vars[0];
				input >> vars[1];
				command = std::make_unique<ExtendProcedureCommand>(ProcedureID(vars[0]), int(vars[1]));
				break;

			case hash("ClearProcedure"):
				input >> vars[0];
				command = std::make_unique<ClearProcedureCommand>(ProcedureID(vars[0]));
				break;

			case hash("Pause"):
				input >> vars[0];
				command = std::make_unique<PauseCommand>(bool(vars[0]));
				break;

			case hash("Quit"):
				command = std::make_unique<QuitCommand>();
			break;

			case hash("ClearAllEntities"):
				command = std::make_unique<ClearAllEntitiesCommand>();
			break;

			case hash("ClearAllTextures"):
				command = std::make_unique<ClearAllTexturesCommand>();
			break;

			case hash("ClearAllSpritesheets"):
				command = std::make_unique<ClearAllSpritesheetsCommand>();
			break;

			case hash("ClearAllProcedures"):
				command = std::make_unique<ClearAllProceduresCommand>();
			break;

			case hash("ExecuteFile"):
				input >> line;
				command = std::make_unique<ExecuteFileCommand>(line, renderer);
				break;

			case hash("ExecuteFileClean"):
				input >> line;
				command = std::make_unique<ExecuteFileCleanCommand>(line, renderer);
				break;

			case hash("CallProcedure"):
				input >> vars[0];
				command = std::make_unique<CallProcedureCommand>(ProcedureID(vars[0]));
				break;

			case hash("AddFont"):
				input >> vars[0];
				input >> line;
				command = std::make_unique<AddFontCommand>(line, int(vars[0]));
				break;

			case hash("AddTextureFromFile"):
				input >> line;
				command = std::make_unique<AddTextureFromFileCommand>(line, renderer);
				break;

			case hash("AddTextureFromString"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				input >> vars[3];
				std::getline(input, line);
				command = std::make_unique<AddTextureFromStringCommand>(line, FontID(vars[0]), uint8_t(vars[1]), uint8_t(vars[2]), uint8_t(vars[3]), renderer);
				break;

			case hash("AddSpritesheet"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				input >> vars[3];
				input >> vars[4];
				input >> vars[5];
				input >> vars[6];
				input >> vars[7];
				input >> vars[8];
				input >> vars[9];
				input >> vars[10];
				input >> vars[11];
				input >> vars[12];
				input >> vars[13];
				input >> vars[14];
				command = std::make_unique<AddSpritesheetCommand>(int(vars[0]), int(vars[1])
												  , int(vars[2]), int(vars[3])
												  , int(vars[4]), int(vars[5])
												  , int(vars[6]), int(vars[7])
												  , int(vars[8]), int(vars[9])
												  , int(vars[10]), int(vars[11])
												  , int(vars[12]), int(vars[13])
												  , double(vars[14])
													);
				break;

			case hash("AddSprite"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				input >> vars[3];
				input >> vars[4];
				input >> vars[5];
				command = std::make_unique<AddSpriteCommand>(SpritesheetID(vars[0]), TextureID(vars[1]), vars[2], vars[3], vars[4], vars[5]);
				break;

			case hash("AddProcedure"):
				input >> vars[0];
				command = std::make_unique<AddProcedureCommand>(int(vars[0]));
				break;

			case hash("AddCharacter"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				input >> vars[3];
				input >> vars[4];
				input >> vars[5];
				command = std::make_unique<AddCharacterCommand>(vars[0], vars[1], vars[2], vars[3], vars[4], SpritesheetID(vars[5]));
				break;

			case hash("AddPlatform"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				input >> vars[3];
				input >> vars[4];
				input >> vars[5];
				input >> vars[6];
				command = std::make_unique<AddPlatformCommand>(vars[0], vars[1], vars[2], vars[3], SpritesheetID(vars[4]), vars[5], vars[6]);
				break;

			case hash("AddProjectile"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				input >> vars[3];
				input >> vars[4];
				command = std::make_unique<AddProjectileCommand>(vars[0], vars[1], vars[2], vars[3], SpritesheetID(vars[4]));
				break;

			case hash("AddZone"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				input >> vars[3];
				input >> vars[4];
				input >> vars[5];
				input >> vars[6];
				input >> vars[7];
				command = std::make_unique<AddZoneCommand>(vars[0], vars[1], vars[2], vars[3], int8_t(vars[4]), ProcedureID(vars[5]), ProcedureID(vars[6]), ProcedureID(vars[7]));
				break;

			case hash("AddVisualObject"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				input >> vars[3];
				input >> vars[4];
				input >> vars[5];
				command = std::make_unique<AddVisualObjectCommand>(vars[0], vars[1], vars[2], vars[3], SpritesheetID(vars[4]), int(vars[5]));
				break;

			case hash("AddEntity"):
				command = std::make_unique<AddEntityCommand>();
				break;

			case hash("RemoveEntity"):
				command = std::make_unique<RemoveEntityCommand>();
				break;

			case hash("ModifyPosition"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				input >> vars[3];
				command = std::make_unique<ModifyPositionCommand>(vars[0], vars[1], vars[2], vars[3]);
				break;

			case hash("ModifyControl"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				input >> vars[3];
				input >> vars[4];
				command = std::make_unique<ModifyControlCommand>(vars[0], vars[1], vars[2], vars[3], vars[4]);
				break;

			case hash("ModifyMovement"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				input >> vars[3];
				input >> vars[4];
				input >> vars[5];
				input >> vars[6];
				command = std::make_unique<ModifyMovementCommand>(vars[0], vars[1], vars[2], vars[3], vars[4], vars[5], vars[6]);
				break;

			case hash("ModifyCollision"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				command = std::make_unique<ModifyCollisionCommand>(vars[0], vars[1], vars[2]);
				break;

			case hash("ModifyInteraction"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				input >> vars[3];
				input >> vars[4];
				input >> vars[5];
				command = std::make_unique<ModifyInteractionCommand>(vars[0], vars[1], vars[2], vars[3], vars[4], vars[5]);
				break;

			case hash("ModifyHealth"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				command = std::make_unique<ModifyHealthCommand>(vars[0], vars[1], vars[2]);
				break;

			case hash("ModifyVisuals"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				input >> vars[3];
				input >> vars[4];
				command = std::make_unique<ModifyVisualsCommand>(vars[0], vars[1], vars[2], vars[3], vars[4]);
				break;

			case hash("UseNullPosition"):
				command = std::make_unique<UseNullPositionCommand>();
				break;

			case hash("UseAbsolutePosition"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				input >> vars[3];
				command = std::make_unique<UseAbsolutePositionCommand>(AbsolutePosition(vars[0], vars[1], vars[2], vars[3]));
				break;

			case hash("UseAttachedPosition"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				input >> vars[3];
				input >> vars[4];
				command = std::make_unique<UseAttachedPositionCommand>(EntityID(vars[0]), vars[1], vars[2], vars[3], vars[4]);
				break;

			case hash("UseNullControl"):
				command = std::make_unique<UseNullControlCommand>();
				break;

			case hash("UseConstantControl"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				input >> vars[3];
				command = std::make_unique<UseConstantControlCommand>(int8_t(vars[0]), bool(vars[1]), bool(vars[2]), Control::LookDir(vars[3]));
				break;

			case hash("UseInputControl"):
				input >> vars[0];
				input >> vars[1];
				command = std::make_unique<UseInputControlCommand>(ProcedureID(vars[0]), vars[1]);
				break;

			case hash("UseInputSelectControl"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				command = std::make_unique<UseInputSelectControlCommand>(int(vars[0]), int(vars[1]), ProcedureID(vars[2]));
				break;

			case hash("UseChaseAIControl"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				input >> vars[3];
				command = std::make_unique<UseChaseAIControlCommand>(EntityID(vars[0]), ProcedureID(vars[1]), vars[2], vars[3]);
				break;

			case hash("UseGuideControl"):
				input >> vars[0];
				input >> vars[1];
				command = std::make_unique<UseGuideControlCommand>(EntityID(vars[0]), vars[1]);
				break;

			case hash("UseNullMovement"):
				command = std::make_unique<UseNullMovementCommand>();
			break;

			case hash("UseFullMovement"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				input >> vars[3];
				input >> vars[4];
				command = std::make_unique<UseFullMovementCommand>(vars[0], vars[1], vars[2], vars[3], bool(vars[4]));
				break;

			case hash("UseInstantMovement"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				command = std::make_unique<UseInstantMovementCommand>(vars[0], vars[1], vars[2]);
				break;

			case hash("UseNullCollision"):
				command = std::make_unique<UseNullCollisionCommand>();
			break;

			case hash("UseBasicCollision"):
				input >> vars[0];
				command = std::make_unique<UseBasicCollisionCommand>(Collision::CollisionState(vars[0]));
				break;

			case hash("UseDamageCollision"):
				input >> vars[0];
				input >> vars[1];
				command = std::make_unique<UseDamageCollisionCommand>(Collision::CollisionState(vars[0]), vars[1]);
				break;

			case hash("UseNullInteraction"):
				command = std::make_unique<UseNullInteractionCommand>();
				break;

			case hash("UseNormalInteraction"):
				input >> vars[0];
				command = std::make_unique<UseNormalInteractionCommand>(int32_t(vars[0]));
				break;

			case hash("UseTriggerInteraction"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				input >> vars[3];
				command = std::make_unique<UseTriggerInteractionCommand>(int8_t(vars[0]), ProcedureID(vars[1]), ProcedureID(vars[2]), ProcedureID(vars[3]));
				break;

			case hash("UseFullInteraction"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				input >> vars[3];
				input >> vars[4];
				command = std::make_unique<UseFullInteractionCommand>(int32_t(vars[0]), int8_t(vars[1]), ProcedureID(vars[2]), ProcedureID(vars[3]), ProcedureID(vars[4]));
				break;

			case hash("UseNullHealth"):
				command = std::move(std::make_unique<UseNullHealthCommand>());
				break;

			case hash("UseAttachedHealth"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				command = std::make_unique<UseAttachedHealthCommand>(EntityID(vars[0]), vars[1], vars[2]);
				break;

			case hash("UseCharacterHealth"):
				input >> vars[0];
				input >> vars[1];
				command = std::make_unique<UseCharacterHealthCommand>(vars[0], vars[1]);
				break;

			case hash("UseTimedHealth"):
				input >> vars[0];
				input >> vars[1];
				command = std::make_unique<UseTimedHealthCommand>(vars[0], ProcedureID(vars[1]));
				break;

			case hash("UseNullVisuals"):
				command = std::make_unique<UseNullVisualsCommand>();
				break;

			case hash("UseCharacterVisuals"):
				input >> vars[0];
				command = std::make_unique<UseCharacterVisualsCommand>(SpritesheetID(vars[0]));
				break;

			case hash("UseTiledVisuals"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				command = std::make_unique<UseTiledVisualsCommand>(SpritesheetID(vars[0]), uint16_t(vars[1]), uint16_t(vars[2]));
				break;

			case hash("UseStaticVisuals"):
				input >> vars[0];
				input >> vars[1];
				command = std::make_unique<UseStaticVisualsCommand>(SpritesheetID(vars[0]), int(vars[1]));
				break;

			case hash("UseHealthVisuals"):
				input >> vars[0];
				input >> vars[1];
				command = std::make_unique<UseHealthVisualsCommand>(SpritesheetID(vars[0]), uint16_t(vars[1]));
				break;

			case hash("UseMenuItemVisuals"):
				input >> vars[0];
				command = std::make_unique<UseMenuItemVisualsCommand>(SpritesheetID(vars[0]));
				break;

			case hash("ReusePosition"):
				input >> vars[0];
				command = std::make_unique<ReusePositionCommand>(EntityID(vars[0]), renderer);
				break;

			default:
				std::cerr << "Parsing error: Unknown token " << token << std::endl;
			    break;
        	}

        if(input.fail())
        {
            std::cerr << "Parsing error: Parameters of token " << token << std::endl;
        }
        else if(command)
        {
			if(insert_mode)
				command_queue().insert_next(std::move(command));
			else
				command_queue().push(std::move(command));
        }
    }
}
