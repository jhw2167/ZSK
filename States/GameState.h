#pragma once

//gameState extends state.h to build gameState object
#include "State.h"

//Project includes
#include "../Game_Files/Bullet.h"
#include "../Game_Files/FollowerShape.h"
#include "../Game_Files/Player.h"
#include "../Game_Files/Follower.h"
#include "../Game_Files/FollowerShape.h"
#include "../Game_Files/Tower.h"

class GameState :
	public State
{
private:

	//Game Based Vectors
	std::vector<Player> players;
	std::vector<Follower> activeFollowers;
	std::vector<Tower> towers;
	sf::Vector2i mousePos;

	//Simple Game Values
	int numPlayers;
	int maxPlayers;
	int numberOfTowers;
	//number of towers is... 4


	/******************/
	//Private functions
	/*****************/

	/* Init Functions*/
	void initTowers();
	void initVars();


	//Game Update functions

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

	/* Other Functions  */
	void reset();
	void updateDt();


public:

	//Constructors / Destructors
	GameState();

	//Modifiers

	//Accessors

	virtual ~gameState();
};
