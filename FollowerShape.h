//Explicit header file for defining shape of a given follower
//inclluded by Player.h and Follower.h

#pragma once

//SFML Includes
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

//Std Lib includes
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
#include <random>
#include <cstdlib>

//Project includes
#include "TowerObject.h"


#ifndef FollowerShape

//Start with FollowerShape class
class FollowerShape
{
private:

	sf::CircleShape head;			//shape vars for followers set up in constructor
	sf::CircleShape shield;
	sf::RectangleShape leg1;
	sf::RectangleShape leg2;

	float headRadius;				//size variables scaled by "fSize"							
	float shieldRadius;				// in setSize
	float legLength;
	float legWidth;
	float legAngle;

	float fSize;				//scales up follow size
	sf::Color fColor;
	sf::Vector2f fPos;

public:

	FollowerShape(sf::Color color = sf::Color::Black, float scale = 2.5f)
	{
		//setUp follower Shape and size
		legAngle = 35;
		setSize(scale);
		//set follower color
		setColor(color);
	}

	//setter methods
	void setSize(float scale)
	{
		headRadius = scale * 5.f;
		legLength = scale * 10.f;
		legWidth = scale * 2.f;

		head.setRadius(headRadius);
		head.setOrigin(head.getRadius(), head.getRadius());
		//origin at center of head

		leg1.setSize(sf::Vector2f(legWidth, legLength));
		leg1.setOrigin(sf::Vector2f(legWidth / 2.f, 0));
		leg1.setRotation(legAngle);
		//Origin at center, left side of leg

		leg2.setSize(sf::Vector2f(legWidth, legLength));
		leg2.setOrigin(sf::Vector2f(legWidth / 2.f, 0));
		leg2.setRotation(360 - legAngle);
		//Origin at center, left side of leg

		fSize = scale;
	}

	void setColor(sf::Color color)
	{
		head.setFillColor(color);
		leg1.setFillColor(color);
		leg2.setFillColor(color);

		fColor = color;
	}

	void setPosition(sf::Vector2f newPos)
	{
		head.setPosition(newPos);
		leg1.setPosition(newPos);
		leg2.setPosition(newPos);

		fPos = newPos;
	}
	//***END SETTER METHODS***



	//getter methods
	float getSize() {
		return fSize;
	}

	sf::Color getColor() {
		return fColor;
	}

	sf::Vector2f getPosition() {
		return fPos;
	}

	sf::FloatRect getGlobalBounds()
		//taken as global bounds of follower's circleShape head
	{
		return head.getGlobalBounds();
	}

	//bounds with respect to center of follower head at fPos
	float getLeftBounds()
	{
		return fPos.x - headRadius;
	}

	float getUpperBounds()
	{
		return fPos.y - headRadius;
	}

	float getRightBounds()
	{
		return fPos.x + headRadius;
	}

	float getLowerBounds()
	{
		float degsToRads = 3.14159 / 180;
		float dist = 2 * headRadius * cos(legAngle * degsToRads);
		return fPos.y + dist;
	}

	float getHeadRadius() {
		return headRadius;
	}

	//***END GETTER METHODS***

	//other Methods
	void move(sf::Vector2f moveVect)
	{
		head.move(moveVect);
		leg1.move(moveVect);
		leg2.move(moveVect);

		fPos += moveVect;
	}

	void draw(sf::RenderWindow &window)
	{
		window.draw(head);
		window.draw(leg1);
		window.draw(leg2);
	}
};


#endif // !FollowerShape

