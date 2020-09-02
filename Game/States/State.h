#pragma once

/*
	Parent class for all states in the game: main menu,
	gameState, pause state, so on and so forth.

*/

//Include Exceptions class
#include "../../BaseCode/Exceptions/Exceptions.h"

class State
{
protected:
	/*  Protected Members are availible to
				Base Classes			*/
	sf::RenderWindow* window_ptr;
	std::vector<sf::Event>* events;

private:
	//Private Variables

public:

	//Constructors
	State(sf::RenderWindow* w_ptr, std::vector<sf::Event>* evs);


	/*
		Pure virtual functions, all child classes
		MUST define, else compile error
	*/

	virtual short update(sf::Vector2i &mousePos, const float& dt) = 0;
	virtual void render(sf::RenderTarget* rt = nullptr) = 0;
	virtual void quitState() = 0;

	//Destructors
	virtual ~State();
};

