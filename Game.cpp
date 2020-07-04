

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
}

//END CONSTRUCTORS


/*		PRIVATE FUNCTIONS		*/

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
			std::string openFileErr = "Unable to open config file with name: ";
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
	//End catch: establish window with default values

	try
	{
		//create window with file or default values
		window_ptr = new sf::RenderWindow(vidMode, title);
		window_ptr->setFramerateLimit(frameLimit);
	}

	catch (std::bad_alloc &ba1) {
		std::cout << "bad_alloc error caught in Game::initWindow : "
			<< std::endl;

		std::cout << ba1.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown exception caught in Game::initWindow : "
			<< std::endl;
	}
	//end Catch statements 

}

void Game::initStartMenu() {
	startMenu_ptr = new StartMenu(*window_ptr);
}


//Game Update functions

	/*  Start Menu  */

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


/*  Draw Functions  */

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
