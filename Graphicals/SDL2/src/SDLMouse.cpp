/*
** EPITECH PROJECT, 2023
** Paradigms Seminar
** File description:
** Exercise 02
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <iostream>
#include "SDLDisp.hpp"

namespace Game
{
    Events::MouseMoveMent SDLDisp::_bindMoveEvent(unsigned int x, unsigned int y)
    {
        Events::MouseMoveMent event;

        event.x = x;
        event.y = y;
        event.type = Events::MouseEvent::Type::MouseMove;
        return event;
    }

    Events::MouseEvent SDLDisp::_bindMouseEvent(Events::MouseEvent::Type mouseType, Events::MouseEvent::Key key, unsigned int x, unsigned int y)
	{
		Events::MouseEvent e;

		e.x = x;
		e.y = y;
		e.button = button;
		e.type = clickType;
		return e;
	}

    Events::MouseEvent::Key SDLDisp::_getSTDclick(uint8_t type)
    {
        Events::MouseEvent::Key event;

        switch (type) {
            case SDL_BUTTON_LEFT:
                event = Events::MouseEvent::Key::Left;
                break;
            case SDL_BUTTON_MIDDLE:
                event = Events::MouseEvent::Key::Middle;
                break;
            case SDL_BUTTON_RIGHT:
                event = Events::MouseEvent::Key::Right;
                break;
            default:
                break;
        }
        return event;
    }
}