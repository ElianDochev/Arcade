#pragma once

#include <iostream>
#include <memory>
#include <string>

namespace Game
{
    namespace Display
    {
        struct AObject
        {
            struct coordinates
            {
                float x;
                float y;
            };

            enum Type
            {
                CIRCLE,
                RECTANGLE,
                TEXT,
                LINE,
                SPRITE
            };

            enum BackupColor
            {
                WHITE = 1,
                RED,
                GREEN,
                BLUE,
                BLACK,
                MAGENTA,
                CYAN,
                YELLOW
            };
            //! @brief the color of the object rgb value
            unsigned color;
            //! @brief the x and y positions of the object
            coordinates pos;
            //! @brief the color of the object when the rgb value failed
            unsigned backupColor = WHITE;
            //! @brief constructor
            AObject() = default;
            AObject(unsigned color, coordinates pos, unsigned backupColor = WHITE)
                : color(color), pos(pos), backupColor(backupColor) {}
            //! @brief the type of the object
            virtual Type getType() const = 0;
            //! @brief the default destructor
            virtual ~AObject() = default;
            struct AObjectUnknownException : public std::exception
            {
                AObjectUnknownException() : std::exception() {}
                const char *what() const noexcept override { return "Encountered unknown object"; }
            };
        };

        struct Circle : public AObject
        {
            Circle(unsigned color, coordinates pos, int radius, unsigned backupColor = GREEN)
                : AObject(color, pos, backupColor), radius(radius) {}
            //! @brief the radius of the circle
            int radius;
            Type getType() const override { return CIRCLE; }
        };

        struct Rectangle : public AObject
        {
            Rectangle(unsigned color, coordinates pos, int width, int height, unsigned backupColor = WHITE)
                : AObject(color, pos, backupColor),
                  width(width), height(height) {}
            //! @brief the width of the rectangle
            int width;
            //! @brief the height of the rectangle
            int height;
            Type getType() const override { return RECTANGLE; }
        };

        struct Text : public AObject
        {
            Text() = default;
            Text(unsigned color, coordinates pos, const std::string &text, unsigned backupColor = WHITE)
                : AObject(color, pos, backupColor),
                  text(text) {}
            //! @brief the text to display
            std::string text;
            //! @brief the size of the text
            size_t FontSize;
            //! @brief The font file
            std::string path;
            //! @brief The font hitbox (?)
            //! @brief size of the text box
            coordinates hitbox;
            Type getType() const override { return TEXT; }
        };

        struct Line : public AObject
        {
            Line(unsigned color, coordinates pos, int x2, int y2, unsigned backupColor = WHITE)
                : AObject(color, pos, backupColor),
                  x2(x2), y2(y2) {}
            //! @brief the x position of the end of the line
            int x2;
            //! @brief the y position of the end of the line
            int y2;
            Type getType() const override { return LINE; }
        };

        struct Sprite : public AObject
        {
            //! @brief the path to the sprite
            std::string path;
            //! @brief the width of the sprite
            int sizeX;
            //! @brief the height of the sprite
            int sizeY;
            //! @brief the character to use to represent as a backup
            int backupChar;
            Type getType() const override { return SPRITE; }
        };
    }
    struct Sound //< vasiliy added this struct
    {
        //! @brief the path to the sound
        std::string path;
        //! @brief the volume of the sound
        bool loop;
        //! @brief the volume of the sound
        bool stopOthers;
    };
}