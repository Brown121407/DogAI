#pragma once
#include <string>
#include "globals.hpp"

class Texture
{
public:
	Texture();
	~Texture();

	bool loadFromFile(const std::string& path);

	void free();

	void render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0f, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE) const;

	uint32_t getWidth() const;
	uint32_t getHeight() const;

private:
	SDL_Texture* _texture = nullptr;

	uint32_t _width, _height;
};

