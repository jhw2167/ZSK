#pragma once

/*
	Menu State class contains the Main Game menu and
	possibly other game menus down the line
	-It extends BOTH the State and StartMenu Classes,
	and is pushed onto the states stack at the beginning
	of the Game App
*/


//Project Includes
#include "State.h"
#include "../Menus/startMenu.h"



class MenuState :
	public State
{
private:

	short gameState;
	//0 is main menu state

	StartMenu mainMenu;
	//declare our main menu object

	/*  Private Functions  */


public:

		/*  Constructors  */

	MenuState(sf::RenderWindow* w_ptr);


		/*  Modifiers  */

		/*  Accessors  */

		/*  Other Public Funtions  */
	virtual void update(sf::Vector2i &mousePos);

	virtual void render();

	virtual void quitState();
	

	/*  Destructor  */
	virtual ~MenuState();
};

