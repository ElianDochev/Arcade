#pragma once

#include "AObject.hpp"
#include "IModule.hpp"
#include "IGame.hpp"
#include "IGraphic.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <utility>

namespace Game
{
    class IGame;
}

namespace Graphical
{
    class IGraphic;
}

namespace Core
{
    class IMediator
    {
    public:
        // Called when the game is initialized
        virtual void onGameInit() = 0;

        virtual ~IMediator() = default;

        IMediator() = default;

        virtual void changeGame(const std::string &) = 0;

        virtual void changeGraph(const std::string &) = 0;

        //! @brief executes the changing of libs if needed
        virtual void ExecChanges() = 0;

        //! @brief checks if the game uses percent position or literal position
        virtual bool GetPositionMode() { return game->usePercentPosition(); }

        //! @brief returns indexs for graphical and game libs
        virtual std::pair<size_t &, size_t &> GetLibsIndex() = 0;

        //! @brief returns the graphical library available
        virtual std::vector<std::string> &getGraphLibs() = 0;

        //! @brief returns the game library available
        virtual std::vector<std::string> &getGameLibs() = 0;

        //! @brief should the program exit
        virtual bool toExit() = 0;

        /**
         * @brief changes the graphical library ingame
         *
         * @param dir direction of the change 1 for next -1 for previous
         *
         * @note does nothing if dir is exactly not 1 or -1
         */
        virtual void changeGraphLib(int dir) = 0;

        //! @brief gets the score of the last game played(0 if no game played)
        virtual size_t &getScore() = 0;

        //! @brief sets the score of the last game played
        virtual void setScore(size_t score) = 0;

        //! @brief gets the name of the player
        virtual std::string &getPlayerName() = 0;

        //! @brief sets the name of the player
        virtual void setPlayerName(const std::string &name) = 0;
        //! @brief returns the graphical library object
        virtual Graphical::IGraphic *getGraphic() = 0;

        //! @brief returns the game object
        virtual Game::IGame *getGame() = 0;

        //! @brief ends the program
        virtual void exit() = 0;
        //! @brief returns to the main menu
        virtual void returnToMenu() = 0;

    protected:
        // The game object/main menu
        Game::IGame *game{nullptr};
        // The graphics library object
        Graphical::IGraphic *graphics{nullptr};
    };
}
