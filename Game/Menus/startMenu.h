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
	float wLength;
	float wHeight;

	//Title Vars
	sf::Font arcade;
	sf::Text title1;
	sf::Text title2;
	sf::Vector2f t1Pos;
	sf::Vector2f t2Pos;

	//Subtitle Vars
	sf::Text subtitle1;

	//Option Vars
	short numOptions;

	sf::Text playText;
	sf::Text quitText;

	sf::RectangleShape playRect;
	sf::RectangleShape quitRect;

	//Settings Vars
	sf::RectangleShape settingsRect;

	/*  Init Methods  */
	void initvars();
	void initGameTitle();
	void initMenuOptions();

	/*  Other Functions  */
	void updateOption(short selection);
	void animateTitle();
	void hoverOptions(sf::Vector2i const &mousePos);
	void selectRect(sf::RectangleShape &rect, sf::Text & text);

public:

		/*  Constructors  */
	StartMenu();
	//default constructor, does nothing

	StartMenu(sf::RenderWindow &window);

	//One Line title, One option -- overload for general menu option,
	//	maybe later
	//StartMenu(sf::RenderWindow &window, std::string *options[] );

		/*  Setter Methods  */
	void setWindowSize(sf::RenderWindow &window);
	void setTitlePos(sf::Vector2f const &newPos);
	void setTitleSize(int newSize);

	void setOptionsSize(int txtSize);
	void setOptionsPos(sf::Vector2f const &newPos);
	
	//for options menu, consists of a few boxes


		/*  Accessor Methods  */
	short getOptionSelected();

		/*  Other Functions  */
	void update(sf::Vector2i const &mousePos);

	void drawMenu(sf::RenderWindow &window);

		/*  Destructors  */
	virtual ~StartMenu();
};



