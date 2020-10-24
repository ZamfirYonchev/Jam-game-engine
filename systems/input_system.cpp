/*
 * input_system.cpp
 *
 *  Created on: Oct 7, 2020
 *      Author: zamfi
 */

#include "input_system.h"
#include "../globals.h"

void InputSystem::process_input(Globals& globals)
{
	m_up_pressed = false;
	m_down_pressed = false;
	m_select_pressed = false;

    while(SDL_PollEvent(&m_event) != 0)
    {
        switch(m_event.type)
        {
            case SDL_QUIT:
                globals.app_running = false;
            break;

            case SDL_KEYDOWN:
                if(m_event.key.keysym.sym == m_keyjump)
                {
                    m_jump_pressed = true;
                    m_up_pressed = true;
                }
                else if(m_event.key.keysym.sym == m_keydown)
                {
                	m_duck_pressed = true;
                    m_down_pressed = true;
                }
                else if(m_event.key.keysym.sym == m_keyleft)
                    m_left_pressed = true;
                else if(m_event.key.keysym.sym == m_keyright)
                    m_right_pressed = true;
                else if(m_event.key.keysym.sym == m_keyshoot)
                    m_shoot_pressed = true;
                else if(m_event.key.keysym.sym == m_keyselect)
                    m_select_pressed = true;
                else if(m_event.key.keysym.sym == m_keyquit || m_event.key.keysym.sym == SDLK_F10)
                	globals.app_running = false;
                else if(m_event.key.keysym.sym == SDLK_r)
                    globals.app_needs_reload = true;
                else if(m_event.key.keysym.sym == m_keypause)
                    globals.app_paused = !globals.app_paused;
                else if(m_event.key.keysym.sym == SDLK_h)
                    globals.show_hitboxes = !globals.show_hitboxes;
            break;

            case SDL_KEYUP:
                if(m_event.key.keysym.sym == m_keyjump)
                    m_jump_pressed = false;
                else if(m_event.key.keysym.sym == m_keydown)
                    m_duck_pressed = false;
                else if(m_event.key.keysym.sym == m_keyleft)
                    m_left_pressed = false;
                else if(m_event.key.keysym.sym == m_keyright)
                    m_right_pressed = false;
                else if(m_event.key.keysym.sym == m_keyshoot)
                    m_shoot_pressed = false;
            break;
        }
    }
}

