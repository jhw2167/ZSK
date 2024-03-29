//manages bullet object that is created when player shoots
#pragma once

//Precompiled header
#include "../../../BaseCode/pch/stdafx.h"

//General functions
#include "../Other/functions.h"

//Game object
#include "../GameObj.h"

class Bullet :
	public GameObj 
{

private:

	sf::RectangleShape bBody;
	sf::CircleShape bTop;

	sf::Vector2f velocity;		//bullets speed and direction
	int strip;					//how many zoms layers bullet strips
	int pen;			//How many zoms bullet punches through

	/*  Private Functions  */
	void orient();


public:

	/*	BULLET CONSTRUCTOR	*/
	Bullet(const sf::Vector2f& startPos = sf::Vector2f(0, 0), const int bStrip = 1,
		const int bPen = 1, const float scale = 4.f, const float speed = 10.f,
		const sf::Color& color = sf::Color::Black);
	//Bullet constructor initializes size, shape and position 
	//of bullet object
	

	/*  Initialize Functions  */
	void initBullet(const float scale,
		const int bStrip, const int bPen, const sf::Color& bColor);


	/*	BULLET SET FUNCTIONS	*/
	void setBulletPosition(const sf::Vector2f& newPos);
	//setPosition function

	void setBulletVelocity(const sf::Vector2f& playerPos, const float speed = 10.f);
		//moves bullet by adding unit vector to bullet shapes move function

	void setStrip(const int bStrip);

	void setPen(const int bPen);


	/*	BULLET ACCESSOR FUNCTIONS	*/
	sf::Vector2f getBulletPosition() const;
	//get bullets position function used for collisions 

	const sf::FloatRect getGlobalBounds() const;
	//taken as global bounds of of bullets circlceShape top
	
	int getStrip() const;

	int getPen() const;


	/*	OTHER PUBLIC FUNCTIONS	*/
	void moveBullet();

	bool isOutOBounds();

	/*		UPDATE		*/
	STATE update();
	/***************/


	//DRAW FUNCTIONS
	void drawBullet();


	//copy constructor
	Bullet(const Bullet& rhs);

	//destructor (not implemented)

};