#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include "globals.hpp"
#include "Time.hpp"
#include "Dog.hpp"
#include "ImageHolder.hpp"

class Game
{
public:
	Game(const std::string& wTitle, const uint32_t wWidth, const uint32_t wHeight);
	~Game();

	void loadMedia();

	void mainLoop();

	void quit();
private:
	bool init(const std::string& wTitle, const uint32_t wWidth, const uint32_t wHeight);

	bool _killed = false;
	Color _bgColor;

	ImageHolder _imageHolder;
};

