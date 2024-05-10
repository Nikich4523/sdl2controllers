#pragma once

class SDL_Surface;
class SDL_Window;

namespace base
{


class DummyWindow
{
public:
	DummyWindow();
private:
	SDL_Window *SDLWindow{nullptr};
	SDL_Surface *SDLWindowSurface{nullptr};
	int windowWidth{300};
	int windowHeight{300};
};


}

