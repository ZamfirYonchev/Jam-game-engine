/*
 * globals.h
 *
 *  Created on: Jan 16, 2021
 *      Author: zamfi
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <unordered_map>
#include <iostream>
#include <string>
#include "command_value.h"
#include "types.h"
#include "utilities.h"

class Globals
{
public:

	enum AppGlobal : HashT
	{
		app_running = hash("app_running"),
		app_needs_reload = hash("app_needs_reload"),
		app_paused = hash("app_paused"),
		app_show_hitboxes = hash("app_show_hitboxes"),
		app_current_level = hash("app_current_level"),
		app_debug_level = hash("app_debug_level"),
		app_resolution_x = hash("app_resolution_x"),
		app_resolution_y = hash("app_resolution_y"),
		app_fullscreen = hash("app_fullscreen"),
		app_enable_audio = hash("app_enable_audio"),
		app_sound_channels = hash("app_sound_channels"),
		app_window_title = hash("app_window_title"),
		selected_entity = hash("selected_entity"),
	};

	const CommandValue& operator()(HashT name_hash) const
	{
    	return m_variables[name_hash];
	}

	CommandValue& operator()(HashT name_hash)
	{
    	return m_variables[name_hash];
	}

	const CommandValue& operator()(std::string_view name) const
	{
    	const HashT name_hash = hash(name.data());
    	if(m_variables.find(name_hash) == cend(m_variables))
    		std::cerr << "Accessing an uninitialized variable " << name << std::endl;

    	return m_variables[hash(name.data())];
	}

	CommandValue& operator()(std::string_view name)
	{
    	const HashT name_hash = hash(name.data());
    	if(m_variables.find(name_hash) == cend(m_variables))
    		std::cerr << "Accessing an uninitialized variable " << name << std::endl;

    	return m_variables[hash(name.data())];
	}

private:
    mutable std::unordered_map<HashT, CommandValue> m_variables;
};



#endif /* GLOBALS_H_ */
