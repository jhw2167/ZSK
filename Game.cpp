#include "Game.h"


//Private game functions

void Game::initVars()
{
	//init window_ptr to nullptr
	this->window_ptr = nullptr;

}

void Game::initWindow()
{

	this->vidMode.width = 1500.f;
	this->vidMode.height = 1200.f;

	this->window_ptr = new sf::RenderWindow(this->vidMode, "Zombie Slayer Killer");
	window_ptr->setFramerateLimit(60);


}

Game::Game()
{
	this->initVars();
	this->initWindow();
}


Game::~Game()
{
	delete this->window_ptr;
}

//Update game logic
void Game::update()
{
	
}

//Draws all game components
void Game::render()
{


}
