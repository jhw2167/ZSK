//Explicit header file for defining shape of a given follower
//inclluded by Player.h and Follower.h
#pragma once

//Precompiled header
#include "../../../BaseCode/pch/stdafx.h"

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

	/*	Constructor	*/
	FollowerShape(sf::Color color = sf::Color::Black, float scale = 2.5f);


		/*	Setter Methods	*/
	void setSize(float scale);

	void setColor(sf::Color color);

	void setPosition(sf::Vector2f newPos);
	//***END SETTER METHODS***



		/*	Accessor Methods	*/
	float getSize();

	sf::Color getColor();

	sf::Vector2f getPosition();
		
	const sf::FloatRect& getGlobalBounds();

	//bounds with respect to center of follower head at fPos
	float getLeftBounds();

	float getUpperBounds();

	float getRightBounds();

	float getLowerBounds();

	float getHeadRadius();

	//***END GETTER METHODS***

	//other Methods
	void move(sf::Vector2f moveVect);

	void draw(const std::shared_ptr<sf::RenderWindow>& window_ptr);
};



