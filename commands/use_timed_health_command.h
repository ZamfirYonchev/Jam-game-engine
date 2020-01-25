/*
 * use_timed_health_command.h
 *
 *  Created on: Nov 26, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_TIMED_HEALTH_COMMAND_H_
#define COMMANDS_USE_TIMED_HEALTH_COMMAND_H_

#include "command.h"
#include "../types.h"

class UseTimedHealthCommand : public Command
{
public:
	UseTimedHealthCommand(double ttl, ProcedureID proc_id)
	: m_ttl(ttl)
	, m_proc_id(proc_id)
	{}

    void execute() const;
    Command* clone() { return new UseTimedHealthCommand(m_ttl, m_proc_id); }
private:
    double m_ttl;
    ProcedureID m_proc_id;
};

#endif /* COMMANDS_USE_TIMED_HEALTH_COMMAND_H_ */
