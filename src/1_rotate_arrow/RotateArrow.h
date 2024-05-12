#pragma once

class SDL_Window;

namespace RotateArrow
{

// RAII-wrap to shutdown all system on quit
class Shutdowner
{
public:
	~Shutdowner();
};

void run();
void printDescription();

bool initSDL();
void shutdownSDL();

}
