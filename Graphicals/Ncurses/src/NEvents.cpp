#include "../../../Headers/NCurses/NCurses.hpp"

namespace ev = Game::Events;

static bool win_changed = false; // used to detect window resize

void Graphical::NCurses::_win_resize(int sig)
{
    (void)sig;
    win_changed = true;
}

void Graphical::NCurses::event_loop()
{
    int ch;
    MEVENT event;

    if (win_changed)
    {
        getmaxyx(stdscr, max_y, max_x);
        move(max_y / 2, max_x / 2);
        refresh();
        win_changed = false;
    }

    while ((ch = getch()) != ERR)
    {
        if (ch == KEY_MOUSE)
        {
            if (getmouse(&event) == OK)
            {
                _queue.push(std::make_pair(ch, event));
            }
        }
        else
        {
            _queue.push(std::make_pair(ch, event));
        }
    }
}

std::vector<std::unique_ptr<g::Events::AEvents>> Graphical::NCurses::GetEvents()
{
    std::vector<std::unique_ptr<g::Events::AEvents>> events;

    while (!_queue.empty())
    {
        std::unique_ptr<g::Events::AEvents> ptr;
        if (_queue.front().first == KEY_MOUSE)
        {
            std::unique_ptr<g::Events::AEvents> event = std::make_unique<ev::MouseEvent>();
            MEVENT mouse_event = _queue.front().second;
            // std::cerr << "mouse_event.bstate: " << mouse_event.bstate << std::endl;
            switch (mouse_event.bstate) // sometimes it cant detect the button pressed
            {
            case BUTTON1_CLICKED:
            case BUTTON1_PRESSED:
                event->key = ev::MouseEvent::Left;
                event->type = ev::MouseEvent::MouseClick;
                break;
            case BUTTON1_RELEASED:
                event->key = ev::MouseEvent::Left;
                event->type = ev::MouseEvent::MouseRelease;
                break;
            case BUTTON2_CLICKED:
            case BUTTON2_PRESSED:
                event->key = ev::MouseEvent::Middle;
                event->type = ev::MouseEvent::MouseClick;
                break;
            case BUTTON2_RELEASED:
                event->key = ev::MouseEvent::Middle;
                event->type = ev::MouseEvent::MouseRelease;
                break;
            case BUTTON3_CLICKED:
            case BUTTON3_PRESSED:
                event->key = ev::MouseEvent::Right;
                event->type = ev::MouseEvent::MouseClick;
                break;
            case BUTTON3_RELEASED:
                event->key = ev::MouseEvent::Right;
                event->type = ev::MouseEvent::MouseRelease;
                break;
            default:
                event->key = ev::MouseEvent::Undetified;
                event->type = ev::MouseEvent::Undetified;
                break;
            }
            auto &mouse = event->getMouse();
            mouse.value().x = (float)mouse_event.x;
            mouse.value().y = (float)mouse_event.y;
            _pos_to_percent(mouse.value());
            // std::cerr << "Event: , type: " << event->type << ", key: " << event->key << ", mouse x " << mouse_event.x << ", mouse y " << mouse_event.y << std::endl;
            ptr = std::move(event);
            // printw("Event: , type: %d, key: %d, mouse x %d, mouse y %d\n", event->type, event->key, mouse_event.x, mouse_event.y);
        }
        else
        {
            std::unique_ptr<g::Events::AEvents> event = std::make_unique<ev::KeyboardEvent>();
            auto event_type = _get_event_type(_queue.front().first);
            event->type = event_type.first;
            event->key = event_type.second;
            ptr = std::move(event);
            // printw("Event: , type: %d, key: %d\n", event->type, event->key);
        }
        events.push_back(std::move(ptr));
        _queue.pop();
    }
    return events;
}

std::pair<int, int> Graphical::NCurses::_get_event_type(int c)
{
    int keynum = 0;

    switch (c)
    {
    case KEY_BACKSPACE:
        keynum = ev::KeyboardEvent::BACKSPACE;
        break;
    case KEY_BTAB:
        keynum = ev::KeyboardEvent::TAB;
        break;
    case 10: // shit my pants
        keynum = ev::KeyboardEvent::ENTER;
        break;
    case KEY_DC:
        keynum = ev::KeyboardEvent::DELETE;
        break;
    case KEY_UP:
        keynum = ev::KeyboardEvent::UP_ARROW;
        break;
    case KEY_DOWN:
        keynum = ev::KeyboardEvent::DOWN_ARROW;
        break;
    case KEY_LEFT:
        keynum = ev::KeyboardEvent::LEFT_ARROW;
        break;
    case KEY_RIGHT:
        keynum = ev::KeyboardEvent::RIGHT_ARROW;
        break;
    case KEY_HOME:
        keynum = ev::KeyboardEvent::HOME;
        break;
    case KEY_END:
        keynum = ev::KeyboardEvent::END;
        break;
    case KEY_PPAGE:
        keynum = ev::KeyboardEvent::PAGE_UP;
        break;
    case KEY_NPAGE:
        keynum = ev::KeyboardEvent::PAGE_DOWN;
        break;
    case KEY_IC:
        keynum = ev::KeyboardEvent::INSERT;
        break;
    case KEY_F(1):
        keynum = ev::KeyboardEvent::F1;
        break;
    case KEY_F(2):
        keynum = ev::KeyboardEvent::F2;
        break;
    case KEY_F(3):
        keynum = ev::KeyboardEvent::F3;
        break;
    case KEY_F(4):
        keynum = ev::KeyboardEvent::F4;
        break;
    case KEY_F(5):
        keynum = ev::KeyboardEvent::F5;
        break;
    case KEY_F(6):
        keynum = ev::KeyboardEvent::F6;
        break;
    case KEY_F(7):
        keynum = ev::KeyboardEvent::F7;
        break;
    case KEY_F(8):
        keynum = ev::KeyboardEvent::F8;
        break;
    case KEY_F(9):
        keynum = ev::KeyboardEvent::F9;
        break;
    case KEY_F(10):
        keynum = ev::KeyboardEvent::F10;
        break;
    case KEY_F(11):
        keynum = ev::KeyboardEvent::F11;
        break;
    case KEY_F(12):
        keynum = ev::KeyboardEvent::F12;
        break;
    case KEY_ESC:
        keynum = ev::KeyboardEvent::ESCAPE;
        break;
    default:
        if (c >= 32 && c <= 126)
            keynum = c;
        else
            keynum = ev::KeyboardEvent::UNDEFINED;
        break;
    }
    return std::make_pair(ev::KeyboardEvent::KeyPressed, keynum);
}

// #include "../Headers/NCurses/NEvents.hpp"
// #include <bits/stdc++.h>

// namespace ev = Game::Events;
// namespace entity = Game::Display;
// using Ptr = std::unique_ptr<ev::AEvents>;

// NEvents::NEvents(int exit_key)
// {
//     running = false;
//     _window = stdscr;
//     _exit_key = _get_exit_key(exit_key);
// }

// NEvents::NEvents(WINDOW *window, int exit_key)
// {
//     running = false;
//     _window = window;
//     _exit_key = _get_exit_key(exit_key);
// }

// void NEvents::SetWindow(WINDOW *window)
// {
//     _window = window;
// }

// void NEvents::Start()
// {
//     if (running)
//         return;
//     running = true;
//     _thread = std::thread(&NEvents::_thread_function, this);
// }

// void NEvents::Stop()
// {
//     // if (running)
//     // {
//     running.store(false);
//     ungetch('q');
//     _thread.join();
//     // }
//     // running = false;
// }

// int NEvents::_get_exit_key(int c)
// {
//     if (c == KEY_ESC)
//         return ev::KeyboardEvent::KeyNum::ESCAPE;
//     return std::tolower(c);
// }

// NEvents::~NEvents()
// {
//     assert(!running);
// }

// bool NEvents::Check_Event()
// {
//     std::lock_guard<std::mutex> lock(_mutex);
//     return !_queue.empty();
// }

// std::queue<std::pair<int, MEVENT>> NEvents::GetEvents()
// {
//     std::lock_guard<std::mutex> lock(_mutex);
//     std::queue<std::pair<int, MEVENT>> events;
//     std::swap(events, _queue);
//     return events;
// }

// std::vector<Ptr> NEvents::GetParcedEvents()
// {
//     std::lock_guard<std::mutex> lock(_mutex);
//     std::vector<Ptr> events;

//     while (!_queue.empty())
//     {
//         Ptr ptr;
//         if (_queue.front().first == KEY_MOUSE)
//         {
//             Ptr event = std::make_unique<ev::MouseEvent>();
//             MEVENT mouse_event = _queue.front().second;
//             switch (mouse_event.bstate) // sometimes it cant detect the button pressed
//             {
//             case BUTTON1_PRESSED:
//                 event->key = ev::MouseEvent::Left;
//                 event->type = ev::MouseEvent::MouseClick;
//                 break;
//             case BUTTON1_RELEASED:
//                 event->key = ev::MouseEvent::Left;
//                 event->type = ev::MouseEvent::MouseRelease;
//                 break;
//             case BUTTON2_PRESSED:
//                 event->key = ev::MouseEvent::Middle;
//                 event->type = ev::MouseEvent::MouseClick;
//                 break;
//             case BUTTON2_RELEASED:
//                 event->key = ev::MouseEvent::Middle;
//                 event->type = ev::MouseEvent::MouseRelease;
//                 break;
//             case BUTTON3_PRESSED:
//                 event->key = ev::MouseEvent::Right;
//                 event->type = ev::MouseEvent::MouseClick;
//                 break;
//             case BUTTON3_RELEASED:
//                 event->key = ev::MouseEvent::Right;
//                 event->type = ev::MouseEvent::MouseRelease;
//                 break;
//             default:
//                 event->key = ev::MouseEvent::Undetified;
//                 event->type = ev::MouseEvent::Undetified;
//                 break;
//             }
//             auto &mouse = event->getMouse();
//             mouse.value().x = (float)mouse_event.x;
//             mouse.value().y = (float)mouse_event.y;
//             ptr = std::move(event);
//         }
//         else
//         {
//             Ptr event = std::make_unique<ev::KeyboardEvent>();
//             auto event_type = _get_event_type(_queue.front().first);
//             event->type = event_type.first;
//             event->key = event_type.second;
//             ptr = std::move(event);
//         }
//         events.push_back(std::move(ptr));
//         _queue.pop();
//     }
//     std::cerr << events.size() << '\n';
//     return events;
// }

// std::pair<int, int> NEvents::_get_event_type(int c)
// {
//     int keynum = 0;

//     switch (c)
//     {
//     case KEY_BACKSPACE:
//         keynum = ev::KeyboardEvent::BACKSPACE;
//         break;
//     case KEY_BTAB:
//         keynum = ev::KeyboardEvent::TAB;
//         break;
//     case KEY_ENTER:
//         keynum = ev::KeyboardEvent::ENTER;
//         break;
//     case KEY_DC:
//         keynum = ev::KeyboardEvent::DELETE;
//         break;
//     case KEY_UP:
//         keynum = ev::KeyboardEvent::UP_ARROW;
//         break;
//     case KEY_DOWN:
//         keynum = ev::KeyboardEvent::DOWN_ARROW;
//         break;
//     case KEY_LEFT:
//         keynum = ev::KeyboardEvent::LEFT_ARROW;
//         break;
//     case KEY_RIGHT:
//         keynum = ev::KeyboardEvent::RIGHT_ARROW;
//         break;
//     case KEY_HOME:
//         keynum = ev::KeyboardEvent::HOME;
//         break;
//     case KEY_END:
//         keynum = ev::KeyboardEvent::END;
//         break;
//     case KEY_PPAGE:
//         keynum = ev::KeyboardEvent::PAGE_UP;
//         break;
//     case KEY_NPAGE:
//         keynum = ev::KeyboardEvent::PAGE_DOWN;
//         break;
//     case KEY_IC:
//         keynum = ev::KeyboardEvent::INSERT;
//         break;
//     case KEY_F(1):
//         keynum = ev::KeyboardEvent::F1;
//         break;
//     case KEY_F(2):
//         keynum = ev::KeyboardEvent::F2;
//         break;
//     case KEY_F(3):
//         keynum = ev::KeyboardEvent::F3;
//         break;
//     case KEY_F(4):
//         keynum = ev::KeyboardEvent::F4;
//         break;
//     case KEY_F(5):
//         keynum = ev::KeyboardEvent::F5;
//         break;
//     case KEY_F(6):
//         keynum = ev::KeyboardEvent::F6;
//         break;
//     case KEY_F(7):
//         keynum = ev::KeyboardEvent::F7;
//         break;
//     case KEY_F(8):
//         keynum = ev::KeyboardEvent::F8;
//         break;
//     case KEY_F(9):
//         keynum = ev::KeyboardEvent::F9;
//         break;
//     case KEY_F(10):
//         keynum = ev::KeyboardEvent::F10;
//         break;
//     case KEY_F(11):
//         keynum = ev::KeyboardEvent::F11;
//         break;
//     case KEY_F(12):
//         keynum = ev::KeyboardEvent::F12;
//         break;
//     case KEY_ESC:
//         keynum = ev::KeyboardEvent::ESCAPE;
//         break;
//     default:
//         if (c >= 32 && c <= 126)
//             keynum = c;
//         else
//             keynum = ev::KeyboardEvent::UNDEFINED;
//         break;
//     }
//     return std::make_pair(ev::KeyboardEvent::KeyPressed, keynum);
// }

// void NEvents::_thread_function()
// {
//     int c;
//     MEVENT event;

//     std::cerr << "start " << running.load() << '\n';

//     while (running.load())
//     {
//         std::lock_guard<std::mutex> lock(_mutex);
//         c = wgetch(_window);
//         if (c == KEY_MOUSE)
//         {
//             if (getmouse(&event) == OK)
//             {
//                 _queue.push(std::make_pair(c, event));
//             }
//         }
//         else
//             _queue.push(std::make_pair(c, event));
//         if (c == _exit_key)
//         {
//             running.store(false);
//         }
//     }

//     // std::cerr << "exit " << running.load() << ' ' << c << ' ' << ERR << '\n';
// }
