/*
 * input_system.cpp
 *
 *  Created on: Oct 7, 2020
 *      Author: zamfi
 */

#include "input_system.h"

void InputSystem::process_input(Globals& globals, std::list<std::pair<EntityID, ProcedureID>>& procedure_calls)
{
    while(SDL_PollEvent(&m_event) != 0)
    {
        switch(m_event.type)
        {
            case SDL_QUIT:
            	globals(Globals::app_running) = CommandReturnValue{0.0};
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
                	globals(Globals::app_running) = CommandReturnValue{0.0};
                else if(m_event.key.keysym.sym == SDLK_r)
                	globals(Globals::app_needs_reload) = CommandReturnValue{true};
                else if(m_event.key.keysym.sym == m_keypause)
                	globals(Globals::app_paused) = CommandReturnValue{!globals(Globals::app_paused).boolean(), 0};
                else if(m_event.key.keysym.sym == SDLK_h)
                	globals(Globals::app_show_hitboxes) = CommandReturnValue{!globals(Globals::app_show_hitboxes).boolean(), 0};
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

void InputSystem::clear_toggle_inputs()
{
	m_up_pressed = false;
	m_down_pressed = false;
	m_select_pressed = false;
}
