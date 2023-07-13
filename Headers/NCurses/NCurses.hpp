#pragma once

#include <ncurses.h>
#include "../Abstracts/IGraphic.hpp"
#include "NEvents.hpp"
#include <queue>
#include <vector>

#ifndef KEY_ESC
#define KEY_ESC 27
#endif

namespace Graphical
{
    class NCurses : public IGraphic
    {
    public:
        NCurses() {}
        ~NCurses();
        bool init(Core::IMediator *mediator) override;
        std::vector<std::unique_ptr<g::Events::AEvents>> GetEvents() override;
        bool draw(g::Display::Circle &obj) override;
        bool draw(g::Display::Line &obj) override;
        bool draw(g::Display::Rectangle &obj) override;
        bool draw(g::Display::Text &obj) override;
        bool draw(g::Display::Sprite &obj) override;
        void draw(std::vector<std::unique_ptr<g::Display::AObject>> &objs) override;
        // bool refresh() override;
        inline bool load(const std::string &, const std::string &) override { return true; }
        inline void unload(const std::string &, const std::string &) override {}
        void unloadAll() override {}
        inline bool CheckEvents() override
        {
            return !_queue.empty();
        }
        inline void playSound(g::Sound &) override {}
        inline bool close() { return !_started; }
        bool clear_screen()
        {
            clear();
            return true;
        }
        bool refresh_screen()
        {
            refresh();
            usleep(1000);
            return true;
        }
        Core::ModInfo::Type getModInfo()
        {
            return Core::ModInfo::Type::GRAPHIC;
        }
        bool toClose();
        void event_loop();
        static void _win_resize(int sig);

    protected:
        g::Display::AObject::coordinates pos_from_percent(g::Display::AObject::coordinates pos) override;

    private:
        Core::IMediator *_mediator;
        // NEvents _events;
        bool _started = false;
        std::queue<std::pair<int, MEVENT>> _queue;
        std::pair<int, int> _get_event_type(int c);
        int _getColor(unsigned int color);
        size_t max_x;
        size_t max_y;
        void _pos_to_percent(g::Display::AObject::coordinates &pos);
    };
}
