/*
** EPITECH PROJECT, 2023
** Paradigms Seminar
** File description:
** Exercise 02
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <iostream>
#include "SDLDisp.hpp"

void Graphical::SDLDisp::event_loop()
{
	_events.clear();
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			SDL_Quit();
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				SDL_Quit();
			if (event.key.keysym.sym == SDLK_UP)
				_events.push_back(std::make_unique<Game::Events::AEvents>(Game::Events::KeyboardEvent::UP_ARROW));
			if (event.key.keysym.sym == SDLK_DOWN)
				_events.push_back(std::make_unique<Game::Events::AEvents>(Game::Events::KeyboardEvent::DOWN_ARROW));
			if (event.key.keysym.sym == SDLK_LEFT)
				_events.push_back(std::make_unique<Game::Events::AEvents>(Game::Events::KeyboardEvent::LEFT_ARROW));
			if (event.key.keysym.sym == SDLK_RIGHT)
				_events.push_back(std::make_unique<Game::Events::AEvents>(Game::Events::KeyboardEvent::RIGHT_ARROW));
			if (event.key.keysym.sym == SDLK_SPACE)
				_events.push_back(std::make_unique<Game::Events::AEvents>(Game::Events::KeyboardEvent::SPACE));
			if (event.key.keysym.sym == SDLK_RETURN)
				_events.push_back(std::make_unique<Game::Events::AEvents>(Game::Events::KeyboardEvent::ENTER));
			if (event.key.keysym.sym == SDLK_BACKSPACE)
				_events.push_back(std::make_unique<Game::Events::AEvents>(Game::Events::KeyboardEvent::BACKSPACE));
			if (event.key.keysym.sym == SDLK_w)
				_events.push_back(std::make_unique<Game::Events::AEvents>(Game::Events::KeyboardEvent::KEY_W));
			if (event.key.keysym.sym == SDLK_s)
				_events.push_back(std::make_unique<Game::Events::AEvents>(Game::Events::KeyboardEvent::KEY_S));
			if (event.key.keysym.sym == SDLK_a)
				_events.push_back(std::make_unique<Game::Events::AEvents>(Game::Events::KeyboardEvent::KEY_A));
			if (event.key.keysym.sym == SDLK_d)
				_events.push_back(std::make_unique<Game::Events::AEvents>(Game::Events::KeyboardEvent::KEY_D));
			if (event.key.keysym.sym == SDLK_q)
				_events.push_back(std::make_unique<Game::Events::AEvents>(Game::Events::KeyboardEvent::KEY_Q));
			if (event.key.keysym.sym == SDLK_e)
				_events.push_back(std::make_unique<Game::Events::AEvents>(Game::Events::KeyboardEvent::KEY_E));
		}
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
				_events.push_back(std::make_unique<Game::Events::AEvents>(Game::Events::MouseEvent::Left, event.button.x, event.button.y));
			if (event.button.button == SDL_BUTTON_RIGHT)
				_events.push_back(std::make_unique<Game::Events::AEvents>(Game::Events::MouseEvent::Right, event.button.x, event.button.y));
		}
	}
}

std::vector<std::unique_ptr<Game::Events::AEvents>> Graphical::SDLDisp::GetEvents()
{
	return _events;
}