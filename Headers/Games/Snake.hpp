#pragma once

#include "../Abstracts/IGame.hpp"

#include <deque>
#include <string>

extern std::string GRAPH_LIB_FOR_MENU;

namespace Game
{

class SnakeGame : public IGame {
    public:
        //! @brief Virtual destructor
        // ~SnakeGame() override = default;

        SnakeGame();

        //! @brief Get resources to preload.
        //! @info Only called once.
        //! @return A vector of tupple of (type of resource, path of the resource).
        const std::vector<std::pair<std::string, std::string>> &getResources() const {
            return _res;
        }

        //! @brief Return a list of objects to display.
        //! @return The list of objects
        std::vector<std::unique_ptr<Display::AObject>> &getObject();

        //! @brief Return a list of sounds to play.
        //! @return The list of sounds
        const std::vector<Sound> &getSounds() {
            return _sounds;
        }

        //! @brief Advance the game of x seconds
        //! @param tick The number of ticks that occured since the last call.
        void addTicks(unsigned) {}

        //! @brief Restart the game.
        void restart() {}

        //! @brief Handle one event (A key press, a click, a close event...)
        //! @param event The event to handle.
        void handleEvent(Events::AEvents &event);

        // add score dump
        bool toClose();

        bool UpdateFrame();

        bool init(Core::IMediator *mediator) override;

    private:
        static const Game::Display::Rectangle segment;
        static const Game::Display::Circle food;
        static const Game::Display::Line wall;

        static const Game::Display::Text game_over_text;
        static Game::Display::Text score_text;

        static const std::pair<int, int> directions[4];

        size_t current_direction{0};

    private:
        void generateFood();

        template <typename T>
        void createAt(int x, int y, const T& reference) {
            objects_.emplace_back(std::make_unique<T>(reference));
            objects_.back()->pos.x = x;
            objects_.back()->pos.y = y;
        }

        void createWall(int x1, int y1, int x2, int y2);

        void MoveSnake(bool add_segment);

        void takeCoord(Game::Display::AObject::coordinates&);

        void freeCoord(Game::Display::AObject::coordinates&);

        void checkCollisions();

        void OverTheGame();

    private:
        std::vector<std::unique_ptr<Display::AObject>> objects_;

        std::deque<Display::AObject*> snake_;
        Display::AObject* food_;
        Game::Display::Text* score_text_ref;

        std::vector<Sound> _sounds;
        std::vector<std::pair<std::string, std::string>> _res;
        Core::IMediator *mediator_;

        size_t gameover_timer{10};
};

}