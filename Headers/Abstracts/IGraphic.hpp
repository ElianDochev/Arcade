#pragma once

#include "AObject.hpp"
#include "../Games/AEvents.hpp"
#include "IMediator.hpp"
#include "IModule.hpp"
#include "Sound.hpp"
#include <vector>
#include <list>

namespace g = Game;

namespace Graphical
{
    class IGraphic : public Core::IMod
    {
    public:
        virtual bool CheckEvents() = 0;
        //! @brief pull events(clicks, keypresses, etc) that has been passed by Mediator
        //! @return a list of events that occured
        virtual std::vector<std::unique_ptr<g::Events::AEvents>> GetEvents() = 0;
        //! @brief True if the Circle could be drawned. False otherwise.
        //! @param objs the circle to draw
        virtual bool draw(g::Display::Circle &objs) = 0;
        //! True if the Line could be drawned. False otherwise.
        //! @param objs the line to draw
        virtual bool draw(g::Display::Line &objs) = 0;
        //! @brief True if the rectangle could be drawned. False otherwise.
        //! @param objs the rectangle to draw
        virtual bool draw(g::Display::Rectangle &objs) = 0;
        //! @brief True if the Text could be drawned. False otherwise.
        //! @param objs the text to draw
        virtual bool draw(g::Display::Text &objs) = 0;
        //! @brief True if the Sprite could be drawned. False otherwise.
        //! @param objs the sprite to draw
        virtual bool draw(g::Display::Sprite &objs) = 0;
        //! @brief objects to display gotten from the game
        virtual void draw(std::vector<std::unique_ptr<g::Display::AObject>> &objs) = 0;
        //! @brief displays the buffeded objects
        virtual bool refresh_screen() = 0;
        //! @brief Clear the screen and reset the buffer
        virtual bool clear_screen() = 0;
        //! @brief the event loop
        virtual void event_loop() = 0;
        //! @brief Load a resource
        //! @return Return true if the resource was successfully loaded. False otherwise
        virtual bool load(const std::string &type, const std::string &path) = 0;
        //! @brief Unload a resource
        virtual void unload(const std::string &type, const std::string &path) = 0;
        //! @brief Unload all resources loaded.
        virtual void unloadAll() = 0;
        //! @brief Play a sound
        virtual void playSound(g::Sound &sound) = 0;

    protected:
        //! @brief convert a position in percent to a position in pixel for current graphic library
        virtual g::Display::AObject::coordinates pos_from_percent(g::Display::AObject::coordinates pos) = 0;
    };
}
