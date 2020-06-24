#pragma once
//Ensures game engine defined only once

/*
	Zombie Slayer Killer (ZSK) development code, main.h file
	ZSK is a third person, 2D simplistic shooter/follower arcade game
	with a bit of a twist adding the tower dynamic to assist zombie slaying
*/

/*
	Visual Studious Visual C++ 2017 version 15.9.5
	SMFL for Visual C++ 15, version 2.5.1 for 32 bit OS
	Last updated *6/24/2020*
*/
  

//Game engine/wrapper stored collectively in game class

//SFML includes
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

//Std lib includes
#include <iostream>
#include <cmath>
#include <math.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <array>
#include <algorithm>
#include <ctime>
#include <vector>
#include <cstdlib>

//Project includes
#include "FollowerObject.h"
#include "coutTests.h"

class Game
{
private:
	//Variables

	//Window
	sf::RenderWindow *window_ptr;
	sf::VideoMode vidMode;
	sf::Event event;


	//Private functions
	void initVars();
	void initWindow();


public:

	//Constructors / Destructors
	Game();
	virtual ~Game();


	//Functions
	void update();
	void render();
};

