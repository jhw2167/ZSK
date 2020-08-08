#include "MenuState.h"

/*
	Implementation File for MenuState Class
*/



/*  Constructors  */
MenuState::MenuState(sf::RenderWindow* w_ptr) 
	: State(w_ptr), mainMenu(*w_ptr)
{
	gameState = 0;
	//mainMenu = StartMenu(*w_ptr);
}


/*  Modifiers  */

/*  Accessors  */

/*  Other Public Funtions  */

short MenuState::update(sf::Vector2i &mousePos, const float& dt)
{
	//Update and animate title screen
	mainMenu.update(mousePos);
	return mainMenu.getOptionSelected();
}

void MenuState::render(sf::RenderTarget* rt) {
	mainMenu.drawMenu(*window_ptr);
}

void MenuState::quitState()
{
}


/*  Other Private Functions  */


	/*  Destructor  */
MenuState::~MenuState()
{
}
