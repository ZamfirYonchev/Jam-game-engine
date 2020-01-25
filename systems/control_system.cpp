/*
 * control_system.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#include "control_system.h"
#include "../components/control.h"
#include "../components/health.h"
#include "../globals.h"
#include "../commands/call_procedure_command.h"
#include "../commands/modify_position_command.h"
#include "../commands/modify_control_command.h"

void ControlSystem::update(Time time_diff)
{
    for(auto it = entities.begin(); it != entities.end(); ++it)
    {
    	Control* control = globals.entity_system.entity(*it)->control();
    	Health* health = globals.entity_system.entity(*it)->health();


        if(health->alive() && health->stunned() == false)
        	control->update_decisions(time_diff);
        else
        	control->clear_decisions();

        if(control->decision_attack() && control->attack_proc_id() >= 0)
        {
        	Position* position = globals.entity_system.entity(*it)->position();
            globals.command_queue.push(new CallProcedureCommand(control->attack_proc_id()));
            if(control->look_dir() == Control::LEFT)
            {
                globals.command_queue.push(new ModifyPositionCommand(position->x(), position->y(), 0, 0));
                globals.command_queue.push(new ModifyControlCommand(0, 0, 0, -0.0, -0.0));
                globals.command_queue.push(new ModifyControlCommand(0, 0, 0, -1, control->look_dir()));
            }
            else // Look dir is right
            {
                //globals.command_queue.push(new ModifyPositionCommand(-0.0, 0, 0, 0));
                //globals.command_queue.push(new ModifyPositionCommand(position->x()+position->w(), position->y(), 0, 0));
                globals.command_queue.push(new ModifyPositionCommand(position->x(), position->y(), 0, 0));
                globals.command_queue.push(new ModifyControlCommand(0, 0, 0, -0.0, -0.0));
                globals.command_queue.push(new ModifyControlCommand(0, 0, 0, 1, control->look_dir()));
            }
        }

    }
}
