#pragma once

#include <vector>
#include "AObject.hpp"
#include "../Games/AEvents.hpp"
// #include "IMediator.hpp"
#include "IModule.hpp"
#include "Sound.hpp"

namespace Game
{
    // this is used my the mediator
    class IGame : public Core::IMod
    {
    public:
        enum class GameState
        {
            PLAYING,
            GAMEOVER
        };

        //! @brief Virtual destructor
        ~IGame() override = default;

        //! @brief Get resources to preload.
        //! @info Only called once.
        //! @return A vector of tupple of (type of resource, path of the resource).
        virtual const std::vector<std::pair<std::string, std::string>> &getResources() const = 0;
        //! @brief Return a list of objects to display.
        //! @return The list of objects
        virtual std::vector<std::unique_ptr<Display::AObject>> &getObject() = 0;
        //! @brief Return a list of sounds to play.
        //! @return The list of sounds
        virtual const std::vector<Sound> &getSounds() = 0;
        //! @brief Advance the game of x seconds
        //! @param tick The number of ticks that occured since the last call.
        virtual void addTicks(unsigned tick) = 0;

        //! @brief Restart the game.
        virtual void restart() = 0;

        //! @brief Handle one event (A key press, a click, a close event...)
        //! @param event The event to handle.
        virtual void handleEvent(Events::AEvents &event) = 0;

        //! @brief Get the score (used for saving/displaying)
        inline unsigned long getScore() { return score; }

        //! @brief does it use percent position or pixel position
        virtual bool usePercentPosition() const { return false; }

        virtual bool UpdateFrame()
        {
            return true;
        }

    protected:
        GameState state{GameState::PLAYING};
        size_t score = 0;
    };
}
