#pragma once

//gameState extends state.h to build gameState object
#include "State.h"

//Project includes
#include "../GameFiles/Bullet.h"
#include "../GameFiles/FollowerShape.h"
#include "../GameFiles/Player.h"
#include "../GameFiles/Follower.h"
#include "../GameFiles/FollowerShape.h"
#include "../GameFiles/Tower.h"


class GameState :
	public State
{
private:

	//Game Based Vectors
	std::vector<Player> players;
	std::list<Follower> followers;
	std::vector<Tower> towers;
	sf::Vector2i mousePos;

	//Simple Game Values
	int numPlayers;
	int maxPlayers;

	//Fols
	static int maxFollowers;

	//Towers
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
	bool isGameOver();

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

	/*  g*/
	GameState(sf::RenderWindow* w_ptr);

	//Modifiers
	void setMousePos(sf::Vector2i &mPos);

	//Accessors


	/*  Other Public Functions  */
	virtual void quitState();
	virtual short update(sf::Vector2i &mousePos, const float& dt);
	virtual void render(sf::RenderTarget* rt = nullptr);

		/*  Destructor  */
	virtual ~GameState();
};

