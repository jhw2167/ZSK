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
		if (side.contains(obj->getPos())) {
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
		- We determine if 2 given objs within a given
		quad (vector of Obj vectors) intersect
		- If so, we push the obj ptr onto the collisions vector
		- Collisions is vector<GameObj*> class variable of obj 
	*/

	for (const auto& ls : quads)
	{
		//get iterator from list
		auto it1 = ls.begin() ;
		while (it1 != ls.end())
		{
			for (auto it2 = it1; ++it2 != ls.end();)
			{
				GameObj* obj1 = it1._Ptr->_Myval;
				GameObj* obj2 = it2._Ptr->_Myval;
				if (obj1->getGlobalBounds().intersects(
					obj2->getGlobalBounds())) 
				{
					//compare all objects to each other
					obj1->collisions.push_back(obj2);
					obj2->collisions.push_back(obj1);
				}
			}
			//End OBJ FOR
			++it1;
		}
		//END LST FOR
	}
	//END vector for
}



/* LEVEL 1  -  Call From Update*/
void GameState::movePlayerLogic()
{
	/*
		SOLUTION:
		- move entire method into player class
		- call player::update from gamestate::update and then
		make this function call inside it
		- check tower collision may be handled by scanning
		player::collisions for a tower collision and getting
		that tower num
		- "move logic" will have to be called internally in player
		- for loop will be abandoned
	*/

	//towerNum is initialized to element number  of tower player is colliding with
	int towerNum = checkTowerCollision();
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
		SOLUTUON
		- just move these methods to player::update function
	*/

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
	/*
		SOLUTION
		- move into player class
		- get rid of for loop
		- mousePos should be a static variable in objs class
		- window ptr should also be static objs var
		- update these two items in each gs::update function call
	*/

	for (size_t i = 0; i < players.size(); i++)
	{
		players.at(i).shoot(mousePos);
		players.at(i).moveBullets();
		players.at(i).checkBulletInBounds(*window_ptr);
	}
}

void GameState::followerMechanics()
{
	/*
		SOLUTION
		- This can be main updaet function inside
		followers class
		- methods called will have to be accompanying
	*/

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
	
	//Leave this for now, will consider what to do here

	return players.at(0).isGameOver();
}


/* LEVEL 2  -  Followers*/
void GameState::spawnFollowers()
{
	/*
		SOLUTION
		- move into follower class
		- perhaps Follower class will have a static
		ptr to follower List in order to load folls
		from inside the class
		- Vars may become static vars of the class 
	*/

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
	/*
		SOLUTION
		- for loop will be moved to gs::update function so
		all follower->update methods will be called independently
		- remove outer for loop for players
		- move logic will be called internally
		- utilize collisions vector shared by all objects
		- major redesigning necessary for follower->moveLogic
	*/

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
		SOLUTION
		- general object collisions method will hand collisions
		- follower->takeDamage method will have to be called from
		player class, somehow
		- It would be wise to double commit on the collisions
		vector so each object knows precisely what its colliding
		into
		- follower->tk Damage will be called automatically
		from follower class if it intersects a bullet
		- We must be cautious of disconnect and double counting here -
		part of this work will be done in player class (score counting)
		and part will be done in follower movement (pen, strip, deletion)
	
	*/

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
				fol_it->getGlobalBounds());

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
	/*
		SOLUTION
		- We have collision information from the general case again
		- It may be best for player just to take his own 
		damage here 
		- However, we may also want to do something to a folower
		knowing that it has just dealt damage so I should touch
		on this in the fol class even if nothing is done yet

	*/

	for (size_t i = 0; i < players.size(); i++)
	{
		for (auto& fol : followers)
		{
			if (fol.getGlobalBounds().intersects(
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
	/*
		SOLUTION
		- collisions are handled by general case
		- This method is only relevant to players and 
		player move logic, will be handled accordingly

	*/

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
	for (size_t i = 0; i < players.size(); i++) {
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
	//Removes the gamestate from the gameApp stack by
	//changing the 
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
