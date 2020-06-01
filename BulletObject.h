//manages bullet object that is created when player shoots

//SFML includes
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

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


class Bullet {

private:

	sf::RectangleShape bBody;
	sf::CircleShape bTop;

	sf::Vector2f velocity;		//bullets speed and direction
	int strips;					//how many zoms layers bullet strips
	int penetrates;			//How many zoms bullet punches through


public:

	Bullet(sf::Vector2f startPos = sf::Vector2f(0.f, 0.f),
		sf::Vector2i cursorPos = sf::Vector2i(50.f, 50.f), int bStrip = 1,
		int bPen = 1, float scale = 2.f )
	//Bullet constructor initializes size, shape and position 
	//of bullet object
	{
		float bulletLength = scale * 2.f;
		float bulletHeight = scale;

		bBody.setSize(sf::Vector2f(bulletLength, bulletHeight));
		bBody.setFillColor(sf::Color::Black);
		bBody.setOrigin(bulletLength, bulletHeight / 2.f);				//origin of bullet set at bullet top so circleShape "bTop" can be set to same position
		bBody.setPosition(startPos);									//and they will be overlapping

		bTop.setRadius(scale / 2.f);
		bTop.setFillColor(sf::Color::Black);
		bTop.setOrigin(bTop.getRadius(), bTop.getRadius());
		bTop.setPosition(startPos);

		setBulletVelocity(startPos, cursorPos);

		strips = bStrip;			//by default bullets strip 1 layer (strips=1) and delete
		penetrates = bPen;			// after colliding with 1 zombie (pen = 1)
	}

	void setBulletPosition(sf::Vector2f newPos)				//setPosition function
	{
		bBody.setPosition(newPos);
		bTop.setPosition(newPos);
	}

	sf::Vector2f getBulletPosition()						//get bullets position function used for collisions 
	{
		return bTop.getPosition();
	}

	sf::FloatRect getBulletGlobalBounds()		//taken as global bounds of of bullets circlceShape top
	{
		return bTop.getGlobalBounds();
	}

	void setBulletVelocity(sf::Vector2f playerPos, sf::Vector2i cursorPos, float speed = 10.f)		//moves bullet by adding unit vector to bullet shapes move function
	{
		float yCoord = cursorPos.y - playerPos.y;				

		float xCoord = cursorPos.x - playerPos.x;

		float mag = sqrt(pow(xCoord, 2) + pow(yCoord, 2));

		bBody.rotate(std::tan(static_cast<double>(yCoord / xCoord)));

		velocity = sf::Vector2f((xCoord / mag) * speed, (yCoord / mag) * speed);		
		//creates bullet velocity vector as function of direction vector and speed												
	}

	void moveBullet()
	{
		bBody.move(velocity);
		bTop.move(velocity);
	}

	bool isOutOBounds(sf::RenderWindow &window)
	{
		float xPos = bTop.getPosition().x;
		float yPos = bTop.getPosition().y;

		bool isOut = false;

		if (xPos > window.getSize().x|| xPos < 0)
		{
			isOut = true;
		}
			
		else if (yPos > window.getSize().y || yPos < 0)
		{
			isOut = true;
		}

		return isOut;
	}


	void drawBullet(sf::RenderWindow &window)
	{
		window.draw(bBody);
		window.draw(bTop);
	}

};
