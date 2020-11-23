

//Project Includes
#include "Game.h"


//Game.cpp file describes game object

const short Game::maxPlayers = 4;

/*		CLASS CONSTRUCTOR		*/
Game::Game()
{
	initVars();
	initWindow();
	initStartMenu();

	GameState::setNumPlayerVars(maxPlayers);
}



	/*  Init Functions  */

void Game::initVars()
{
	//init window_ptr to nullptr
	window_ptr = nullptr;
	gameState = MAIN_MENU;
	numPlayers = 0;

	//load game art and objects
	zsk::art::loadFonts();
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

	//Declares and opens file simultaneously
	std::string configFile = "Game/window/config.ini";
	std::ifstream w_config(configFile);

	try
	{
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
		frameLimit = 60;

		w_config >> skip;
		w_config >> vertical_syn_enabled;


		w_config.close();
	}
	//End Try Block

	catch (file_open_error &foe1) {
		std::cout << "File open error caugh in Game::initWindow : " 
			<< std::endl;

		std::cout << foe1.what() << std::endl;
		w_config.close();
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
	MenuState* mm = new MenuState(window_ptr, &events);
	states.push(mm);
}



	/*  Game Update Functions  */
void Game::updateGameState(STATE gs)
{
	if (gs != gameState)
	{
		//cout << "gs is: " << gs << endl;

		switch (gs)
		{
		case MAIN_MENU:
			//Create new MenuState and add
			//it to the stack
			updateState<MenuState>(true);
			break;

		case LOBBY:
			updateState<LobbyState>(true);
			break;

		case HOST_LOBBY:
			//subcase of lobby, no state update
			gs = LOBBY;
			break;

		case JOIN_LOBBY:
			//subcase of lobby, no state update
			gs = LOBBY;
			break;

		case GAME:
			//Create new gameState and add
			//it to the stack
			updateState<GameState>(true);
			break;

		case PAUSE:
			//Create new pauseState, overlay it
			//onto the stack
			break;

		case QUIT:
			window_ptr->close();
			break;

		default:
			//do nothing
			//maybe for alternative lobby states, set gs = LOBBY
			break;
		}
		gameState = gs;
	}

}

void Game::isGameOver() {
	/*
		Will set gamestate = 0, reset all
		game entities, and direct player
		back to main menu, by pushing it 
		onto the stack.
	*/

	cout << "here" << endl;

	//gameState = 0;
}

void Game::updateDt()
{
	/*
		Updates dt float with seconds required to
		update single frame of data in game
	*/

	dt = dtClock.restart().asSeconds();
}


/*		PUBLIC FUNCTIONS		*/


	/*  Accessors  */
const bool Game::windowIsOpen() const {
	return window_ptr->isOpen();
}


	/*  Game Update Functions  */
void Game::pollEvents()
{
	//clear vector of events so new events set
	events.clear();

	while (window_ptr->pollEvent(event))
	{
		//poll for events

		switch (event.type)
		{

		case sf::Event::Closed:
			window_ptr->close();
			break;

		case sf::Event::KeyReleased:

			if (event.key.code == sf::Keyboard::Escape) {
				updateGameState(PAUSE);
			}
			break;
		}

		events.push_back(event);
	}
	//End window.pollEvent

}

void Game::updateMousePosition() {
	mousePos = sf::Mouse::getPosition(*window_ptr);
}

void Game::addPlayer() {
	GameState::addPlayer();
}

void Game::update()
{
	/* 
		Primary game update thread, if the states
		stack is NOT empty, update the top
	*/

	updateMousePosition();
	pollEvents();
	updateDt();

	STATE gs = MAIN_MENU;
	if (!states.empty())
		gs = states.top()->update(mousePos, dt);
	else
		gs = QUIT;
		//gameState quit;

	static int c = 0;
	if (c > 200)
	{
		//std::cout << "gs in game::update: " << gs << std::endl;
		c = 0;
	}
	c++;

	//cout << "Calling Game::update with gs = "<< gs << endl;

	updateGameState(gs);
}


	/*  Game Render  */
void Game::render()
{
	/*
		Clears, renders and displays the game, if there is a
		state in the stack
	*/

	window_ptr->clear(zsk::art::winClearColor);

	if (!states.empty())
		states.top()->render();

	window_ptr->display();
}



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
