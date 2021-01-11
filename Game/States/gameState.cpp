//Implementation file for GameState.h

#include "gameState.h"

/*  CNTRL + M + O to collapse all */

/*  Initializing static variables  */
int GameState::maxFollowers = 1;

int GameState::numPlayers = 0;
int GameState::maxPlayers_this = 0;


	/*  Constructors  */

GameState::GameState(sf::RenderWindow* w_ptr, std::vector<sf::Event>* evs)
	: State(w_ptr, evs)
{
	initVars();
	players.emplace_back(*w_ptr);
	initArt();
	initTowers();
}

/*  Public Static Functions  */
void GameState::setNumPlayerVars(const int maxPlayersThisGame) {
	/*
		Default max players is 4, o/t we set new max players
	*/

	numPlayers = 1;
	//if we start a game we have one player

	maxPlayers_this = maxPlayersThisGame;
	//establish our max players for *this* gamestate instance
}

void GameState::addPlayer() {
	/*
		Adds player to the eventual gamestate, each game
		may have a different number of max players
	*/

	if (numPlayers < maxPlayers_this) {
		numPlayers++;
	}
}

/*  Private Functions  */
void GameState::initArt()
{
	//Const variables - should be, but not actually
	zsk::art::primColor = sf::Color::White;
	zsk::art::secColor = sf::Color::Black;

	zsk::art::winClearColor = sf::Color::White;

	//init playerColors
	zsk::art::playerColors = { sf::Color::Red,
	sf::Color::Blue, sf::Color::Magenta, sf::Color::Green };

}

void GameState::initTowers()
{
	//adds an additional tower out of play that assists with mechanics
	for (size_t i = 0; i < numberOfTowers + 1; i++) {
		//towers.push_back(Tower(*window_ptr, i));
		towers.emplace_back(*window_ptr, i);
	}
}

void GameState::initVars()
{
	/*
		Initiate fundamental non-static vars
	*/
	
	//set number of towers and reserve vector space
	numberOfTowers = std::max(maxPlayers_this, 4);
	towers.reserve(zsk::smallContSz);
	players.reserve(zsk::smallContSz);

	objs.reserve(zsk::lrgContSz);	//reserve 512 * 4 bytes for game Objs
	GameObj::setObjs(&objs);		//set ptr to objs in GameObjs class
}

//Game Update Functions

/*  Collission functions  */
void GameState::checkCollisions()
{
	std::list<GameObj*> activeObjs;
	for (auto& obj : objs) {
		activeObjs.push_back(obj.second);
	}

	std::vector<std::list<GameObj*>> quads;
	sf::FloatRect area(sf::Vector2f(0.0,0.0), 
		sf::Vector2f(window_ptr->getSize()));
	int numQuads = 4;

	//seperate objs into 16 quadrants for collision detection
	binSep(activeObjs, quads, area, numQuads);

	//determine collisions
	determineCollisions(quads);

}

void GameState::binSep(std::list<GameObj*>& actObjs, 
	std::vector<std::list<GameObj*>>& quads, sf::FloatRect side, int lvl)
{
	/*
		Seperate each level of objs unordered map into 
		2 "quadrants" repeatedly until lvl = 0;
	*/

	//create actObjs2 - vector of GameObj*'s NOT in float rect area
	std::list<GameObj*> actObjs2;

	//Determine upper/left area
	sf::FloatRect otherSide(side);
	if ((lvl % 2) == 0) {
		side.height /= 2;
		otherSide.height /= 2;
		otherSide.top += otherSide.height;
	}
	else {
		side.width /= 2;
		otherSide.width /= 2;
		otherSide.left += otherSide.width;
	}

	//test if floatRect contains
		//push back into appropriate vector
	for (const auto& obj : actObjs) 
	{
		if (side.contains(obj->getPos)) {
			//do nothing, obj belongs in this vect
		}
		else {
			actObjs2.push_back(obj);
			actObjs.remove(obj);
		}
	}

	//Call binSep recursively OR push vect onto quads
	if (lvl > 0) {
		binSep(actObjs, quads, side, --lvl);
		binSep(actObjs2, quads, otherSide, lvl);
	}
	else {
		quads.push_back(actObjs);
		quads.push_back(actObjs2);
	}

}

void GameState::determineCollisions(const 
	std::vector<std::list<GameObj*>>& quads)
{
	/*
		For all objs in quadrant 
	*/

	for (const auto& ls : quads)
	{
		//get iterator from list
		auto it1 = ls.begin() ;

		for (auto it2 = ++it1; it2 != ls.end();)
		{
			GameObj* obj1 = it1._Ptr->_Myval;
			GameObj* obj2 = it2._Ptr->_Myval;
			if (obj1->getGlobalBounds().intersects(
				obj2->getGlobalBounds()))
				//compare all objects to each other
			{
				obj1->collisions
			}
			else {
				fol_it2++;
			}
		}
	}

}



/* LEVEL 1  -  Call From Update*/
void GameState::movePlayerLogic()
{
	int towerNum = checkTowerCollision();		//towerNum is initialized to element number  of tower player is colliding with
	enum dir { UP = 1, LEFT, DOWN, RIGHT };

	for (size_t i = 0; i < players.size(); i++)
	{
		//moves player up if not at upwardbounds
	//Yes there needs to be a function call after each if to support directional travel
	//no, you cannot pass the key pressed event.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (players.at(i).getPlayerShape().getUpperBounds() > 0)
				players.at(i).moveLogic(UP, towerNum, towers.at(towerNum).getPosition(),
					towers.at(towerNum).getTowerRadius());
		}
		//move player left if not at left bounds
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			if (players.at(i).getPlayerShape().getLeftBounds() > 0)
				players.at(i).moveLogic(LEFT, towerNum, towers.at(towerNum).getPosition(),
					towers.at(towerNum).getTowerRadius());
		}
		//down
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			if (players.at(i).getPlayerShape().getLowerBounds() < window_ptr->getSize().y)
				players.at(i).moveLogic(DOWN, towerNum, towers.at(towerNum).getPosition(),
					towers.at(towerNum).getTowerRadius());
		}
		//and right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			if (players.at(i).getPlayerShape().getRightBounds() < window_ptr->getSize().x)
				players.at(i).moveLogic(RIGHT, towerNum, towers.at(towerNum).getPosition(),
					towers.at(towerNum).getTowerRadius());
		}

		/*Second parameter in function call accepts bool type, integer type is passed because any int > 0, (i.e. tower num 1,2,3 or 4)
		is interpreted as bool TRUE, if checkTowerColliion() fails to
		find colliding tower, it passes tower at elem 0 which is out of bounds*/
	}

}

void GameState::otherPlayerMechs()
{
	/*
		Other player mechanics to call include shield and 
		managing follower area behavior 
	*/

	//Grow follow area
	players.at(0).growLargeFollowArea(sf::Mouse::isButtonPressed(sf::Mouse::Right));

	//regenShield
	players.at(0).regenShield();

}

void GameState::shootingMechanics()
{
	for (size_t i = 0; i < players.size(); i++)
	{
		players.at(i).shoot(mousePos);
		players.at(i).moveBullets();
		players.at(i).checkBulletInBounds(*window_ptr);
	}
}

void GameState::followerMechanics()
{
	spawnFollowers();
	moveFollowers();

	shootFollowers();
	attackPlayer();
}

void GameState::towerMechanics()
{
	/*
		Three main objects in tower mechanics section;
			- check and update tower ownership
			- toggle towers on and off based on internal timer
			- check for laser collisions
	*/
}

bool GameState::isGameOver() {
	return players.at(0).isGameOver();
}


/* LEVEL 2  -  Followers*/
void GameState::spawnFollowers()
{
	static int temperSpawnRate = 0; temperSpawnRate++;				//moderates spawn rate
	static int tmperRate = 50;

	if ((temperSpawnRate % tmperRate == 0) && (followers.size() < maxFollowers))
	{
		Follower follower(*window_ptr, towers.at(0).getTowerRadius());
		//EXCEPTION THROWN HERE WHEN TOWERS NOT INNIT

		followers.push_back(follower);				
		//adds new follower to vector of active follower
		//std::cout << "Spawning fol, total num: " << followers.size() << std::endl;
	}
}

void GameState::moveFollowers()
{
	for (size_t i = 0; i < players.size(); i++) {

		for (auto fol_it = followers.begin(); fol_it != followers.end();)
		{
			fol_it->moveLogic(fol_it->followerCollision(followers, fol_it),
				players.at(i), towers);
			fol_it++;
			//checks follower for follower collision then moves awnd adjust velocity as necesary
			//if follower is in collision with another follower, function "bounces" them off each other
			//otherwise just moves follwer at current velocity
		}
		
	}
}

void GameState::shootFollowers()
{
	/*
		For each player, checks if each follower intersects
		any of the player's bullets calling the "shoot follower" 
		method
	*/

	for (size_t i = 0; i < players.size(); i++) 
	{
		for (auto fol_it = followers.begin(); fol_it != followers.end();)
		{
			//Determines dmg done by player to zombie
			int dmg = players.at(i).shootFollower(
				fol_it->getFollowerGlobalBounds());

			if (dmg > 0)
			{
				if (fol_it->takeDamage(dmg) <= 0) {
					fol_it = followers.erase(fol_it);
					//returns next iterator
				}
				else
					++fol_it;
			}
			else
				++fol_it;
		}

		//return array of followers shot by this player
		//aggregate all dead followers into 1 array by arr1 || arr2

	}
}

void GameState::attackPlayer()
{
	for (size_t i = 0; i < players.size(); i++)
	{
		for (auto& fol : followers)
		{
			if (fol.getFollowerGlobalBounds().intersects(
				players.at(i).getHeartBounds())) {	
				//if a follwer insects the player's global bounds

				int dmg = fol.getDamage();
				players.at(i).takeDamage(dmg);	
				//reduce player's health
			}
		}
	}
}


/*LEVEL 2  -  Tower Collisions */
int GameState::checkTowerCollision()
{
	int collidingTower = 0;		//tower num (1-4) of colliding tower, or 0 for none
	//We can make this better, only check for collision if close to tower

	for (size_t i = 0; i < players.size(); i++)
	{
		for (size_t j = 0; j < towers.size(); j++)
		{
			if (towers[j].checkTowerCollision(players.at(i))) {
				collidingTower = j;
			}

		}
	}

	return collidingTower;
}


/* LEVEL 3  -  Draw Functions*/
void GameState::drawPlayers()
{
	for (size_t i = 0; i < players.size(); i++)
	{
		players.at(i).drawPlayer(*window_ptr);
	}
}

void GameState::drawFollowers()
{
	for (auto& fol : followers) {
		fol.drawFollower(*window_ptr);
	}
}

void GameState::drawTowers()
{
	for (size_t i = 0; i < towers.size(); i++) {
		towers.at(i).drawTowers(*window_ptr);
	}
}


	/*  Other Private Functions  */
void GameState::reset()
{

}

void GameState::updateDt()
{
	/*  
		Update our "delta t" value that keeps
		relative number of frames straight.
	*/


}


	/*  Modifiers  */
void GameState::setMousePos(sf::Vector2i &mPos) {
	mousePos = mPos;
}


	/*  Other Public Functions  */	

void GameState::quitState()
{

}

STATE GameState::update(sf::Vector2i &mPos, const float& dt)
{
	/*
		Update Function calls all game update 
		functions for game components
		- Players
		- Followers
		- Towers
	*/
	setMousePos(mPos);
	movePlayerLogic();
	otherPlayerMechs();
	shootingMechanics();
	followerMechanics();

	std::string msg = "Size of objs: ";
	msg += std::to_string(objs.size());

	static int i = 0;
	zsk::print(msg, i);


	if (!isGameOver()) {
		return GAME;
	}

	return MAIN_MENU;
}

void GameState::render(sf::RenderTarget* rt)
{
	/*
		Render Function calls draw functions for all
		game components
		- Players
		- Followers
		- Towers
	*/

	drawPlayers();
	drawFollowers();
	drawTowers();
}


	/*  Destructors  */

GameState::~GameState()
{
}
