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

namespace Game
{
	bool SDLDisp::init()
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		{
			std::cerr << "SDL wasn't able to initialize " << SDL_GetError() << std::endl;
			return false;
		}
	}

	bool SDLDisp::refresh()
	{
		SDL_Rect fillRect = {0, 0, 0, 0};

		this->setRendererColor(0);
		fillRect.w = this->_internalWindowOffset.first;
		fillRect.h = this->_windowHeight;
		SDL_RenderFillRect(this->_windowRenderer, &fillRect);

		fillRect.x = this->_internalWindowOffset.first + this->_internalWindowSize;
		SDL_RenderFillRect(this->_windowRenderer, &fillRect);

		fillRect.x = 0;
		fillRect.y = 0;
		fillRect.w = this->_windowWidth;
		fillRect.h = this->_internalWindowOffset.second;
		SDL_RenderFillRect(this->_windowRenderer, &fillRect);

		fillRect.x = 0;
		fillRect.y = this->_internalWindowOffset.second + this->_internalWindowSize;
		SDL_RenderFillRect(this->_windowRenderer, &fillRect);

		this->setRendererColor(0);
		SDL_RenderPresent(this->_windowRenderer);
		SDL_RenderClear(this->_windowRenderer);
		return true;
	}

	void SDLDisp::setRendererColor(unsigned int color)
	{
		SDL_SetRenderDrawColor(this->_windowRenderer,
							   (color & (0xFF << 24)) >> 24,
							   (color & (0xFF << 16)) >> 16,
							   (color & (0xFF << 8)) >> 8,
							   color & 0xFF);
	}

	ModInfo::Type SDLDisplay::getType() const
	{
		return ModInfo::GRAPHIC;
	}

	bool SDLDisp::load(const std::string &type, const std::string &path)
	{
		void *resource;

		if (this->_loadedResources.find(path) != this->_loadedResources.end())
		{
			return false;
		}
		resource = this->createResource(type, path);
		if (!resource)
		{
			std::cerr << "Failed to load: " << path << " of type " << type << std::endl;
			if (type == resourceSpriteType)
			{
				std::cerr << SDL_GetError() << std::endl;
			}
			return false;
		}
		this->_loadedResources[path] = std::make_pair(type, resource);
		return true;
	}

	void SDLDisp::unload(const std::string &type, const std::string &path)
	{
		if (this->_loadedResources.find(path) != this->_loadedResources.end())
		{
			this->destResource(this->_loadedResources[path]);
			this->_loadedResources.erase(path);
		}
	}

	void SDLDisp::unloadAll()
	{
		for (auto iter = this->_loadedResources.begin(); iter != this->_loadedResources.end(); ++iter)
		{
			this->unload(iter->first, iter->second.first);
		}
		this->_loadedResources.clear();
	}

	void SDLDisp::destResource(const std::pair<std::string, void *> &resource)
	{
		switch (resource.first)
		{
		case resourceSpriteType:
			SDL_DestroyTexture(static_cast<SDL_Texture *>(resource.second));
			break;
		case resourceFontType:
			TTF_CloseFont(static_cast<TTF_Font *>(resource.second));
			break;
		case resourceMusicType:
			Mix_FreeMusic(static_cast<Mix_Music *>(resource.second));
			break;
		default:
			break;
		}
	}

	void *SDLDisp::createResource(const std::string &type, const std::string &path)
	{
		switch (type)
		{
		case resourceSpriteType:
			return IMG_LoadTexture(this->_windowRenderer, path.c_str());
		case resourceFontType:
			return TTF_OpenFont(path.c_str(), 219);
		case resourceMusicType:
			return Mix_LoadMUS(path.c_str());
		default:
			return nullptr;
		}
	}

	void SDLDisp::playSound(Sound &sound)
	{
		int loops = 1;
		if (this->_loadedResources.find(sound.path) == this->_loadedResources.end())
			return;
		if (this->_loadedResources[sound.path].first != resourceMusicType)
			return;
		if (sound.loop)
			loops = -1;
		Mix_PlayMusic(static_cast<Mix_Music *>(this->_loadedResources[sound.path].second), loops);
	}

	int SDLDisp::preciseCrossProduct(float percent, float total, float base)
	{
		return static_cast<int>(percent * (total / base)) + 1;
	}

	void SDLDisp::_updateInternalWindow()
	{
		this->_internalWindowSize = std::min(this->_windowWidth, this->_windowHeight);
		this->_internalWindowOffset.first = std::max(0U, (this->_windowWidth - this->_internalWindowSize) / 2);
		this->_internalWindowOffset.second = std::max(0U, (this->_windowHeight - this->_internalWindowSize) / 2);
	}

}

extern "C" ModInfo GetHeader()
{
	ModInfo module;
	module.name = "SDL2";
	module.type = ModInfo::GRAPHIC;
	return module;
}

extern "C" Game::IMod *GetModule(Core::IMediator *mediator)
{
	auto *module = new SDLDisp();
	module->init(mediator);
	return module;
}
