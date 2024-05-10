#include "getting_started.h"
#include "base/DummyWindow.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_joystick.h>

#include <SDL2/SDL_stdinc.h>
#include <iostream>


namespace getting_started
{

void run()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER))
	{
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
		return;
	}
	std::cout << "SDL initialized\n";

	SDL_GameController *game_controller{nullptr};
	for (int i = 0, cnt = SDL_NumJoysticks(); i < cnt; ++i)
	{
		if (SDL_IsGameController(i))
		{
			game_controller = SDL_GameControllerOpen(i);
			std::cout << "Controller found: " << SDL_GameControllerName(game_controller) << "\n";
			break;
		}
	}

	if (!game_controller)
	{
		std::cout << "Controller did not find\n";
		return;
	}

	base::DummyWindow app;

	SDL_Event event;
	while (true)
	{
		while(SDL_PollEvent(&event)) 
		{
			switch (event.type)
			{
			  case SDL_KEYDOWN: exit(0);
			}
		}

		if (SDL_GameControllerGetButton(game_controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_X))
		{
			std::cout << "Pressed X button\n";
			SDL_GameControllerSetLED(game_controller, 255, 0, 0);
		}
		if (SDL_GameControllerGetButton(game_controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_Y))
		{
			std::cout << "Pressed Y button\n";
			SDL_GameControllerSetLED(game_controller, 0, 255, 0);
		}
		if (SDL_GameControllerGetButton(game_controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A))
		{
			std::cout << "Pressed A button\n";
			SDL_GameControllerSetLED(game_controller, 0, 0, 255);
		}
		if (SDL_GameControllerGetButton(game_controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_B))
		{
			std::cout << "Pressed B button\n";
			SDL_GameControllerSetLED(game_controller, 255, 255, 0);
		}
		if (SDL_GameControllerGetButton(game_controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_UP))
		{
			std::cout << "Pressed ArrowUp button\n";
		}
		if (SDL_GameControllerGetButton(game_controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_DOWN))
		{
			std::cout << "Pressed ArrowDown button\n";
		}
		if (SDL_GameControllerGetButton(game_controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_LEFT))
		{
			std::cout << "Pressed ArrowLeft button\n";
		}
		if (SDL_GameControllerGetButton(game_controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
		{
			std::cout << "Pressed ArrowRight button\n";
		}
		if (SDL_GameControllerGetButton(game_controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_LEFTSTICK))
		{
			std::cout << "Pressed LeftStick button\n";
		}
		if (SDL_GameControllerGetButton(game_controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_RIGHTSTICK))
		{
			std::cout << "Pressed RightStick button\n";
		}
		if (SDL_GameControllerGetButton(game_controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_LEFTSHOULDER))
		{
			std::cout << "Pressed LeftShoulder button\n";
		}
		if (SDL_GameControllerGetButton(game_controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_RIGHTSHOULDER))
		{
			std::cout << "Pressed RightShoulder button\n";
		}
		if (Sint16 deep = SDL_GameControllerGetAxis(game_controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERLEFT))
		{
			std::cout << "Pressed LeftTrigger: " << deep << "\n";
		}
		if (Sint16 deep = SDL_GameControllerGetAxis(game_controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERRIGHT))
		{
			std::cout << "Pressed RightTrigger: " << deep << "\n";
		}
	}
}


}

