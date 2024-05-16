#include "RotateArrow.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

#include <cmath>
#include <cstdlib>
#include <iostream>


RotateArrow::Shutdowner::~Shutdowner()
{
	shutdownSDL();
}

void RotateArrow::run()
{
	printDescription();

	// 1.
	Shutdowner shutdowner;
	if (!initSDL())
	{
		std::cout << "SDL could not be initialized! SDL error: " << SDL_GetError() << "\n";
		return;
	}

	constexpr int width{640};
	constexpr int height{360};
	SDL_Window *window = SDL_CreateWindow("Rotate Arrow Example",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			width, height,
			SDL_WINDOW_SHOWN);
	if (!window)
	{
		std::cout << "SDL Window could not be created! SDL error: " << SDL_GetError() << "\n";
		return;
	}

	constexpr int default_render_driver{-1};
	SDL_Renderer *renderer = SDL_CreateRenderer(window, default_render_driver, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(!renderer)
	{
		std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
		return;
	}

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	if (IMG_Init(IMG_INIT_PNG) < 0) {
		std::cout << "SDL_image could not be initialized! SDL Error: " << SDL_GetError() << "\n";
		return;
	}

	const std::string img_path{"./src/1_rotate_arrow/arrow.png"};
	SDL_Surface *surface = IMG_Load(img_path.c_str());
	if (!surface)
	{
		std::cout << "Could not load " << img_path.c_str() << "!\n";
		return;
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture)
	{
		std::cout << "Could not create texture from surface. SDL Error: " << SDL_GetError() << "\n";
		return;
	}

	const Uint32 start_ms = SDL_GetTicks();
	const Uint32 duration_ms{2000};
	const double rotation_speed{360.0 / duration_ms};
	Uint32 elapsed_ms{0};
    while(elapsed_ms < duration_ms)
    {
		elapsed_ms = SDL_GetTicks() - start_ms;
        SDL_PumpEvents();

		// 2.
        SDL_RenderClear(renderer);
		SDL_RenderCopyEx(renderer, texture, nullptr, nullptr, elapsed_ms * rotation_speed, nullptr, SDL_FLIP_NONE);
        SDL_RenderPresent(renderer);
    }

	// 3. & 4.
	SDL_GameController *gamecontroller{nullptr};
	for (int i = 0, cnt = SDL_NumJoysticks(); i < cnt; ++i)
	{
		if (SDL_IsGameController(i))
		{
			gamecontroller = SDL_GameControllerOpen(i);
		}
	}

	if (!gamecontroller)
	{
		std::cout << "Could not find game controller!\n";
		return;
	}

	const int controller_deadzone_motion{8000};
	double rotation_angle{0.0};

	SDL_Event event;
	while (true)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT: return;
				case SDL_CONTROLLERAXISMOTION:
				{
					if (event.caxis.axis != SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX)
					{
						break;
					}

					const int controller_motion = event.caxis.value;
					if (std::abs(controller_motion) < controller_deadzone_motion)
					{
						break;
					}

					rotation_angle += copysign(rotation_speed, controller_motion);
				}
			}
		}

        SDL_RenderClear(renderer);
		SDL_RenderCopyEx(renderer, texture, nullptr, nullptr, rotation_angle, nullptr, SDL_FLIP_NONE);
        SDL_RenderPresent(renderer);
	}

	// rotate arrow via controller's stick
	// rotate arrow via controller's triggers considering pressing force
}

void RotateArrow:: printDescription()
{
	std::cout << "---------- Rotate Arrow ----------\n";
	std::cout << "1. Create window with arrow texture\n";
	std::cout << "2. Rotate arrow via code\n";
	std::cout << "3. Rotate arrow via controller's stick\n";
	std::cout << "4. Rotate arrow via controller's triggers considering pressing force\n";
	std::cout << "----------------------------------\n\n";
}

bool RotateArrow::initSDL()
{
	return SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) == 0;
}

void RotateArrow::shutdownSDL()
{
	SDL_Quit();
}

