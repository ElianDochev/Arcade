#include "../../../Headers/NCurses/NCurses.hpp"
#include <signal.h>

namespace ev = Game::Events;

bool Graphical::NCurses::init(Core::IMediator *mediator)
{
    _mediator = mediator;
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    mousemask(BUTTON1_CLICKED | BUTTON1_RELEASED | BUTTON1_CLICKED |
                  BUTTON3_CLICKED | BUTTON3_RELEASED | BUTTON3_CLICKED |
                  BUTTON2_CLICKED | BUTTON2_RELEASED | BUTTON2_CLICKED,
              NULL);
    mouseinterval(0);
    start_color();
    nodelay(stdscr, TRUE);
    getmaxyx(stdscr, max_y, max_x);
    signal(SIGWINCH, _win_resize);
    signal(SIGINT, [](int sig)
           {
        endwin();
        exit(sig); });
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_BLACK, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_CYAN, COLOR_BLACK);
    init_pair(8, COLOR_YELLOW, COLOR_BLACK);
    return true;
}

Graphical::NCurses::~NCurses()
{
    signal(SIGWINCH, SIG_DFL);
    signal(SIGINT, SIG_DFL);
    flushinp();
    endwin();
}

bool Graphical::NCurses::toClose()
{
    _started = false;
    delete this;
    return true;
}

extern "C"
{
    Core::IMod *GetModule(Core::IMediator *mediator)
    {
        Graphical::IGraphic *obj = new Graphical::NCurses();
        obj->init(mediator);
        return obj;
    }
    Core::ModInfo GetHeader()
    {
        Core::ModInfo info;
        info.type = Core::ModInfo::Type::GRAPHIC;
        info.name = "NCurses";
        return info;
    }
}
