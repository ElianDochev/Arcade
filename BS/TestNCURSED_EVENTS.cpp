#include "../Headers/NCurses/NEvents.hpp"

// from root g++ BS/TestNCURSED_EVENTS.cpp Graphicals/Ncurses/src/NEvents.cpp -I./Headers -lncurses

namespace ev = Game::Events;
namespace entity = Game::Display;
using Ptr = std::unique_ptr<ev::AEvents>;

int main(void)
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    mouseinterval(0);
    NEvents events;
    events.Start();
    start_color();
    init_color(200, 0xf5, 0xf5, 0x00);
    init_pair(1, 200, COLOR_BLACK);
    size_t i = 0;
    int running = 1;
    while (running)
    {
        if (events.Check_Event())
        {
            auto event_vec = events.GetParcedEvents();
            for (auto &event : event_vec)
            {
                auto &mouse = event->getMouse();
                float x = 0;
                float y = 0;

                if (mouse.has_value())
                {
                    x = mouse.value().x;
                    y = mouse.value().y;
                }
                if (event->type == ev::KeyboardEvent::Type::KeyPressed && event->key == ev::KeyboardEvent::KeyNum::ESCAPE)
                {
                    running = 0;
                    break;
                }
                attron(COLOR_PAIR(1));
                printw("Event %d: , type: %d, key: %d, mouse: %f, %f\n", i++, event->type, event->key, x, y);
            }
            int y, x;
            getyx(stdscr, y, x);
            int max_y, max_x;
            getmaxyx(stdscr, max_y, max_x);

            if (y >= max_y - 1 || x >= max_x - 1)
                clear();
        }
        refresh();
    }
    events.Stop();
    endwin();
    return 0;
}
