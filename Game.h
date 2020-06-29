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
#include "stdafx.h"

//Project includes
#include "Bullet.h"
#include "FollowerShape.h"
#include "Player.h"
#include "Follower.h"
#include "FollowerShape.h"
#include "Tower.h"
#include "startMenu.h"

class Game
{
private:
	//Variables

	//Window
	sf::RenderWindow *window_ptr;
	sf::VideoMode vidMode;
	sf::Event event;

	//Menus
	StartMenu *startMenu_ptr;

	//Game Based Vectors
	std::vector<Player> players;
	std::vector<Follower> activeFollowers;
	std::vector<Tower> towers;
	sf::Vector2i mousePos;

	//Simple Game Values
	int numPlayers;
	int maxPlayers;
	int numberOfTowers;
	//number of towers is 

	short gameState;
	//0 - Startmenu, 1 - in game, 2 - pauseMenu
	//3 - quit

	/******************/
	//Private functions
	/*****************/

	/* Init Functions*/
	void initTowers();
	void initVars();
	void initWindow();
	void initStartMenu();

	//Game Update functions

	/* LEVEL 1 - Start Menu*/
	void runStartMenu();
	void pauseMenu();


	/* LEVEL 1  -  Call From Update*/
	void movePlayerLogic();
	void shootingMechanics();
	void followerMechanics();
	void isGameOver();

	/* LEVEL 2  -  Followers*/
	void spawnFollowers();
	void moveFollowers();
	void shootFollowers();
	void attackPlayer();

	/* LEVEL 2  -  Towers*/
	int checkTowerCollision();


	/* LEVEL 3  -  Draw Functions*/
	void drawPlayers();
	void drawFollowers();
	void drawTowers();

	void drawStartMenu();
	void drawPauseMenu();

	//END PRIVATE FUNCTIONS

public:

	//Constructors / Destructors
	Game();
	virtual ~Game();

	//SETTERS

	//GETTERS
	const bool windowIsOpen() const;

	//Functions
	void addPlayer();

	void pollEvents();
	void updateMousePosition();

	void update();
	void render();
};

