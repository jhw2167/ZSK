//main.h file
#pragma once

//Main file brings all objects together to create the game
#include "Game.h"
#include "coutTests.h"


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