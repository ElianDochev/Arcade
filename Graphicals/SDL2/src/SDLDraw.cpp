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

    bool SDLDisp::draw(Display::Line &obj)
	{
		this->setRendererColor(obj.color);
		SDL_RenderDrawLine(this->_windowRenderer,
		                   preciseCrossProduct(obj.x, this->_internalWindowSize) + this->_internalWindowOffset.first,
		                   preciseCrossProduct(obj.y, this->_internalWindowSize) + this->_internalWindowOffset.second,
		                   preciseCrossProduct(obj.endX, this->_internalWindowSize) + this->_internalWindowOffset.first,
		                   preciseCrossProduct(obj.endY, this->_internalWindowSize) + this->_internalWindowOffset.second
		);
		this->setRendererColor(0);
		return true;
	}

	bool SDLDisp::draw(Display::Rectangle &obj)
	{
		SDL_Rect fillRect = {preciseCrossProduct(obj.x, this->_internalWindowSize) + static_cast<int>(this->_internalWindowOffset.first),
		                     preciseCrossProduct(obj.y, this->_internalWindowSize) + static_cast<int>(this->_internalWindowOffset.second),
		                     0,
		                     0};
		fillRect.w = preciseCrossProduct(obj.endX, this->_internalWindowSize) - fillRect.x + this->_internalWindowOffset.first;
		fillRect.h = preciseCrossProduct(obj.endY, this->_internalWindowSize) - fillRect.y + this->_internalWindowOffset.second;
		this->setRendererColor(obj.color);
		SDL_RenderFillRect(this->_windowRenderer, &fillRect);
		this->setRendererColor(0);
		return true;
	}

    bool SDLDisp::draw(Display::Circle &obj)
	{
		if (filledCircleRGBA(this->_windowRenderer,
		                     preciseCrossProduct(obj.x, this->_internalWindowSize) + this->_internalWindowOffset.first,
		                     preciseCrossProduct(obj.y, this->_internalWindowSize) + this->_internalWindowOffset.second,
		                     preciseCrossProduct(static_cast<int>(obj.size), this->_internalWindowSize),
		                        (obj.color & (0xFF << 24)) >> 24,
		                        (obj.color & (0xFF << 16)) >> 16,
		                        (obj.color & (0xFF << 8)) >> 8,
		                        obj.color & 0xFF) == 0) {
			this->setRendererColor(0);
			return true;
		}
		return false;
	}


    bool SDLDisp::draw(Display::Text &obj)
	{
		int w;
		int h;
		SDL_Surface *surface;
		SDL_Texture *texture;
		SDL_Rect rect;

		if (this->_loadedResources.find(obj.path) == this->_loadedResources.end()
		    || this->_loadedResources[obj.path].first != resourceFontType) {
			return false;
		}
		if (obj.text.empty()) {
			return true;
		}
		surface = TTF_RenderText_Solid(static_cast<TTF_Font *>(this->_loadedResources[obj.path].second),
		                               obj.text.c_str(),
		                               (SDL_Color) {
			                               static_cast<Uint8>((obj.color & (0xFF << 24)) >> 24),
			                               static_cast<Uint8>((obj.color & (0xFF << 16)) >> 16),
			                               static_cast<Uint8>((obj.color & (0xFF << 8)) >> 8)
		                               });
		if (! surface) {
			return false;
		}
		texture = SDL_CreateTextureFromSurface(this->_windowRenderer, surface);
		if (! texture) {
			SDL_FreeSurface(surface);
			return false;
		}
		SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
		rect.x = preciseCrossProduct(obj.x, this->_internalWindowSize) + this->_internalWindowOffset.first;
		rect.y = preciseCrossProduct(obj.y, this->_internalWindowSize) + this->_internalWindowOffset.second;
		rect.h = static_cast<int>(obj.fontSize);
		rect.w = static_cast<int>((obj.fontSize * w) / h);
		SDL_RenderCopyEx(this->_windowRenderer, texture, nullptr, &rect, 0, nullptr, SDL_FLIP_NONE);
		SDL_DestroyTexture(texture);
		SDL_FreeSurface(surface);
		return true;
	}

    bool SDLDisp::draw(Display::Sprite &obj)
	{
		int w;
		int h;
		std::string path = obj.path;
		SDL_Rect rect;
		SDL_Texture *img;

		if (this->_loadedResources.find(path) == this->_loadedResources.end()
		    || this->_loadedResources[path].first != resourceSprite'Type) {
			return false;
		}
		img = static_cast<SDL_Texture *>(this->_loadedResources[path].second);
		SDL_QueryTexture(img, nullptr, nullptr, &w, &h);
		rect.x = preciseCrossProduct(obj.x, this->_internalWindowSize) + this->_internalWindowOffset.first;
		rect.y = preciseCrossProduct(obj.y, this->_internalWindowSize) + this->_internalWindowOffset.second;
		rect.w = preciseCrossProduct(static_cast<int>(obj.sizeX), this->_internalWindowSize);
		rect.h = preciseCrossProduct(static_cast<int>(obj.sizeY), this->_internalWindowSize);
		rect.x -= rect.w / 2;
		rect.y -= rect.h / 2;
		SDL_RenderCopyEx(this->_windowRenderer, img, nullptr, &rect, obj.rotation, nullptr, SDL_FLIP_NONE);
		return true;
	}
}