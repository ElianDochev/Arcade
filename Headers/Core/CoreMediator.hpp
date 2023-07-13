#pragma once

#include "../Abstracts/IMediator.hpp"
#include "../Utils/ReadDlib.hpp"

namespace Core
{
    class CoreMediator : public IMediator
    {
    public:
        ~CoreMediator() = default;
        // Called when the game is initialized
        void onGameInit() {}

        CoreMediator(const char *graphic_lib);
        CoreMediator(const CoreMediator &) = delete;
        CoreMediator(CoreMediator &&) = delete;

        void changeGame(const std::string &);

        bool toExit() { return _exit; }

        void changeGraph(const std::string &);

        std::vector<std::string> &getGraphLibs() { return graphLibs; }

        std::vector<std::string> &getGameLibs() { return gameLibs; }

        void returnToMenu();

        std::pair<size_t &, size_t &> GetLibsIndex() { return {gameIndex, graphicIndex}; }

        void ExecChanges();

        void changeGraphLib(int dir);

        size_t &getScore() { return _score; }

        void setScore(size_t score) { _score = score; }

        void setPlayerName(const std::string &name) { _playerName = name; }

        std::string &getPlayerName() { return _playerName; }

        void exit();

        Game::IGame *getGame() { return game; }

        Graphical::IGraphic *getGraphic() { return graphics; }

    private:
        void initGame();

        void initGraph();

        DlibReader game_reader_;
        DlibReader graphic_reader_;

        const std::string menu_graphic_lib;

        std::vector<std::string> graphLibs;
        std::vector<std::string> gameLibs;

        std::string MainMenuLib = "";

        size_t gameIndex{0};
        size_t graphicIndex{0};

        struct PendingChanges
        {
            bool gameChange = false;
            bool graphicChange = false;
            std::string pendingGame;
            std::string pendingGraphic;
        };
        void _initResources();
        PendingChanges pendingChanges;
        bool _exit = false;
        size_t _score{0};
        std::string _playerName = "Enter your name";
    };
}
