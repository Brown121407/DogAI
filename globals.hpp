#pragma once
#include <SDL.h>
#include <random>

#define DEBUG

extern const uint32_t WINDOW_WIDTH;
extern const uint32_t HEIGHT;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

extern std::mt19937 gRng;

struct Pointf
{
	float x, y;
};

struct Pointi
{
	int x, y;
};

struct Color
{
	uint8_t r, g, b, a;
	Color(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha)
	: r(red), g(green), b(blue), a(alpha)
	{
	}

	Color()
	: r(0), g(0), b(0), a(0)
	{
	}
};