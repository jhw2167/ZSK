#pragma once
/*
	Menu plays upon startup, allows users:
	-to start game
	-join another players game/host multiplayer game
	-check options/game settings
	-quit game

*/

//Precompiled header
#include "../../BaseCode/pch/stdafx.h"
#include "MenuObjects.h"


class StartMenu
{
private:

	short optionSelected;
	//take option 0 ... n for n availible options from start menu
	//and 0 is default

	//Window Vars
	sf::RenderWindow *win_ptr;

	//Title Vars
	sf::Text title1;
	sf::Text title2;
	sf::Vector2f t1Pos;
	sf::Vector2f t2Pos;

	//Subtitle Vars
	sf::Text subtitle1;

	//Option Vars
	short numOptions;

	MenuObjects::Button play;
	MenuObjects::Button quit;

	//Settings Vars
	MenuObjects::Button settings;

	/*  Init Methods  */
	void initvars();
	void initGameTitle();
	void initMenuOptions();

	/*  Other Functions  */
	void updateOption(short selection);
	void animateTitle();
	void hoverOptions();
	
public:

		/*  Constructors  */
	StartMenu();
	//default constructor, does nothing

	StartMenu(sf::RenderWindow &window);

	//One Line title, One option -- overload for general menu option,
	//	maybe later
	//StartMenu(sf::RenderWindow &window, std::string *options[] );

		/*  Setter Methods  */
	void setTitlePos(sf::Vector2f const &newPos);
	void setTitleSize(int newSize);


		/*  Accessor Methods  */
	short getOptionSelected();

		/*  Other Functions  */
	void update(sf::Vector2i const &mousePos);

	void drawMenu(sf::RenderWindow &window);

		/*  Destructors  */
	virtual ~StartMenu();
};



