

//Project Includes
#include "Game.h"


//Game.cpp file describes game object



/*		CLASS CONSTRUCTOR		*/

Game::Game()
{
	initVars();
	initWindow();
	initStartMenu();

	addPlayer();
	initTowers();
}

//END CONSTRUCTORS


/*		PRIVATE FUNCTIONS		*/

void Game::initTowers()
{
	//adds an additional tower out of play that assists with mechanics
	for (size_t i = 0; i < numberOfTowers + 1; i++) {
		towers.push_back(Tower(*window_ptr, i));
	}
}

void Game::initVars()
{
	//init window_ptr to nullptr
	window_ptr = nullptr;
	startMenu_ptr = nullptr;

	numPlayers = 0;
	maxPlayers = 4;
	numberOfTowers = 4;

	gameState = 0;
}

void Game::initWindow()
{
	/*
		Init sf::render window, from config file
		Initializes default vars first
	*/

	std::string title = "ZSK";
	vidMode.width = 1500.f;
	vidMode.height = 1200.f;
	int frameLimit = 60;
	bool vertical_syn_enabled = false;

	std::string skip;
	//we want to skip certain elements in
	//our config file and just get the data

	try
	{
		//Declares and opens file simultaneously
		std::string configFile = "window/config.ini";
		std::ifstream w_config(configFile);

		if (!w_config)
		{
			//Throw exception if file not open
			std::string openFileErr = "Unable to open file with name: ";
			openFileErr += configFile;
			throw file_open_error(openFileErr);
		}
		//read vars in from file 

		w_config >> skip;
		std::getline(w_config, title);

		w_config >> skip;
		w_config >> vidMode.width >> vidMode.height;

		w_config >> skip;
		w_config >> frameLimit;

		w_config >> skip;
		w_config >> vertical_syn_enabled;


		w_config.close();
	}
	//End Try Block

	catch (file_open_error &foe1) {
		std::cout << "File open error caugh in Game::initWindow : " 
			<< std::endl;

		std::cout << foe1.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown exception caught in Game::initWindow : "
			<< std::endl;
	}
	//end Catch statements 

	//create window with file or default values

	window_ptr = new sf::RenderWindow(vidMode, title);
	window_ptr->setFramerateLimit(frameLimit);
}

void Game::initStartMenu() {
	startMenu_ptr = new StartMenu(*window_ptr);
}



//Game Update functions

	/* LEVEL 1  -  Start Menu*/

void Game::runStartMenu() 
{
	//Update and animate title screen
	startMenu_ptr->update(mousePos);

	if (startMenu_ptr->getOptionSelected() == 1)
	{
		gameState = startMenu_ptr->getOptionSelected();
		delete startMenu_ptr;
		startMenu_ptr = nullptr;
	}
}

void Game::pauseMenu() 
{
	gameState = 1;
}


/* LEVEL 1  -  Call From Update*/
void Game::movePlayerLogic()
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


		//Grow follow area -- unrelated to movement but a good place to call
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			players.at(i).growLargeFollowArea();
		else
			players.at(i).setLargeFollowerRadius(players.at(i).getMinLFR());

		//regenShield
		if (players.at(i).getShield() > 0)
			players.at(i).regenShield();
	}


}

void Game::shootingMechanics()
{
	for (size_t i = 0; i < players.size(); i++)
	{
		players.at(i).shoot(mousePos);
		players.at(i).moveBullets();
		players.at(i).checkBulletInBounds(*window_ptr);
	}
}

void Game::followerMechanics()
{
	spawnFollowers();
	moveFollowers();

	shootFollowers();
	attackPlayer();
}

void Game::isGameOver()
{
	for (size_t i = 0; i < players.size(); i++)
	{
		if (players.at(i).isGameOver() == true) {
			gameState = 0;
			break;
		}
			
	}

	if (gameState == 0)
	{
		//Erase players!, err restart game ;/
		reset();
		initStartMenu();
	}

}


	/* LEVEL 2  -  Followers*/
void Game::spawnFollowers()
{
	static int temperSpawnRate = 0; temperSpawnRate++;				//moderates spawn rate
	static int maxFollowers = 10;
	static int tmperRate = 50;

	if ((temperSpawnRate % tmperRate == 0) && (activeFollowers.size() < maxFollowers))
	{
		Follower follower(*window_ptr, towers.at(0).getTowerRadius());
		//EXCEPTION THROWN HERE WHEN TOWERS NOT INNIT

		activeFollowers.push_back(follower);				//adds new follower to vector of active follower
		//std::cout << "Spawning fol, total num: " << activeFollowers.size() << std::endl;
	}
}

void Game::moveFollowers()
{
	for (size_t i = 0; i < players.size(); i++) {
		for (size_t j = 0; j < activeFollowers.size(); j++)
		{
			activeFollowers[j].moveLogic(activeFollowers[j].followerCollision(activeFollowers, j),
				players.at(i), towers);
			//checks follower for follower collision then moves and adjust velocity as necesary
			//if follower is in collision with another follower, function "bounces" them off each other
			//otherwise just moves follwer at current velocity
		}
	}
}

void Game::shootFollowers()
{
	std::vector<bool> erasefollower;
	for (size_t i = 0; i < players.size(); i++) {
		for (size_t j = 0; j < activeFollowers.size(); j++)
		{
			int dmg = players.at(i).shootFollower(
				activeFollowers.at(j).getFollowerGlobalBounds());

			//activeFollowers.takeDamage(dmg);

			if (dmg > 0) {
				activeFollowers.erase(activeFollowers.begin() + j);
				j--;
			}
		}

		//return array of followers shot by this player
		//aggregate all dead followers into 1 array by arr1 || arr2

	}
}

void Game::attackPlayer()
{
	for (size_t i = 0; i < players.size(); i++)
	{
		for (size_t j = 0; j < activeFollowers.size(); j++)
		{
			if (activeFollowers[j].getFollowerGlobalBounds().intersects(
				players.at(i).getHeartBounds())) {	//if a follwer insects the player's global bounds

				int dmg = 1;					//later dmg = given followers damage
				players.at(i).takeDamage(dmg);	//reduce player's health
			}
		}
	}
}


	/*LEVEL 2  -  Towers*/
int Game::checkTowerCollision()
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
void Game::drawPlayers()
{
	for (size_t i = 0; i < players.size(); i++)
	{
		players.at(i).drawPlayer(*window_ptr);
	}
}

void Game::drawFollowers()
{
	for (size_t i = 0; i < activeFollowers.size(); i++) {
		activeFollowers.at(i).drawFollower(*window_ptr);
	}
}

void Game::drawTowers()
{
	for (size_t i = 0; i < towers.size(); i++) {
		towers.at(i).drawTowers(*window_ptr);
	}
}

void Game::drawStartMenu() {
	startMenu_ptr->drawMenu(*window_ptr);
}

void Game::drawPauseMenu()
{
}

void Game::reset()
{
	/*
		resets player, follower and tower vectors,
		by clearing all vector elements and reinitializing
	*/

	players.clear();
	activeFollowers.clear();
	towers.clear();

	initStartMenu();
	initTowers();
	addPlayer();
}

void Game::updateDt()
{
	/*
		Updates dt float with seconds required to
		update single frame of data in game
	*/

	dt = dtClock.restart().asSeconds();
}


//END PRIVATE FUNCTIONS


/*		PUBLIC FUNCTIONS		*/

//ACCESSORS
const bool Game::windowIsOpen() const {
	return window_ptr->isOpen();
}




//GAME UPDATES
void Game::pollEvents()
{

	while (window_ptr->pollEvent(event))
	{
		switch (event.type)
		{

		case sf::Event::Closed:
			window_ptr->close();
			break;

		case sf::Event::KeyPressed:

			if (event.key.code == sf::Keyboard::Escape) {
				window_ptr->close();
			}
			break;
		}

	}
	//End window.pollEvent

}

void Game::updateMousePosition() {
	mousePos = sf::Mouse::getPosition(*window_ptr);
}

void Game::addPlayer()
{
	if (numPlayers < maxPlayers)
	{
		numPlayers += 1;

		Player player(*window_ptr, numPlayers);
		players.push_back(player);
		//calling copy constructor here to store
		//in vector, beware of ptrs in player class

		players.at(0).setLives(0);
	}

}

void Game::update()
{
	updateMousePosition();
	pollEvents();
	updateDt();

	switch (gameState)
	{
	case 0:
		runStartMenu();
		break;

	case 1:
		movePlayerLogic();
		shootingMechanics();
		followerMechanics();
		isGameOver();
		break;

	case 2:
		pauseMenu();
		break;

	case 3:
		window_ptr->close();
		break;
	}
}


//RENDER COMPONENTS
void Game::render()
{
	window_ptr->clear(sf::Color::White);

	switch (gameState)
	{
	case 0:
		drawStartMenu();
		break;

	case 1:
		drawPlayers();
		drawFollowers();
		drawTowers();
		break;

	case 2:
		drawPauseMenu();
		break;
	}

	window_ptr->display();

}


//END PUBLIC FUNCTIONS


/*	CLASS DESTRUCTOR	*/
Game::~Game() {
	delete window_ptr;
	window_ptr = nullptr;

	if (!(startMenu_ptr == nullptr)) {
		delete startMenu_ptr;
		startMenu_ptr = nullptr;
	}
}

//END DESTRUCTOR
