/*
 * input_system.h
 *
 *  Created on: Oct 7, 2020
 *      Author: zamfi
 */

#ifndef SYSTEMS_INPUT_SYSTEM_H_
#define SYSTEMS_INPUT_SYSTEM_H_

#include "SDL2/SDL.h"

struct Globals;

class InputSystem
{
public:
	InputSystem()
	: m_keypause(SDLK_p)
	, m_keyjump(SDLK_w)
	, m_keydown(SDLK_s)
	, m_keyleft(SDLK_a)
	, m_keyright(SDLK_d)
	, m_keyshoot(SDLK_e)
	, m_keyquit(SDLK_ESCAPE)
	, m_keyselect(SDLK_RETURN)
	, m_left_pressed(false)
	, m_right_pressed(false)
	, m_jump_pressed(false)
	, m_duck_pressed(false)
	, m_shoot_pressed(false)
	, m_up_pressed(false)
	, m_down_pressed(false)
	, m_select_pressed(false)
	{}

    void process_input(Globals& globals);
    bool jumping() const { return m_jump_pressed; }
    bool ducking() const { return m_duck_pressed; }
    bool shooting() const { return m_shoot_pressed; }
    bool going_left() const { return m_left_pressed; }
    bool going_right() const { return m_right_pressed; }
    bool up() const { return m_up_pressed; }
    bool down() const { return m_down_pressed; }
    bool select() const { return m_select_pressed; }

private:
    SDL_Keycode m_keypause, m_keyjump, m_keydown, m_keyleft, m_keyright, m_keyshoot, m_keyquit, m_keyselect;
    bool m_left_pressed, m_right_pressed, m_jump_pressed, m_duck_pressed, m_shoot_pressed, m_up_pressed, m_down_pressed, m_select_pressed;
    SDL_Event m_event;
};

#endif /* SYSTEMS_INPUT_SYSTEM_H_ */
