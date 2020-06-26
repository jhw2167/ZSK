#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <math.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <fstream>
#include <iomanip>
#include <string>
#include <array>
#include <algorithm>
#include <ctime>
#include <vector>
#include <cstdlib>

#include "Player.h"

class Tower {

private:
	float towerRadius;						//towers will be circleShapes in each of the four coners of the map
	int towerNumber;						//labels towers, 0, 1, 2, 3 

	enum towerOwned {NOTOWNED, PLAYER1, PLAYER2, PLAYER3, PLAYER4};
	towerOwned towerOwnedBy;
	
	sf::Vector2f towerPosition;

	sf::CircleShape towerShape;
	sf::Sprite laser1;						
	//Laser will be comprised of a series of drawn sprites

	sf::RectangleShape laser;

public:
	
		/*  Constructors */
	Tower(sf::RenderWindow &window, int tNumber = 0, float tRadius = 200.f);

	Tower(int tNumber = 0, float tRadius = 200.f);


		/*  Init Methods  */
	void initTowerShape(float tRadius);



		/*  Setter methods  */
	void setPosition(sf::RenderWindow &window, int tNumber);


		/*  Accessor Methods  */
	sf::FloatRect getTowerGlobalBounds();

	sf::Vector2f getPosition();

	float getTowerRadius();

	sf::CircleShape getTowerShape();

	//TOWER OWNERSHIP METHODS
	bool isTowerOwned(sf::Vector2i mousePos, towerOwned i);

	int getTowerOwnership();
	
	/*  Functions  */

	//TOWER COLLISIONS
	bool checkTowerCollision(Player &player);

	//if (distanceFrom(playerPos) <= towerRadius)
		//return true;

	float distanceFrom(sf::Vector2f objectPos);



	//TOWER MECHANICS


	//ACTIVATING LASER






	//TOWER DRAW METHODS
	void drawTowers(sf::RenderWindow &window);

};
