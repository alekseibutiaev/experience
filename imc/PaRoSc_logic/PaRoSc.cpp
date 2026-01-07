#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <string>

#include "PaRoSc.h"

parosc::parosc(const int& _attempt) : attempt(_attempt)
{
	srand(static_cast<unsigned int>(time(0)));
}
void parosc::play()
{
	const std::string name[] = { "Scissors", "Rock", "Paper" };
	int res[] = { 0, 0, 0 };
	while (attempt--)
	{
		const int c = computer_choose();
		const int p = player_choose();
		std::cout << "Computer: " << name[c] << " You: " << name[p] << std::endl;
		++res[party(c, p) + 1];
	}
	std::cout << (res[0] < res[2] ? "Computer won !!!" : res[2] < res[0] ? "You won !!!" : "Tie.");
}

int parosc::party(int computer, int player)
{
	static const int res[] = {
		0, -1, 1,
		1, 0, -1,
		-1, 1, 0 };
	return res[computer * 3 + player];
}

int parosc::player_choose() const
{
	for (;;)
	{
		char c;
		std::cout << "Your choose. [P]aper, [R]ock, [S]cissors: ";
		std::cin >> c;
		if (c == 'P' || c == 'p')
			return 2;
		if (c == 'R' || c == 'r')
			return 1;
		if (c == 'S' || c == 's')
			return 0;
		std::cout << std::endl << "incorrect input: " << c << std::endl;
	}
}

int parosc::computer_choose() const
{
	return rand() % 3;
}
