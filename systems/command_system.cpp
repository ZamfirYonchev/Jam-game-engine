/*
 * command_system.cpp
 *
 *  Created on: Oct 7, 2020
 *      Author: zamfi
 */

#include "command_system.h"

#include <fstream>
#include "../commands/null_command.h"
#include "../commands/debug_message_command.h"
#include "../commands/set_level_command.h"
#include "../commands/fix_view_width_command.h"
#include "../commands/select_entity_command.h"
#include "../commands/extend_procedure_command.h"
#include "../commands/execute_file_command.h"
#include "../commands/execute_file_clean_command.h"
#include "../commands/clear_procedure_command.h"
#include "../commands/pause_command.h"
#include "../commands/quit_command.h"
#include "../commands/clear_all_entities_command.h"
#include "../commands/clear_all_textures_command.h"
#include "../commands/clear_all_spritesheets_command.h"
#include "../commands/clear_all_procedures_command.h"
#include "../commands/call_procedure_command.h"
#include "../commands/add_font_command.h"
#include "../commands/add_texture_from_file_command.h"
#include "../commands/add_texture_from_string_command.h"
#include "../commands/add_spritesheet_command.h"
#include "../commands/add_sprite_command.h"
#include "../commands/add_procedure_command.h"
#include "../commands/add_entity_command.h"
#include "../commands/remove_entity_command.h"
#include "../commands/modify_position_command.h"
#include "../commands/modify_control_command.h"
#include "../commands/modify_movement_command.h"
#include "../commands/modify_collision_command.h"
#include "../commands/modify_interaction_command.h"
#include "../commands/modify_health_command.h"
#include "../commands/modify_visuals_command.h"
#include "../components/absolute_position.h"
#include "../components/attached_position.h"
#include "../components/build_position.h"
#include "../components/null_position.h"
#include "../components/constant_control.h"
#include "../components/absolute_position.h"
#include "../components/attached_position.h"
#include "../components/null_position.h"
#include "../components/chase_ai_control.h"
#include "../components/constant_control.h"
#include "../components/guide_control.h"
#include "../components/input_control.h"
#include "../components/input_select_control.h"
#include "../components/null_control.h"
#include "../components/full_movement.h"
#include "../components/instant_movement.h"
#include "../components/null_movement.h"
#include "../components/basic_collision.h"
#include "../components/damage_collision.h"
#include "../components/null_collision.h"
#include "../components/full_interaction.h"
#include "../components/normal_interaction.h"
#include "../components/trigger_interaction.h"
#include "../components/null_interaction.h"
#include "../components/attached_health.h"
#include "../components/character_health.h"
#include "../components/timed_health.h"
#include "../components/null_health.h"
#include "../components/character_visuals.h"
#include "../components/health_visuals.h"
#include "../components/menu_item_visuals.h"
#include "../components/static_visuals.h"
#include "../components/tiled_visuals.h"
#include "../components/null_visuals.h"
#include "../commands/use_component_command.h"
#include "../commands/reuse_component_command.h"
#include "../commands/export_entities_command.h"
#include "../utilities.h"

void CommandSystem::process(const Time time_diff)
{
    while(m_commands.size() > 0)
    {
        auto cmd = std::move(m_commands.front());
        m_commands.pop_front();
        cmd->execute();
    }
}

void CommandSystem::process_stream(std::istream& input, SDL_Renderer* renderer)
{
    std::string line;
    std::unique_ptr<Command> command;
    double vars[15];
    auto next_cmd_it = std::begin(m_commands);

    while(input.good())
    {
    	const std::string token { [&](){ std::string result; input >> result; return result; }() }; // @suppress("Invalid arguments")
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
				command = std::make_unique<AddSpritesheetCommand>(Spritesheet{int(vars[0]), int(vars[1])
																		  , int(vars[2]), int(vars[3])
																		  , int(vars[4]), int(vars[5])
																		  , int(vars[6]), int(vars[7])
																		  , int(vars[8]), int(vars[9])
																		  , int(vars[10]), int(vars[11])
																		  , int(vars[12]), int(vars[13])
																		  , double(vars[14])}
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
				input >> vars[3];
				command = std::make_unique<ModifyCollisionCommand>(vars[0], vars[1], vars[2], vars[3]);
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
				command = std::make_unique<UseComponentCommand<NullPosition>>();
				break;

			case hash("UseAbsolutePosition"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				input >> vars[3];
				command = std::make_unique<UseComponentCommand<AbsolutePosition>>(vars[0], vars[1], vars[2], vars[3]);
				break;

			case hash("UseAttachedPosition"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				input >> vars[3];
				input >> vars[4];
				command = std::make_unique<UseComponentCommand<AttachedPosition>>(EntityID(vars[0]), vars[1], vars[2], vars[3], vars[4]);
				break;

			case hash("UseBuildPosition"):
				input >> vars[0];
				command = std::make_unique<UseComponentCommand<BuildPosition>>(EntityID(vars[0]));
				break;

			case hash("UseNullControl"):
				command = std::make_unique<UseComponentCommand<NullControl>>();
				break;

			case hash("UseConstantControl"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				input >> vars[3];
				command = std::make_unique<UseComponentCommand<ConstantControl>>(vars[0], vars[1], vars[2], Control::LookDir(vars[3]));
				break;

			case hash("UseInputControl"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				command = std::make_unique<UseComponentCommand<InputControl>>(ProcedureID(vars[0]), vars[1], bool(vars[2]));
				break;

			case hash("UseInputSelectControl"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				command = std::make_unique<UseComponentCommand<InputSelectControl>>(int(vars[0]), int(vars[1]), ProcedureID(vars[2]));
				break;

			case hash("UseChaseAIControl"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				input >> vars[3];
				command = std::make_unique<UseComponentCommand<ChaseAIControl>>(EntityID(vars[0]), ProcedureID(vars[1]), vars[2], vars[3]);
				break;

			case hash("UseGuideControl"):
				input >> vars[0];
				input >> vars[1];
				command = std::make_unique<UseComponentCommand<GuideControl>>(EntityID(vars[0]), vars[1]);
				break;

			case hash("UseNullMovement"):
				command = std::make_unique<UseComponentCommand<NullMovement>>();
			break;

			case hash("UseFullMovement"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				input >> vars[3];
				input >> vars[4];
				command = std::make_unique<UseComponentCommand<FullMovement>>(vars[0], vars[1], vars[2], vars[3], bool(vars[4]));
				break;

			case hash("UseInstantMovement"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				command = std::make_unique<UseComponentCommand<InstantMovement>>(vars[0], vars[1], vars[2]);
				break;

			case hash("UseNullCollision"):
				command = std::make_unique<UseComponentCommand<NullCollision>>();
			break;

			case hash("UseBasicCollision"):
				input >> vars[0];
				input >> vars[1];
				command = std::make_unique<UseComponentCommand<BasicCollision>>(Collision::CollisionState(vars[0]), vars[1]);
				break;

			case hash("UseDamageCollision"):
				input >> vars[0];
				input >> vars[1];
				command = std::make_unique<UseComponentCommand<DamageCollision>>(Collision::CollisionState(vars[0]), vars[1]);
				break;

			case hash("UseNullInteraction"):
				command = std::make_unique<UseComponentCommand<NullInteraction>>();
				break;

			case hash("UseNormalInteraction"):
				input >> vars[0];
				command = std::make_unique<UseComponentCommand<NormalInteraction>>(int32_t(vars[0]));
				break;

			case hash("UseTriggerInteraction"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				input >> vars[3];
				command = std::make_unique<UseComponentCommand<TriggerInteraction>>(int8_t(vars[0]), ProcedureID(vars[1]), ProcedureID(vars[2]), ProcedureID(vars[3]));
				break;

			case hash("UseFullInteraction"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				input >> vars[3];
				input >> vars[4];
				command = std::make_unique<UseComponentCommand<FullInteraction>>(int32_t(vars[0]), int8_t(vars[1]), ProcedureID(vars[2]), ProcedureID(vars[3]), ProcedureID(vars[4]));
				break;

			case hash("UseNullHealth"):
				command = std::move(std::make_unique<UseComponentCommand<NullHealth>>());
				break;

			case hash("UseAttachedHealth"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				command = std::make_unique<UseComponentCommand<AttachedHealth>>(EntityID(vars[0]), vars[1], vars[2]);
				break;

			case hash("UseCharacterHealth"):
				input >> vars[0];
				input >> vars[1];
				command = std::make_unique<UseComponentCommand<CharacterHealth>>(vars[0], vars[1]);
				break;

			case hash("UseTimedHealth"):
				input >> vars[0];
				input >> vars[1];
				command = std::make_unique<UseComponentCommand<TimedHealth>>(vars[0], ProcedureID(vars[1]));
				break;

			case hash("UseNullVisuals"):
				command = std::make_unique<UseComponentCommand<NullVisuals>>();
				break;

			case hash("UseCharacterVisuals"):
				input >> vars[0];
				command = std::make_unique<UseComponentCommand<CharacterVisuals>>(SpritesheetID(vars[0]));
				break;

			case hash("UseTiledVisuals"):
				input >> vars[0];
				input >> vars[1];
				input >> vars[2];
				command = std::make_unique<UseComponentCommand<TiledVisuals>>(SpritesheetID(vars[0]), vars[1], vars[2]);
				break;

			case hash("UseStaticVisuals"):
				input >> vars[0];
				input >> vars[1];
				command = std::make_unique<UseComponentCommand<StaticVisuals>>(SpritesheetID(vars[0]), int(vars[1]));
				break;

			case hash("UseHealthVisuals"):
				input >> vars[0];
				input >> vars[1];
				command = std::make_unique<UseComponentCommand<HealthVisuals>>(SpritesheetID(vars[0]), uint16_t(vars[1]));
				break;

			case hash("UseMenuItemVisuals"):
				input >> vars[0];
				command = std::make_unique<UseComponentCommand<MenuItemVisuals>>(SpritesheetID(vars[0]));
				break;

			case hash("ReusePosition"):
				input >> vars[0];
				command = std::make_unique<ReuseComponentCommand<Position>>(EntityID(vars[0]), renderer);
				break;

			case hash("ReuseControl"):
				input >> vars[0];
				command = std::make_unique<ReuseComponentCommand<Control>>(EntityID(vars[0]), renderer);
				break;

			case hash("ReuseMovement"):
				input >> vars[0];
				command = std::make_unique<ReuseComponentCommand<Movement>>(EntityID(vars[0]), renderer);
				break;

			case hash("ReuseCollision"):
				input >> vars[0];
				command = std::make_unique<ReuseComponentCommand<Collision>>(EntityID(vars[0]), renderer);
				break;

			case hash("ReuseInteraction"):
				input >> vars[0];
				command = std::make_unique<ReuseComponentCommand<Interaction>>(EntityID(vars[0]), renderer);
				break;

			case hash("ReuseHealth"):
				input >> vars[0];
				command = std::make_unique<ReuseComponentCommand<Health>>(EntityID(vars[0]), renderer);
				break;

			case hash("ReuseVisuals"):
				input >> vars[0];
				command = std::make_unique<ReuseComponentCommand<Visuals>>(EntityID(vars[0]), renderer);
				break;

			case hash("ExportEntities"):
				input >> line;
				command = std::make_unique<ExportEntitiesCommand>(line);
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
        	insert_before(next_cmd_it, std::move(command));
        }
    }
}

