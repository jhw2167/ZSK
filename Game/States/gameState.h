#pragma once

//gameState extends state.h to build gameState object
#include "State.h"

//Project includes

//necesary (most downstream) includes
#include "../GameFiles/CoreFiles/Follower.h"

//Other Includes
/*
	#include "../GameFiles/CoreFiles/Bullet.h"
	#include "../GameFiles/CoreFiles/FollowerShape.h"
	#include "../GameFiles/CoreFiles/Player.h"
	#include "../GameFiles/CoreFiles/FollowerShape.h"
	#include "../GameFiles/CoreFiles/Tower.h"
*/



class GameState :
	public State
{
private:

	//Game Based Vectors
	std::vector<Player> players;
	std::list<Follower> followers;
	std::vector<Tower> towers;
	sf::Vector2i mousePos;

	//Game objs
	std::unordered_map<int, GameObj*> objs;

	//Simple Game Values
	static int numPlayers;
	static int maxPlayers_this;

	//Fols
	static int maxFollowers;

	//Towers
	int numberOfTowers;
	//number of towers is... 4


	/******************/
	//Private functions
	/*****************/

	/* Init Functions  */
	void initArt();
	void initTowers();
	void initVars();


	//Game Update functions

	/* LEVEL 1  -  Call From Update*/
	void checkCollisions();
	void binSep(std::list<GameObj*>& actObjs, 
		std::vector<std::list<GameObj*>>& quads, sf::FloatRect area, int lvl);
	void determineCollisions(const std::vector<std::list<GameObj*>>& quads);

	void movePlayerLogic();
	void otherPlayerMechs();
	void shootingMechanics();
	void followerMechanics();
	void towerMechanics();
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

	/*  Gamestate Constructor  */
	GameState(sf::RenderWindow* w_ptr, std::vector<sf::Event>* evs);

	//Modifiers
	void setMousePos(sf::Vector2i &mPos);

	//Accessors


	/*  Other Public Functions  */

	//Generic Functions
	static void setNumPlayerVars(const int maxPlayersForGame = 4);
	static void addPlayer();

	//Virtual Functions
	virtual void quitState();
	virtual STATE update(sf::Vector2i &mousePos, const float& dt);
	virtual void render(sf::RenderTarget* rt = nullptr);

		/*  Destructor  */
	virtual ~GameState();
};

