#pragma once

#include "../Abstracts/IGame.hpp"

namespace Game
{
    class MainMenu : public IGame
    {
    public:
        MainMenu() {}
        ~MainMenu() override = default;
        bool init(Core::IMediator *mediator) override;
        const std::vector<std::pair<std::string, std::string>> &getResources() const override;
        std::vector<std::unique_ptr<Display::AObject>> &getObject() override;
        const std::vector<Sound> &getSounds() override { return _sounds; }
        void addTicks(unsigned) {}
        void restart() override {}
        void handleEvent(Events::AEvents &event) override;
        bool usePercentPosition() const override { return true; }

        bool toClose()
        {
            delete this;
            return true;
        }

    private:
        Core::IMediator *_mediator;
        std::vector<std::unique_ptr<Display::AObject>> _objects;
        std::vector<Sound> _sounds;
        std::vector<std::pair<std::string, std::string>> _resources;
        std::vector<std::string> graphLibs;
        std::vector<std::string> gameLibs;
        size_t _selectedGame{0};
        size_t _selectedGraph{0};
        void _initResources();
        bool _typeText{false};
    };
}