// #pragma once

// #include <thread>
// #include <mutex>
// #include <queue>
// #include <ncurses.h>
// #include "../Games/AEvents.hpp"
// #include <vector>
// #include <memory>
// #include <atomic>

// #ifndef KEY_ESC
// #define KEY_ESC 27
// #endif

// class NEvents
// {
// public:
//     NEvents(int exit_key = Game::Events::KeyboardEvent::KeyNum::ESCAPE);
//     NEvents(WINDOW *window, int exit_key = Game::Events::KeyboardEvent::KeyNum::ESCAPE);
//     void SetWindow(WINDOW *window);
//     void Stop();
//     ~NEvents();
//     bool Check_Event();
//     std::queue<std::pair<int, MEVENT>> GetEvents();
//     std::vector<std::unique_ptr<Game::Events::AEvents>> GetParcedEvents();
//     void Start();

// private:
//     std::thread _thread;
//     std::mutex _mutex;
//     std::queue<std::pair<int, MEVENT>> _queue;
//     std::pair<int, int> _get_event_type(int c);
//     WINDOW *_window;
//     std::atomic<bool> running;
//     int _exit_key;
//     int _get_exit_key(int c);
//     void _thread_function();
// };
