//Implementation file for GameState.h

#include "gameState.h"

/*  CNTRL + M + O to collapse all */

/*  Initializing static variables  */
int GameState::maxFollowers = 5;

int GameState::numPlayers = 0;
int GameState::maxPlayers_this = 0;


	/*  Constructors  */

GameState::GameState(sf::RenderWindow* w_ptr, std::vector<sf::Event>* evs) : State(w_ptr, evs)
{
	players.push_back(Player(*w_ptr));
	initVars();
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
		towers.push_back(Tower(*window_ptr, i));
	}
}

void GameState::initVars()
{
	/*
		Initiate fundamental non-static vars
	*/

	numberOfTowers = std::max(maxPlayers_this, 4);
}

//Game Update Functions

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

	for (size_t i = 0; i < players.size(); i++) {
		for (auto fol_it = followers.begin(); fol_it != followers.end();)
		{

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


/*LEVEL 2  -  Towers*/
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

short GameState::update(sf::Vector2i &mPos, const float& dt)
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
