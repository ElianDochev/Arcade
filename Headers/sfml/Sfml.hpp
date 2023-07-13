#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "../Abstracts/IGraphic.hpp"
#include "../Games/AEvents.hpp"
#include "../Abstracts/AObject.hpp"
#include "../Abstracts/IMediator.hpp"

namespace Graphical
{
    class SFML : public Graphical::IGraphic
    {
    public:
        SFML() {}
        ~SFML() override;
        bool init(Core::IMediator *mediator) override;
        bool CheckEvents() override;
        std::vector<std::unique_ptr<Game::Events::AEvents>> GetEvents() override;
        bool draw(Game::Display::Circle &objs) override;
        bool draw(Game::Display::Line &objs) override;
        bool draw(Game::Display::Rectangle &objs) override;
        bool draw(Game::Display::Text &objs) override;
        bool draw(Game::Display::Sprite &objs) override;
        void draw(std::vector<std::unique_ptr<Game::Display::AObject>> &objs) override;
        bool refresh_screen() override;
        bool clear_screen() override;
        void event_loop() override;
        bool load(const std::string &type, const std::string &path) override
        {
            (void)type;
            (void)path;
            return true;
        }
        void unload(const std::string &type, const std::string &path) override
        {
            (void)type;
            (void)path;
        }
        void unloadAll() override {}
        void playSound(Game::Sound &sound) override { (void)sound; }
        bool toClose() override;

    protected:
        Game::Display::AObject::coordinates pos_from_percent(Game::Display::AObject::coordinates pos) override;

    private:
        Core::IMediator *_mediator;
        sf::RenderWindow _window;
        sf::Event _event;
        std::vector<std::unique_ptr<Game::Events::AEvents>> _events;
        void _parseEventKeyboard();
        std::vector<std::unique_ptr<sf::Drawable>> drawableObjects;
        sf::Font _defaultFont;
        size_t _width = 800;
        size_t _height = 600;
        Game::Display::AObject::coordinates _posToPercent(int x, int y);
        Game::Display::AObject::coordinates _posToPercent(float x, float y);
        class _Line : public sf::Drawable
        {
        public:
            _Line(Game::Display::Line &line, Graphical::SFML *sfml);
            void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const override;

        private:
            sf::VertexArray _line;
        };
    };
};

using sfml = Graphical::SFML;