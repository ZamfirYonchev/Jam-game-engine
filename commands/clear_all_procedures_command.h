/*
 * clear_all_procedures_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_CLEAR_ALL_PROCEDURES_COMMAND_H_
#define COMMANDS_CLEAR_ALL_PROCEDURES_COMMAND_H_

#include "../command_value.h"

template<typename ProcedureResourceSystemT>
class ClearAllProceduresCommand
{
public:
	ProcedureResourceSystemT& procedures;

    ClearAllProceduresCommand(ProcedureResourceSystemT& _procedures)
	: procedures{_procedures}
    {}

    CommandValue operator()() const
    {
    	procedures.clear();
    	return CommandValue{0};
    }
};

#endif /* COMMANDS_CLEAR_ALL_PROCEDURES_COMMAND_H_ */
