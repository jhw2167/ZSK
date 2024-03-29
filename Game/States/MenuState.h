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
#include "../Menus/MenuObjects.h"



class MenuState :
	public State
{
private:

	//Title Vars
	sf::Text title1;
	sf::Text title2;
	sf::Vector2f t1Pos;
	sf::Vector2f t2Pos;

	//Subtitle Vars
	sf::Text subtitle1;

	//Option Vars
	int numOptions;

	MenuObjects::Button play;
	MenuObjects::Button quit;

	//Settings Vars
	MenuObjects::Button settings;


	/*  Private Functions  */

	/*  Init Methods  */
	void initvars();
	void initGameTitle();
	void initMenuOptions();

	/*  Other Functions  */
	void updateOption(STATE selection);
	void animateTitle();
	void hoverOptions();


public:

		/*  Constructors  */

	MenuState();


		/*  Modifiers  */
	void setTitlePos(sf::Vector2f const &newPos);
	void setTitleSize(unsigned int newSize);

		/*  Accessors  */
	STATE getOptionSelected();

		/*  Other Public Funtions  */
	virtual STATE update(const float& dt);

	virtual void render(sf::RenderTarget* rt = nullptr);

	virtual void quitState();
	

	/*  Destructor  */
	virtual ~MenuState();
};

