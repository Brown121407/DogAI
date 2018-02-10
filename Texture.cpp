#include "Texture.hpp"
#include <SDL_image.h>
#include <iostream>


Texture::Texture()
{
}


Texture::~Texture()
{
}

bool Texture::loadFromFile(const std::string& path)
{
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		std::cout << "Unable to load image " << path
			<< ". SDL_image Error: " << IMG_GetError() << '\n';
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == nullptr)
		{
			std::cout << "Unable to create texture from " << path 
			<< ". SDL Error: " << SDL_GetError() << '\n';
		}
		else
		{
			_width = loadedSurface->w;
			_height = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	_texture = newTexture;
	return _texture != nullptr;
}

void Texture::free()
{
	if (_texture != nullptr)
	{
		SDL_DestroyTexture(_texture);
		_width = 0;
		_height = 0;
	}
}

void Texture::render(int x, int y, SDL_Rect * clip, double angle, SDL_Point * center, SDL_RendererFlip flip) const
{
	SDL_Rect renderQuad = { x, y, _width, _height };
	if (clip != nullptr)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(gRenderer, _texture, clip, &renderQuad, angle, center, flip);
}

uint32_t Texture::getWidth() const
{
	return _width;
}

uint32_t Texture::getHeight() const
{
	return _height;
}
