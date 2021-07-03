#pragma once

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <array>
#include <string>
#include <cstdlib>

void coutTests();

int coutTests(int argc, char *argv[])
{
	int switchChoice = 0;

	while (switchChoice == 0)
	{
		std::cout << "What to run? " << std::endl;
		std::cout << "Option 1: cout test creator" << std::endl;
		std::cout << "Option 2: opt 2: " << std::endl;

		std::cin >> switchChoice;
		std::cout << std::endl;
	}

	switch (switchChoice)
	{

	case 1:
		coutTests();
		break;

	case 2:
		exit(1);
		break;

	default:
		exit(2);

	}

	system("pause");


	return 0;
}

void coutTests()
{
	std::vector<std::string> vars;				//initiates vector to hold string objects that will be variables 
	std::vector<std::string> quotedVars;		//to test in other programs
	std::string varToAdd;						//temp string variable will add vars to print message
	std::string q = " \" ";

	int totalVars = 0;

	std::cout << "Number of variables: ";
	std::cin >> totalVars;
	std::cout << std::endl;

	do
	{

		std::cout << "Input variable to print: ";
		std::cin >> varToAdd;

		vars.push_back(varToAdd);			// adds var to vector

		quotedVars.push_back(q + varToAdd + ": " + q);

	} while (--totalVars > 0);


	for (unsigned int a = 0; a < vars.size(); a++)
	{
		if (a == 0)
			std::cout << std::endl << "std::cout << std::endl << ";

		std::cout << quotedVars.at(a) << vars.at(a) << " << std::endl << ";

		if (a == vars.size() - 1)								//ends statement with semicolon if last element in vector
			std::cout << "\b\b\b\b" << ";  "
			<< std::endl << std::endl;

		if (a % 3 == 0)											//spaces variables out nicely
			std::cout << std::endl;
	}

}
