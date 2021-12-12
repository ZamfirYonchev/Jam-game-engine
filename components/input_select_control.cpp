/*
 * input_select_control.cpp
 *
 *  Created on: Oct 18, 2020
 *      Author: zamfi
 */

#include "input_select_control.h"
#include "../systems/input_system.h"

bool InputSelectControl::decision_attack() const
{
	return m_select == m_curr_selection && m_input_system.get().select();
}

void InputSelectControl::update_decisions(const Time time_diff)
{
	m_curr_selection += m_input_system.get().down() - m_input_system.get().up() + m_max;
	m_curr_selection %= m_max;
}
