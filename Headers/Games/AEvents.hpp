#pragma once

#include "../Abstracts/AObject.hpp"
#include <optional>

namespace Game::Events
{
    struct AEvents
    {
        //! @brief the type of event
        int type;
        //! @brief the key pressed
        int key;
        // Game::coordinates mouse;
        virtual std::optional<Game::Display::AObject::coordinates> &getMouse() = 0;
        virtual ~AEvents() = default;
    };

    struct MouseEvent : public AEvents
    {
        MouseEvent(unsigned int key, Game::Display::AObject::coordinates mouse, int type = MouseClick)
        {
            this->key = key;
            this->type = type;
            this->mouse = mouse;
        }
        MouseEvent() = default;
        enum Type
        {
            MouseClick = 10,
            MouseRelease,
            Undetified = 0,
            MouseMove,
        };

        Type typeM;

        enum Key
        {
            Left = 1000,
            Middle,
            Right,
        };

        Key keyM;

        std::optional<Game::Display::AObject::coordinates> &getMouse() override
        {
            return mouse;
        }

    private:
        std::optional<Game::Display::AObject::coordinates> mouse = std::make_optional<Game::Display::AObject::coordinates>({0, 0});
    };

    struct KeyboardEvent : public AEvents
    {
    private:
        std::optional<Game::Display::AObject::coordinates> mouse = std::nullopt; //< not used
    public:
        KeyboardEvent(unsigned int key)
        {
            this->key = key;
            this->type = KeyPressed;
        }
        KeyboardEvent() = default;
        enum Type
        {
            KeyPressed = 20,
            KeyReleased,
            KeyHold,
            Undetified = 0
        };

        Type typeK;

        std::optional<Game::Display::AObject::coordinates> &getMouse() override
        {
            return mouse;
        }
        enum KeyNum
        {
            UNDEFINED = 0,
            BACKSPACE = 8,
            TAB = 9,
            ENTER = 13,
            SHIFT = 16,
            CTRL = 17,
            ALT = 18,
            PAUSE = 19,
            CAPS_LOCK = 20,
            ESCAPE = 27,
            SPACE = 32,
            PAGE_UP = 33,
            PAGE_DOWN = 34,
            END = 35,
            HOME = 36,
            LEFT_ARROW = 37,
            UP_ARROW = 38,
            RIGHT_ARROW = 39,
            DOWN_ARROW = 40,
            INSERT = 45,
            DELETE = 46,
            KEY_0 = 48,
            KEY_1 = 49,
            KEY_2 = 50,
            KEY_3 = 51,
            KEY_4 = 52,
            KEY_5 = 53,
            KEY_6 = 54,
            KEY_7 = 55,
            KEY_8 = 56,
            KEY_9 = 57,
            KEY_A = 65,
            KEY_B = 66,
            KEY_C = 67,
            KEY_D = 68,
            KEY_E = 69,
            KEY_F = 70,
            KEY_G = 71,
            KEY_H = 72,
            KEY_I = 73,
            KEY_J = 74,
            KEY_K = 75,
            KEY_L = 76,
            KEY_M = 77,
            KEY_N = 78,
            KEY_O = 79,
            KEY_P = 80,
            KEY_Q = 81,
            KEY_R = 82,
            KEY_S = 83,
            KEY_T = 84,
            KEY_U = 85,
            KEY_V = 86,
            KEY_W = 87,
            KEY_X = 88,
            KEY_Y = 89,
            KEY_Z = 90,
            LEFT_META = 91,
            RIGHT_META = 92,
            SELECT = 93,
            NUMPAD_0 = 96,
            NUMPAD_1 = 97,
            NUMPAD_2 = 98,
            NUMPAD_3 = 99,
            NUMPAD_4 = 100,
            NUMPAD_5 = 101,
            NUMPAD_6 = 102,
            NUMPAD_7 = 103,
            NUMPAD_8 = 104,
            NUMPAD_9 = 105,
            MULTIPLY = 106,
            ADD = 107,
            SUBTRACT = 109,
            DECIMAL = 110,
            DIVIDE = 111,
            F1 = 112,
            F2 = 113,
            F3 = 114,
            F4 = 115,
            F5 = 116,
            F6 = 117,
            F7 = 118,
            F8 = 119,
            F9 = 120,
            F10 = 121,
            F11 = 122,
            F12 = 123,
            NUM_LOCK = 144,
            SCROLL_LOCK = 145,
            SEMICOLON = 186,
            EQUALS = 187,
            COMMA = 188,
            DASH = 189,
            PERIOD = 190,
            FORWARD_SLASH = 191,
            GRAVE_ACCENT = 192,
            OPEN_BRACKET = 219,
            BACK_SLASH = 220,
            CLOSE_BRACKET = 221,
            SINGLE_QUOTE = 222,
        };
        KeyNum keyK;
    };

    struct MouseMoveMent : public AEvents
    {
        //! @brief The x position (in percentage)
        unsigned x;
        //! @brief The y position (in percentage)
        unsigned y;
    };

}