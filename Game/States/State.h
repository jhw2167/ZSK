#pragma once

/*
	Parent class for all states in the game: main menu,
	gameState, pause state, so on and so forth.

*/

//Include Exceptions class
#include "../../BaseCode/Exceptions/Exceptions.h"
#include "../../BaseCode/Globals/Globals.h"

class State
{
protected:
	/*  Protected Members are availible to
				Base Classes			*/
	static std::shared_ptr<sf::RenderWindow> window_ptr;
	static std::shared_ptr<sf::Mouse> mouse_ptr;
	static std::shared_ptr<std::vector<sf::Event>> events_ptr;

	static STATE gameState;

private:
	//Private Variables

public:

	//Constructors
	State();


	//Set Static variables
	static void setWindow(const std::shared_ptr<sf::RenderWindow>& w_ptr);
	static void setMouse(const std::shared_ptr<sf::Mouse>& m_ptr);
	static void setEvents(const std::shared_ptr<std::vector<sf::Event>>& evs_ptr);


	/*
		Pure virtual functions, all child classes
		MUST define, else compile error
	*/

	virtual STATE update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* rt = nullptr) = 0;
	virtual void quitState() = 0;

	//Destructors
	virtual ~State();
};

