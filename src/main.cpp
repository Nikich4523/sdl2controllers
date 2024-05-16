#include "0_getting_started/getting_started.h"
#include <1_rotate_arrow/RotateArrow.h>

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage: sdl2controllers [example number]\n";
		return 0;
	}
	const int example_arg_index{1};
	const std::string example{argv[example_arg_index]};

	if (example == "0")
	{
		getting_started::run();
	}
	else if (example == "1")
	{
		RotateArrow::run();
	}
	else {
		std::cout << "Unknown example! Check src/ dir, please" << "\n";
	}

	return 0;
}
