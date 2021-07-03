#pragma once

//gameState extends state.h to build gameState object
#include "State.h"

//Project includes

//necesary (most downstream) includes
#include "../GameFiles/CoreFiles/Follower.h"

//Implicit Includes
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

	//Game objs - ALL GAME ENTITIES: Players, towers, followers etc..
	std::shared_ptr<ListMap<GameObj*>> objs;

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
	void binSep(const std::shared_ptr<list<GameObj*>> actObjs,
		std::vector<std::shared_ptr<list<GameObj*>>>& quads, sf::FloatRect area, int lvl);
	void determineCollisions(const std::vector<std::shared_ptr<list<GameObj*>>>& quads);
	void deleteBins(std::vector<std::shared_ptr<list<GameObj*>>>& quads);

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
	GameState();

	//Modifiers
	
	//Accessors


	/*  Other Public Functions  */

	//Generic Functions
	static void setNumPlayerVars(const int maxPlayersForGame = 4);
	static void addPlayer();

	//Virtual Functions
	virtual void quitState();
	virtual STATE update(const float& dt);
	virtual void render(sf::RenderTarget* rt = nullptr);

		/*  Destructor  */
	virtual ~GameState();
};

