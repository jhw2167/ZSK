

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


	/*  Init Functions  */

void Game::initVars()
{
	//init window_ptr to nullptr
	window_ptr = nullptr;
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
	MenuState* mm = new MenuState(window_ptr);
	states.push(mm);
}


	/*  Game Update Functions  */

void Game::isGameOver() {
	/*
		Will set gamestate = 0, reset all
		game entities, and direct player
		back to main menu, by pushing it 
		onto the stack.
	*/

	gameState = 0;
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
	/*
	if (numPlayers < maxPlayers)
	{
		numPlayers += 1;

		Player player(*window_ptr, numPlayers);
		players.push_back(player);
		//calling copy constructor here to store
		//in vector, beware of ptrs in player class

		players.at(0).setLives(0);
	}
	*/
	

}

void Game::update()
{
	updateMousePosition();
	pollEvents();
	updateDt();

	states.top()->update(mousePos);
}


//RENDER COMPONENTS
void Game::render()
{
	window_ptr->clear(sf::Color::White);
	states.top()->render();
	window_ptr->display();
}


//END PUBLIC FUNCTIONS


/*	CLASS DESTRUCTOR	*/
Game::~Game() {
	delete window_ptr;
	window_ptr = nullptr;

	while (!states.empty())
	{
		delete states.top();
		states.pop();
	}
}

//END DESTRUCTOR
