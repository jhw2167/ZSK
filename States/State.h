#pragma once

/*
	Parent class for all states in the game: main menu,
	gameState, pause state, so on and so forth.

*/

//Include Exceptions class
#include "../Exceptions/Exceptions.h"

class State
{
protected:
	/*  Protected Members are availible to
				Base Classes			*/
	sf::RenderWindow* window_ptr;


private:
	

public:

	//Constructors
	State(sf::RenderWindow* w_ptr);


	/*
		Pure virtual functions, all child classes
		MUST define, else compile error
	*/

	virtual void quitState() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	//Destructors
	virtual ~State();
};

