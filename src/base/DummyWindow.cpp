#include "DummyWindow.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

base::DummyWindow::DummyWindow()
{
	SDL_Init(SDL_INIT_VIDEO);

	SDLWindow = SDL_CreateWindow(
		"Hello World",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		windowWidth, windowHeight, 0
	);

	SDLWindowSurface = SDL_GetWindowSurface(SDLWindow);
}

base::DummyWindow::~DummyWindow()
{
	SDL_DestroyWindow(SDLWindow);
}

