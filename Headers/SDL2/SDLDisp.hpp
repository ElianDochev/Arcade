/*
** EPITECH PROJECT, 2023
** Paradigms Seminar
** File description:
** Exercise 02
*/

#pragma once

#include <thread>
#include <mutex>
#include <queue>
#include <SDL2/SDL.h>
#include <ncurses.h>
#include "../Games/AEvents.hpp"
#include "../Abstracts/IGame.hpp"
#include "../Abstracts/IMediator.hpp"
#include "../Abstracts/IGraphic.hpp"
#include "../Abstracts/IModule.hpp"
#include <vector>
#include <memory>
#include <string>
#include <map>

namespace Graphical
{
    class SDLDisp : public IGraphic
    {
    public:
        //! @brief Default constructor
        //! @warning In order to properly use this class you must call the init member function
        SDLDisp() = default;
        //! @brief Default copy constructor.
        //! @warning You must call the close member function before the destructor if you called the init member function
        ~SDLDisp() override = default;
        //! @brief Default copy constructor.
        SDLDisplay(const SDLDisplay &) = default;
        //! @brief Default  assignment operator
        SDLDisplay &operator=(const SDLDisplay &) = default;
        //! @brief Initialize this library. (Create windows & so on)
        //! @return True if the initialization was successful. False otherwise.
        bool init(Core::IMediator *) override;
        //! @brief Allow to say to the library to shutdown and free it's content
        //! @return True if the shutdown was successful. False otherwise.
        bool toClose() override;
        //! @brief The event loop of the library
        void event_loop() override;
        //! @brief Get the events that occured since the last call to this function
        std::vector<std::unique_ptr<g::Events::AEvents>> GetEvents() override;
        bool CheckEvents() override
        {
            return !this->_events.empty();
        }
        bool draw(Game::Display::Circle &objs) override;
        //! True if the Line could be drawned. False otherwise.
        //! @param objs the line to draw
        bool draw(Game::Display::Line &objs) override;
        //! @brief True if the rectangle could be drawned. False otherwise.
        //! @param objs the rectangle to draw
        bool draw(Game::Display::Rectangle &objs) override;
        //! @brief True if the Text could be drawned. False otherwise.
        //! @param objs the text to draw
        bool draw(Game::Display::Text &objs) override;
        //! @brief True if the Sprite could be drawned. False otherwise.
        //! @param objs the sprite to draw
        bool draw(Game::Display::Sprite &objs) override;
        //! @brief objects to display gotten from the game
        void draw(std::vector<std::unique_ptr<Game::Display::AObject>> &objs) override;
        bool refresh_screen() override;
        //! @brief Load a sprite
        //! @param path The path to the texture to load
        //! @return Return true if the texture was successfully loaded. False otherwise
        bool load(const std::string &type, const std::string &path) override;
        //! @brief Unload a sprite
        //! @param path The path to the texture to load
        void unload(const std::string &type, const std::string &path) override;
        //! @brief Unload all sprites loaded.
        void unloadAll() override;
        //! @brief Play a sound
        void playSound(Game::Sound &sound) override;

    private:
        //! @brief The window we're rendering on
        SDL_Window *_window = nullptr;
        //! @brief The surface of the window (renderer)
        SDL_Renderer *_windowRenderer = nullptr;
        //! @brief window height when init
        int _windowHeight = 700;
        //! @brief window width when init
        int _windowWidth = 700;
        //! @brief The event structure used in event loop
        SDL_Event event;
        //! @brief The list of events that occured since the last call to GetEvents
        std::vector<std::unique_ptr<Game::Events::AEvents>> _events;
        //! @brief window title when init
        std::string _windowTitle = "SDL2 Display Module";
        //! @brief When true the caller should close this instance
        bool _shouldClose = true;
        //! @brief A list of all the resources that are loaded and cached and then not needed to open again
        //! @info the pair is holding the type of the resource type and pointer to the resource
        //! @details saving string for the path (used to check if the texture is already loaded) and the Texture ptr
        std::map<std::string, std::pair<std::string, void *>> _loadedResources;
        //! @brief A list of the keys that are currently hold
        //! @info keys are inserted in the list when an event keyDown as occurred and pop out when a keyUp occurred
        std::vector<Game::Events::KeyboardEvent::KeyNum> _keysHeld; // < may be useless
        static constexpr std::string_view resourceMusicType = "music";
        //! @brief Font type resource
        static constexpr std::string_view resourceFontType = "font";
        //! @brief Sprite type resource
        static constexpr std::string_view resourceSpriteType = "sprite";
        //! @brief The internal window for the bestfit (resize)
        unsigned int _internalWindowSize;
        //! @brief The offsets to center the internalWindow
        std::pair<unsigned int, unsigned int> _internalWindowOffset;
        //! @brief Binding of a constructor for KeyboardEvent struct
        //! @param key Value of key attribute of struct Events::KeyboardEvent
        //! @param keyType The type of the key registered (Up, Down or Hold)
        //! @return A KeyEvent struct with it's values correctly filled
        static Game::Events::KeyboardEvent _bindKeyEvent(Game::Events::KeyboardEvent::KeyNum key, Game::Events::KeyboardEvent::Type keyType);
        //! @brief Binding of a constructor for MouseEvent struct
        //! @param mouseType Value of type attribute of struct Game::Events::MouseEvent
        //! @param key Value of key attribute of struct Game::Events::MouseEvent
        static Game::Events::MouseEvent _bindMouseEvent(Game::Events::MouseEvent::Type mouseType, Game::Events::MouseEvent::Key key, unsigned int x, unsigned int y);
        //! @brief Binding of a constructor for MoveEvent struct
        //! @param x The x position (in percentage)
        //! @param y The y position (in percentage)
        //! @return A MoveEvent struct with it's values correctly filled
        static Game::Events::MouseMoveMent _bindMoveEvent(unsigned int x, unsigned int y);
        //! @brief Used to set the color of the SDL2 renderer
        //! @param color The color format: RRGGBBAA (1 byte each)
        void setRendererColor(unsigned color);
        //! @brief Allows to get the standard KeyCode for a key
        //! @param key The key given by the SDL2 library
        //! @return A a value for the key in the standard enum KeyCode
        //! @info If no equivalence found the value KeyCode::UNDEFINED is returned
        static Game::Events::KeyboardEvent::KeyNum _getSTDkey(unsigned int key);
        //! @brief Allows to get the standard Click type for a click
        //! @param type The type of click given by the SDL2 library
        //! @return A a value for the click type in the standard enum Type of MouseClickEvent
        //! @info If no equivalence found the value MouseButton::UNDEFINED is returned
        static Game::Events::MouseEvent::Key _getSTDclick(uint8_t type);
        void *createResource(const std::string &type, const std::string &path);
        //! @brief Free the resource given as param
        //! @param resource the pair is holding the type of the resource type and pointer to the resource
        void destResource(const std::pair<std::string, void *> &resource);
        //! @brief Allows to get the result of crossPruduct as precise as the int can be
        //! @param percent The percentage
        //! @param total The total to base the percentage on
        //! @param base The number to be divided with (default 100)
        //! @return The result of the cross product
        static int preciseCrossProduct(float percent, float total, float base = 100.);
        //! @brief Resize correctly the internal window
        void _updateInternalWindow();
    };
};