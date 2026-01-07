#include <conio.h>
#include <string>
#include <iostream>

#include "..\PaRoSc_logic\PaRoSc.h"

int main( int ac, char** av)
{
	try
	{
		if (ac >= 2)
		{
			const int attempt = std::stoi(av[1]);
			parosc game(attempt);
			game.play();
			std::cout << std::endl << "please press ESC for exit." << std::endl;
			while ( 27 != getch()) {}
			return 0;
		}
		std::cout << "ussage PaRoSc [attempt count]" << std::endl;
		return 0;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
    return -1;
}

