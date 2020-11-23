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
#include "States/gameState.h"
#include "States/MenuState.h"
#include "States/LobbyState.h"


//Template definition

class Game
{
private:
	//Variables

	//Window
	sf::RenderWindow* window_ptr;
	sf::VideoMode vidMode;
	sf::Event event;

	std::vector<sf::Event> events;
	sf::Vector2i mousePos;

	//Clock variables, move irrespective to framerate
	float dt;
	sf::Clock dtClock;

	//Menus
	std::stack<State*> states;

	//Game Based
	short numPlayers;
	const static short maxPlayers;

	STATE gameState;
	//0 - Startmenu, 1 - Lobby, 2 - pauseMenu
	//Peek enum definition in Globals H


	/******************/
	//Private functions
	/*****************/

		/* Init Functions*/
	void initVars();
	void initWindow();
	void initStartMenu();

		/*  Game Update Function  */
	void updateGameState(STATE gs);

	template<class stateType>
	void updateState(bool pop);
	//inline definition for function class

	void isGameOver();

	/* Other Functions  */
	void updateDt();
	
	//END PRIVATE FUNCTIONS

public:

		/*  Constructors  */
	Game();
	virtual ~Game();

		/*  Modifiers  */


		/*  Accessors  */
	const bool windowIsOpen() const;


		/*  Other Public Functions  */
	void addPlayer();

	void pollEvents();
	void updateMousePosition();

	void update();
	void render();
};


template<class stateType>
inline void Game::updateState(bool pop)
{
	if (pop && !states.empty()) {
		delete states.top();
		states.pop();
	}
	
	State* s = new stateType(window_ptr, &events);
	states.push(s);
}