/*
 * input_handler.cpp
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#include "input_handler.h"
#include "globals.h"
#include "commands/quit_command.h"

void InputHandler::process_input()
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
                else if(m_event.key.keysym.sym == m_keyquit)
                    globals.command_queue.push(std::make_unique<QuitCommand>());
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

