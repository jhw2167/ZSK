
//Game Summary

/*
	ZSK or "Zombie Slayer Killer" is a simple 2D animated multiplayer game
	I have developed over the last few months.  The game is designed from 
	scratch in C++ taking advantage of SFML's extensive open source audio,
	graphics and networking libraries. The game is simple, but spans several
	files and hundreds of lines of code to simulate collision mechanics,
	menu's and UI, multiplayer networking and file I/O.
	To design the game, I have made use of solid OOP, polymorphism,
	virtual classes and methods, generic programming, advanced data structures,
	and threading. The two repositories relevant to my project are on my 
	github page above.
*/


//main.h file
#pragma once

//Main file brings all objects together to create the game
#include "Game/Game.h"
#include "Other/coutTests.h"


//TESTS
void vectorTests()
{
	std::cout << " Our new test " << std::endl << std::endl;
	std::vector<int> nums{ 2, 5, 7 };

	for (size_t i = 0; i < nums.size(); i++)
	{
		std::cout << "Nums at i = " << i << " is " << nums[i] << std::endl;
		std::cout << "Nums size is: " << nums.size() << std::endl;
		nums.erase(nums.begin());
		i--;
	}

	getchar();

}