/*
 * export_entities_command.h
 *
 *  Created on: Jul 1, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_EXPORT_ENTITIES_COMMAND_H_
#define COMMANDS_EXPORT_ENTITIES_COMMAND_H_

#include "command.h"
#include <string>
#include <istream>

class ExportEntitiesCommand : public Command
{
public:
	ExportEntitiesCommand(const std::string& filename)
    : m_filename(filename)
    {}

    void execute() const;
    std::unique_ptr<Command> clone() const { return std::make_unique<ExportEntitiesCommand>(m_filename); }

private:
    std::string m_filename;
};

#endif /* COMMANDS_EXPORT_ENTITIES_COMMAND_H_ */
