#include "Game.hpp"

// Initialize variables
// ====================
// Globals
const uint32_t WINDOW_WIDTH = 1920;
const uint32_t HEIGHT = 500;
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
std::mt19937 gRng;


// Time
float Time::_deltaTime = 0.0f;

Game::Game(const std::string& wTitle, const uint32_t wWidth, const uint32_t wHeight)
{
	if (!this->init(wTitle , wWidth, wHeight))
	{
		std::cout << "Couldn't initialize!" << std::endl;
		quit();
	}
	else
	{
		loadMedia();
		gRng.seed(std::random_device()());
		mainLoop();
	}
}


Game::~Game()
{
	if (!_killed)
	{
		this->quit();
	}
}

void Game::loadMedia()
{
	_imageHolder.loadFromFile("Resources/Dog.png", "dog");
}

void Game::mainLoop()
{
	Dog dog("Alejandro", _imageHolder.getTexture("dog"));
	dog.setPosition(Pointi{
		static_cast<int>(WINDOW_WIDTH / 2 - dog.getWidth() / 2),
		static_cast<int>(HEIGHT / 2 - dog.getHeight() / 2)
		});

	Dog dog2("Surgiu", _imageHolder.getTexture("dog"));
	dog2.setPosition(Pointi{
		static_cast<int>(WINDOW_WIDTH / 2 - dog.getWidth() / 2),
		100
		});

	SDL_Event e;
	float lastTime = SDL_GetTicks();
	bool shouldClose = false;
	while (!shouldClose)
	{
		const uint32_t currentTime = SDL_GetTicks();
		Time::setDeltaTime(currentTime - lastTime);
		lastTime = currentTime;

		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				shouldClose = true;
				break;
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					shouldClose = true;
					break;
				}
				break;
			}
		}

		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderClear(gRenderer);

		dog.act();
		dog.render();

		dog2.act();
		dog2.render();

		SDL_RenderPresent(gRenderer);
	}
}

void Game::quit()
{
	_imageHolder.freeAll();

	IMG_Quit();
	SDL_Quit();
	this->_killed = true;
}

bool Game::init(const std::string& wTitle, const uint32_t wWidth, const uint32_t wHeight)
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << SDL_GetError();
		success = false;
	}
	else
	{
		gWindow =
			SDL_CreateWindow(
				wTitle.c_str(),
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				wWidth,
				wHeight,
				SDL_WINDOW_SHOWN
			);

		if (gWindow == nullptr)
		{
			std::cout << SDL_GetError();
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

			if (gRenderer == nullptr)
			{
				std::cout << SDL_GetError();
				success = false;
			}
			else
			{
				_bgColor = Color(255, 255, 255, 255);
				SDL_SetRenderDrawColor(gRenderer, _bgColor.r, _bgColor.g, _bgColor.b, _bgColor.a);

				if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
				{
					std::cout << "SDL_image could not initialize! SDL_image Error: "
						<< IMG_GetError() << '\n';
					success = false;
				}
			}
		}
	}

	return success;
}
