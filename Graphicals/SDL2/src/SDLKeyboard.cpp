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

   Events::KeyboardEvent SDLDisp::_bindKeyEvent(Events::KeyboardEvent::KeyNum key, Events::KeyboardEvent::Type keyType)
	{
		Events::KeyboardEvent e;

		e.key = key;
		e.type = keyType;
		return e;
	}

    Events::KeyboardEvent::KeyNum SDLDisp::_getSTDkey(unsigned int key)
    {
        switch (key) {
            case SDL_KeyCode::SDLK_a: return Events::KeyboardEvent::KEY_A;
		case SDL_KeyCode::SDLK_b: return Events::KeyboardEvent::KEY_B;
		case SDL_KeyCode::SDLK_c: return Events::KeyboardEvent::KEY_C;
		case SDL_KeyCode::SDLK_d: return Events::KeyboardEvent::KEY_D;
		case SDL_KeyCode::SDLK_e: return Events::KeyboardEvent::KEY_E;
		case SDL_KeyCode::SDLK_f: return Events::KeyboardEvent::KEY_F;
		case SDL_KeyCode::SDLK_g: return Events::KeyboardEvent::KEY_G;
		case SDL_KeyCode::SDLK_h: return Events::KeyboardEvent::KEY_H;
		case SDL_KeyCode::SDLK_i: return Events::KeyboardEvent::KEY_I;
		case SDL_KeyCode::SDLK_j: return Events::KeyboardEvent::KEY_J;
		case SDL_KeyCode::SDLK_k: return Events::KeyboardEvent::KEY_K;
		case SDL_KeyCode::SDLK_l: return Events::KeyboardEvent::KEY_L;
		case SDL_KeyCode::SDLK_m: return Events::KeyboardEvent::KEY_M;
		case SDL_KeyCode::SDLK_n: return Events::KeyboardEvent::KEY_N;
		case SDL_KeyCode::SDLK_o: return Events::KeyboardEvent::KEY_O;
		case SDL_KeyCode::SDLK_p: return Events::KeyboardEvent::KEY_P;
		case SDL_KeyCode::SDLK_q: return Events::KeyboardEvent::KEY_Q;
		case SDL_KeyCode::SDLK_r: return Events::KeyboardEvent::KEY_R;
		case SDL_KeyCode::SDLK_s: return Events::KeyboardEvent::KEY_S;
		case SDL_KeyCode::SDLK_t: return Events::KeyboardEvent::KEY_T;
		case SDL_KeyCode::SDLK_u: return Events::KeyboardEvent::KEY_U;
		case SDL_KeyCode::SDLK_v: return Events::KeyboardEvent::KEY_V;
		case SDL_KeyCode::SDLK_w: return Events::KeyboardEvent::KEY_W;
		case SDL_KeyCode::SDLK_x: return Events::KeyboardEvent::KEY_X;
		case SDL_KeyCode::SDLK_y: return Events::KeyboardEvent::KEY_Y;
		case SDL_KeyCode::SDLK_z: return Events::KeyboardEvent::KEY_Z;
		case SDL_KeyCode::SDLK_0: return Events::KeyboardEvent::KEY_0;
		case SDL_KeyCode::SDLK_1: return Events::KeyboardEvent::KEY_1;
		case SDL_KeyCode::SDLK_2: return Events::KeyboardEvent::KEY_2;
		case SDL_KeyCode::SDLK_3: return Events::KeyboardEvent::KEY_3;
		case SDL_KeyCode::SDLK_4: return Events::KeyboardEvent::KEY_4;
		case SDL_KeyCode::SDLK_5: return Events::KeyboardEvent::KEY_5;
		case SDL_KeyCode::SDLK_6: return Events::KeyboardEvent::KEY_6;
		case SDL_KeyCode::SDLK_7: return Events::KeyboardEvent::KEY_7;
		case SDL_KeyCode::SDLK_8: return Events::KeyboardEvent::KEY_8;
		case SDL_KeyCode::SDLK_9: return Events::KeyboardEvent::KEY_9;
		case SDL_KeyCode::SDLK_KP_0: return Events::KeyboardEvent::NUMPAD_0;
		case SDL_KeyCode::SDLK_KP_1: return Events::KeyboardEvent::NUMPAD_1;
		case SDL_KeyCode::SDLK_KP_2: return Events::KeyboardEvent::NUMPAD_2;
		case SDL_KeyCode::SDLK_KP_3: return Events::KeyboardEvent::NUMPAD_3;
		case SDL_KeyCode::SDLK_KP_4: return Events::KeyboardEvent::NUMPAD_4;
		case SDL_KeyCode::SDLK_KP_5: return Events::KeyboardEvent::NUMPAD_5;
		case SDL_KeyCode::SDLK_KP_6: return Events::KeyboardEvent::NUMPAD_6;
		case SDL_KeyCode::SDLK_KP_7: return Events::KeyboardEvent::NUMPAD_7;
		case SDL_KeyCode::SDLK_KP_8: return Events::KeyboardEvent::NUMPAD_8;
		case SDL_KeyCode::SDLK_KP_9: return Events::KeyboardEvent::NUMPAD_9;
		case SDL_KeyCode::SDLK_BACKSPACE: return Events::KeyboardEvent::BACKSPACE;
		case SDL_KeyCode::SDLK_TAB:
		case SDL_KeyCode::SDLK_KP_TAB: return Events::KeyboardEvent::TAB;
		case SDL_KeyCode::SDLK_KP_ENTER: return Events::KeyboardEvent::ENTER;
		case SDL_KeyCode::SDLK_LSHIFT:
		case SDL_KeyCode::SDLK_RSHIFT: return Events::KeyboardEvent::SHIFT;
		case SDL_KeyCode::SDLK_RCTRL:
		case SDL_KeyCode::SDLK_LCTRL: return Events::KeyboardEvent::CTRL;
		case SDL_KeyCode::SDLK_RALT:
		case SDL_KeyCode::SDLK_LALT: return Events::KeyboardEvent::ALT;
		case SDL_KeyCode::SDLK_PAUSE: return Events::KeyboardEvent::PAUSE;
		case SDL_KeyCode::SDLK_CAPSLOCK: return Events::KeyboardEvent::CAPS_LOCK;
		case SDL_KeyCode::SDLK_ESCAPE: return Events::KeyboardEvent::ESCAPE;
		case SDL_KeyCode::SDLK_SPACE:
		case SDL_KeyCode::SDLK_KP_SPACE: return Events::KeyboardEvent::SPACE;
		case SDL_KeyCode::SDLK_PAGEUP: return Events::KeyboardEvent::PAGE_UP;
		case SDL_KeyCode::SDLK_PAGEDOWN: return Events::KeyboardEvent::PAGE_DOWN;
		case SDL_KeyCode::SDLK_END: return Events::KeyboardEvent::END;
		case SDL_KeyCode::SDLK_AC_HOME:
		case SDL_KeyCode::SDLK_HOME: return Events::KeyboardEvent::HOME;
		case SDL_KeyCode::SDLK_LEFT: return Events::KeyboardEvent::LEFT_ARROW;
		case SDL_KeyCode::SDLK_UP: return Events::KeyboardEvent::UP_ARROW;
		case SDL_KeyCode::SDLK_RIGHT: return Events::KeyboardEvent::RIGHT_ARROW;
		case SDL_KeyCode::SDLK_DOWN: return Events::KeyboardEvent::DOWN_ARROW;
		case SDL_KeyCode::SDLK_INSERT: return Events::KeyboardEvent::INSERT;
		case SDL_KeyCode::SDLK_DELETE: return Events::KeyboardEvent::DELETE;
		case SDL_KeyCode::SDLK_SELECT: return Events::KeyboardEvent::SELECT;
		case SDL_KeyCode::SDLK_KP_MULTIPLY:
		case SDL_KeyCode::SDLK_KP_MEMMULTIPLY: return Events::KeyboardEvent::MULTIPLY;
		case SDL_KeyCode::SDLK_KP_MEMADD: return Events::KeyboardEvent::ADD;
		case SDL_KeyCode::SDLK_KP_MEMSUBTRACT: return Events::KeyboardEvent::SUBTRACT;
		case SDL_KeyCode::SDLK_KP_DECIMAL: return Events::KeyboardEvent::DECIMAL;
		case SDL_KeyCode::SDLK_KP_DIVIDE:
		case SDL_KeyCode::SDLK_KP_MEMDIVIDE: return Events::KeyboardEvent::DIVIDE;
		case SDL_KeyCode::SDLK_F1: return Events::KeyboardEvent::F1;
		case SDL_KeyCode::SDLK_F2: return Events::KeyboardEvent::F2;
		case SDL_KeyCode::SDLK_F3: return Events::KeyboardEvent::F3;
		case SDL_KeyCode::SDLK_F4: return Events::KeyboardEvent::F4;
		case SDL_KeyCode::SDLK_F5: return Events::KeyboardEvent::F5;
		case SDL_KeyCode::SDLK_F6: return Events::KeyboardEvent::F6;
		case SDL_KeyCode::SDLK_F7: return Events::KeyboardEvent::F7;
		case SDL_KeyCode::SDLK_F8: return Events::KeyboardEvent::F8;
		case SDL_KeyCode::SDLK_F9: return Events::KeyboardEvent::F9;
		case SDL_KeyCode::SDLK_F10: return Events::KeyboardEvent::F10;
		case SDL_KeyCode::SDLK_F11: return Events::KeyboardEvent::F11;
		case SDL_KeyCode::SDLK_F12: return Events::KeyboardEvent::F12;
		case SDL_KeyCode::SDLK_NUMLOCKCLEAR: return Events::KeyboardEvent::NUM_LOCK;
		case SDL_KeyCode::SDLK_SCROLLLOCK: return Events::KeyboardEvent::SCROLL_LOCK;
		case SDL_KeyCode::SDLK_SEMICOLON: return Events::KeyboardEvent::SEMICOLON;
		case SDL_KeyCode::SDLK_EQUALS:
		case SDL_KeyCode::SDLK_KP_EQUALSAS400:
		case SDL_KeyCode::SDLK_KP_EQUALS: return Events::KeyboardEvent::EQUALS;
		case SDL_KeyCode::SDLK_COMMA:
		case SDL_KeyCode::SDLK_KP_COMMA: return Events::KeyboardEvent::COMMA;
		case SDL_KeyCode::SDLK_KP_MINUS:
		case SDL_KeyCode::SDLK_MINUS: return Events::KeyboardEvent::DASH;
		case SDL_KeyCode::SDLK_PERIOD:
		case SDL_KeyCode::SDLK_KP_PERIOD: return Events::KeyboardEvent::PERIOD;
		case SDL_KeyCode::SDLK_SLASH: return Events::KeyboardEvent::FORWARD_SLASH;
		case SDL_KeyCode::SDLK_BACKSLASH: return Events::KeyboardEvent::BACK_SLASH;
		case SDL_KeyCode::SDLK_BACKQUOTE: return Events::KeyboardEvent::GRAVE_ACCENT;
		case SDL_KeyCode::SDLK_LEFTBRACKET: return Events::KeyboardEvent::OPEN_BRACKET;
		case SDL_KeyCode::SDLK_RIGHTBRACKET: return Events::KeyboardEvent::CLOSE_BRACKET;
		case SDL_KeyCode::SDLK_QUOTE: return Events::KeyboardEvent::SINGLE_QUOTE;
		case SDL_KeyCode::SDLK_RGUI: return Events::KeyboardEvent::RIGHT_META;
		case SDL_KeyCode::SDLK_LGUI: return Events::KeyboardEvent::LEFT_META;
            default: return Events::KeyboardEvent::KeyNum::UNDEFINED;
    	}
	}
}