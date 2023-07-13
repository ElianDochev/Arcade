/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** main
*/

#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "../Headers/Core/CoreMediator.hpp"

static const int MICROSECONDS_FOR_FRAME = 100000;

std::string GRAPH_LIB_FOR_MENU;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Must pass only the graphic lib\n";
        return 84;
    }
    try
    {
        GRAPH_LIB_FOR_MENU = argv[1];
        std::unique_ptr<Core::IMediator> core = std::make_unique<Core::CoreMediator>(argv[1]);

        while (core->toExit() == false)
        {
            // usleep(150000);
            auto start = std::chrono::steady_clock::now();
            // if there is an update from the graphical
            core->getGraphic()->event_loop();
            core->getGraphic()->clear_screen();
            if (core->getGraphic()->CheckEvents())
            {
                // gets the event that has been passed from the graphical to the mediator (event movement, pause)
                auto events = core->getGraphic()->GetEvents();
                // we should check if the event changes the game state or the graphical state
                // passes the event to the game
                for (auto &event : events)
                {
                    if (event->type == Game::Events::KeyboardEvent::KeyPressed && event->key == Game::Events::KeyboardEvent::KEY_Q)
                    {
                        core->changeGraphLib(-1);
                    }
                    if (event->type == Game::Events::KeyboardEvent::KeyPressed && event->key == Game::Events::KeyboardEvent::KEY_E)
                    {
                        core->changeGraphLib(1);
                    }
                    core->getGame()->handleEvent(*event);
                    if (core->toExit())
                        break;
                    if (event->type == Game::Events::KeyboardEvent::KeyPressed && event->key == Game::Events::KeyboardEvent::ESCAPE)
                    {
                        core->returnToMenu();
                        break;
                    }
                }
            }
            if (core->toExit())
                break;
            core->ExecChanges();
            if (core->getGame()->UpdateFrame())
            {
                // gets the object to draw
                auto &objects = core->getGame()->getObject();
                // passes the object to the graphical
                core->getGraphic()->draw(objects);
                // displays the buffeded objects
            }
            else
            {
                core->returnToMenu();
            }
            auto end = std::chrono::steady_clock::now();
            auto process_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            if (process_time < std::chrono::microseconds(MICROSECONDS_FOR_FRAME))
            {
                std::this_thread::sleep_for(std::chrono::microseconds(MICROSECONDS_FOR_FRAME) - process_time);
            }
            core->getGraphic()->refresh_screen();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception caught: " << e.what() << '\n';
        return 84;
    }
    return 0;
}
