//Implementation file for GameState.h

#include "gameState.h"

/*  CNTRL + M + O to collapse all */

/*  Initializing static variables  */
int GameState::maxFollowers = 1;

int GameState::numPlayers = 0;
int GameState::maxPlayers_this = 0;


	/*  Constructors  */

GameState::GameState()
	: State()
{
	gameState = STATE::GAME;

	//Set window and mouse for game objects
	GameObj::setWindow(window_ptr);

	initVars();
	addPlayer();
	//players.emplace_back(*w_ptr);
	//Need to figure out how im going to add players

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
	GameObj::setWindow(window_ptr);

	//set number of towers and reserve vector space
	numberOfTowers = std::max(maxPlayers_this, 4);
	towers.reserve(zsk::smallContSz);
	players.reserve(zsk::smallContSz);

	//set ptr to objs in GameObjs class
	GameObj::setObjs(std::shared_ptr<std::list<GameObj*>>(&objs));		
}


//Game Update Functions


/*  Collission functions  */
void GameState::checkCollisions()
{
	/*
		Outer level "check collisions" function initiates
		recursive function call on binSep and calls 
		determine collisions function
	*/

	std::vector<std::list<GameObj*>*> quads;
	sf::FloatRect area(sf::Vector2f(0.0,0.0), 
		sf::Vector2f(window_ptr->getSize()));
	int numQuads = 4;

	//seperate objs into 16 quadrants for collision detection
	binSep(&objs, quads, area, numQuads);

	//determine collisions
	determineCollisions(quads);

	//delete allocated data in quads

	deleteBins(quads);

}
//END


void GameState::binSep(const std::list<GameObj*>* actObjs, 
	std::vector<std::list<GameObj*>*>& quads, sf::FloatRect side, int lvl)
{
	/*
		Seperate each level of objs unordered map into 
		2 "quadrants" repeatedly until lvl = 0;
	*/

	//create actObjs2 - vector of GameObj*'s NOT in float rect area
	std::list<GameObj*>* actObjs1 = new std::list<GameObj*>();
	std::list<GameObj*>* actObjs2 = new std::list<GameObj*>();

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
	for (const auto& obj : *actObjs) 
	{
		if (side.contains(obj->getPos())) 
			actObjs1->push_back(obj);
		else
			actObjs2->push_back(obj);
	}

	//Call binSep recursively OR push vect onto quads
	if (lvl > 0) {
		binSep(actObjs1, quads, side, --lvl);
		binSep(actObjs2, quads, otherSide, --lvl);
	}
	else {
		quads.push_back(actObjs1);
		quads.push_back(actObjs2);
	}

}
//END


void GameState::determineCollisions(const 
	std::vector<std::list<GameObj*>*>& quads)
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
		auto it1 = ls->begin() ;
		while (it1 != ls->end())
		{
			for (auto it2 = it1; ++it2 != ls->end();)
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

void GameState::deleteBins(std::vector<std::list<GameObj*>*>& quads)
{
	/*
		We delete memory allocated to storing lists
		of game objs belonging in quadrants.
	*/

	for (const auto& list : quads) {
		list->clear();
		delete list;
	}
}




/* LEVEL 1  -  Call From Update*/
void GameState::followerMechanics()
{
	/*
		SOLUTION
		- This can be main updaet function inside
		followers class
		- methods called will have to be accompanying
	*/
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
	if(players.at(0).isGameOver());
	gameState = STATE::MAIN_MENU;
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

	/*
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
	*/
	return 0;
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


	/*  Other Public Functions  */	

void GameState::quitState()
{
	//Removes the gamestate from the gameApp stack by
	//changing the 
}

STATE GameState::update(const float& dt)
{
	/*
		Update Function calls all game update 
		functions for game components
		- Players
		- Followers
		- Towers
	*/

	//Determine all obj Collisions
	checkCollisions();

	//Game_Obj Update for each object
	for (auto& obj : objs) {
		obj->update();
	}

	movePlayerLogic();
	otherPlayerMechs();
	shootingMechanics();
	followerMechanics();

	std::string msg = "Size of objs: ";
	msg += std::to_string(objs.size());

	static int i = 0;
	zsk::print(msg, i);

	//check game state
	isGameOver();

	return gameState;
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
