#pragma once

/*
	Parent class for all states in the game: main menu,
	gameState, pause state, so on and so forth.

*/

//Include Exceptions class
#include "../Exceptions/Exceptions.h"

class State
{
private:


public:
	State();


	/*
		Pure virtual functions, all child classes
		MUST define, else compile error
	*/

	virtual void quitState() = 0;
	virtual void update() = 0;
	virtual void render() = 0;


	virtual ~State();
};

