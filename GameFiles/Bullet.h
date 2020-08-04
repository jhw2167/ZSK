//manages bullet object that is created when player shoots
#pragma once

//Precompiled header
#include "../pch/stdafx.h"
#include "functions.h"

class Bullet {

private:

	sf::RectangleShape bBody;
	sf::CircleShape bTop;

	sf::Vector2f velocity;		//bullets speed and direction
	sf::Vector2f pos;
	int strip;					//how many zoms layers bullet strips
	int pen;			//How many zoms bullet punches through

	/*  Private Functions  */
	void orient(const sf::Vector2i& cursorPos);


public:

	/*	BULLET CONSTRUCTOR	*/
	Bullet(const sf::Vector2f& startPos = sf::Vector2f(0.f, 0.f),
		const sf::Vector2i& cursorPos = sf::Vector2i(50.f, 50.f), int bStrip = 1,
		int bPen = 1, float scale = 10.f);
	//Bullet constructor initializes size, shape and position 
	//of bullet object
	

	/*  Initialize Functions  */
	void initBullet(const float scale,
		const int bStrip, const int bPen);


	/*	BULLET SET FUNCTIONS	*/
	void setBulletPosition(const sf::Vector2f& newPos);
	//setPosition function

	void setBulletVelocity(const sf::Vector2f& playerPos,
		const sf::Vector2i& cursorPos, const float speed = 1.f);
		//moves bullet by adding unit vector to bullet shapes move function

	void setStrip(const int bStrip);

	void setPen(const int bPen);


	/*	BULLET ACCESSOR FUNCTIONS	*/
	sf::Vector2f getBulletPosition() const;
	//get bullets position function used for collisions 

	sf::FloatRect getBulletGlobalBounds() const;
	//taken as global bounds of of bullets circlceShape top
	
	int getStrip() const;

	int getPen() const;


	/*	OTHER PUBLIC FUNCTIONS	*/
	void moveBullet();

	bool isOutOBounds(sf::RenderWindow &window);

	//DRAW FUNCTIONS
	void drawBullet(sf::RenderWindow &window);

};

sf::Vector2f operator*(sf::Vector2f v1,  int const& a);

sf::Vector2f operator/(const sf::Vector2f v1, const sf::Vector2f v2);

sf::Vector2f abs(sf::Vector2f v1);

//Stream overloaders
std::ostream& operator<< (std::ostream &out, const sf::Vector2f v1);

std::ostream& operator<< (std::ostream &out, const sf::Vector2i v1);
