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

#include "PlayerObject.h"

class Tower {

private:
	float towerRadius;						//towers will be circleShapes in each of the four coners of the map
	int towerNumber;						//labels towers, 0, 1, 2, 3 

	enum towerOwned {NOTOWNED, PLAYER1, PLAYER2, PLAYER3, PLAYER4};
	towerOwned towerOwnedBy;
	
	sf::Vector2f towerPosition;

	sf::CircleShape tower;
	sf::Sprite laser1;						//Laser will be comprised of a series of drawn sprites
	sf::RectangleShape laser;

public:

	Tower(float tRadius = 100.f, int tNumber = 0)			//Constructs minimal tower objcet
	{
		towerRadius = tRadius;
		towerNumber = tNumber;

		tower.setRadius(towerRadius);
		tower.setFillColor(sf::Color::Black);
		tower.setOrigin(tower.getRadius(), tower.getRadius());
		tower.setPosition(0, 0);
		towerPosition = tower.getPosition();

		//laser.setSize()

		towerOwnedBy = NOTOWNED;

	}


	//TOWER SET METHODS
	void setPosition(sf::RenderWindow &window, int tNumber)		//sets tower position to one of the four corners
	{
		towerNumber = tNumber;									//tower's number denotation determines its position

		switch (towerNumber) {
		case 1:
			tower.setPosition(0, 0);
			break;
		case 2:
			tower.setPosition(window.getSize().x, 0);
			break;
		case 3:
			tower.setPosition(0, window.getSize().y);
			break;
		case 4:
			tower.setPosition(window.getSize().x, window.getSize().y);
			break;
		case 0:														//case zero tower not intented to be shown or utilized, 
			tower.setPosition(-100.f, -100.f);												//its instantiation helps with mechanics such as checking tower collisions
			break;
		}

		towerPosition = tower.getPosition();						//sets towerPosition var equal to placement of circle shape for easy access
	}


	//TOWER GET METHODS
	sf::Vector2f getTowerGlobalBounds()
	{
		tower.getGlobalBounds();
	}

	sf::Vector2f getPosition()
	{
		return towerPosition;
	}

	float getTowerRadius()
	{
		return towerRadius;
	}

	//TOWER OWNERSHIP METHODS
	bool checkTowerOwnership(sf::Vector2i mousePos, towerOwned i)
	{
		if (tower.getGlobalBounds().contains(mousePos.x, mousePos.y));
		towerOwnedBy = i;

		return towerOwnedBy;				//will return either 0 for unowned or >0 integer that equates to true boolean
	}

	int getTowerOwnership()
	{
		return towerOwnedBy;
	}



	//TOWER COLLISIONS
	bool checkTowerCollision(sf::Vector2f playerPos)
	{
		if (distanceFrom(playerPos) <= towerRadius)
			return true;

		return false;
	}

	float distanceFrom(sf::Vector2f objectPos)											//calculates vector distance from player or tower object
	{
		float xDist = abs(objectPos.x - towerPosition.x);			//calculates x and y distances away follower is from player
		float yDist = abs(objectPos.y - towerPosition.y);

		return pow(xDist * xDist + yDist * yDist, 0.5);							//calculates vector for distance from follower to player
	}



	//TOWER MECHANICS


	//ACTIVATING LASER






	//TOWER DRAW METHODS
	void drawTowers(sf::RenderWindow &window)
	{
		window.draw(tower);
	}

};
