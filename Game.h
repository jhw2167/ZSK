#pragma once
//Ensures game engine defined only once

/*
	Zombie Slayer Killer (ZSK) development code, main.h file
	ZSK is a third person, 2D simplistic shooter/follower arcade game
	with a bit of a twist adding the tower dynamic to assist zombie slaying
*/

/*
	Visual Studious Visual C++ 2017 version 15.9.5
	SMFL for Visual C++ 15, version 2.5.1 for 32 bit OS
	Last updated *6/24/2020*
	SFML Directory: C:/Development/SFML-2.5.1
*/
  

//Game engine/wrapper stored collectively in game class

//Precompiled header
#include "States/State.h"
#include "Menus/startMenu.h"



class Game
{
private:
	//Variables

	//Window
	sf::RenderWindow *window_ptr;
	sf::VideoMode vidMode;
	sf::Event event;

	//Clock variables, move irrespective to framerate
	float dt;
	sf::Clock dtClock;

	//Menus
	StartMenu *startMenu_ptr;

	short gameState;
	//0 - Startmenu, 1 - in game, 2 - pauseMenu
	//3 - quit

	/******************/
	//Private functions
	/*****************/

	/* Init Functions*/
	void initVars();
	void initWindow();
	void initStartMenu();

	//Game Update functions

	/* LEVEL 1 - Start Menu*/
	void runStartMenu();
	void pauseMenu();

	void isGameOver();

	/*  Draw Functions  */
	void drawStartMenu();
	void drawPauseMenu();


	/* Other Functions  */
	void reset();
	void updateDt();
	//resets player, follower and tower vectors,
	// by clearing all vector elements and reinitializing

	//END PRIVATE FUNCTIONS

public:

	//Constructors / Destructors
	Game();
	virtual ~Game();

	//Modifiers

	//Accessors
	const bool windowIsOpen() const;

	//Functions
	void addPlayer();

	void pollEvents();
	void updateMousePosition();

	void update();
	void render();
};

