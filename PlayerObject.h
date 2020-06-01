
//header file to construct and design the player object for the game

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

#include "BulletObject.h"

class PlayerShape {
private:

	sf::CircleShape heart;										//Player position will be at the center of the heart
	sf::Vector2f heartCenterAdj;

	sf::CircleShape head;
	sf::RectangleShape body;
	sf::RectangleShape arms;
	sf::RectangleShape gun1;
	sf::RectangleShape gun2;
	sf::RectangleShape leg1;
	sf::RectangleShape leg2;

	static const int playerBodyArrSize = 6;
	sf::RectangleShape playerBody[playerBodyArrSize];				
	enum BODY {BODY, ARMS, GUN1, GUN2, LEG1, LEG2 };
	//since shapes are all rectangles, can be put into array for easy access

	float heartRadius;
	float headRadius; 

	float bodyHeight; 
	float bodyLength; 

	float armLength;
	float armHeight; 

	float gunLength; 
	float gunHeight;

	float legLength;
	float legWidth; 

	enum direction { STILL = 0, UP, LEFT, DOWN, RIGHT };							
	//declares enum direction to handle player movement

public:

	PlayerShape(float scale = 2.f, float startPos = 500.f,
		sf::Color playerColor = sf::Color::Black)										
		//Constructor for players shape, 
		//"scale" places players size relative to window
	{	
		heartRadius = scale;
		headRadius = scale * 2.f;

		bodyHeight = scale * 12.f;
		bodyLength = scale * 3.f;

		armLength = scale * 16.f;
		armHeight = scale * 2.f;

		gunLength = scale * 4.f;
		gunHeight = scale * 1.5f;

		legLength = scale * 8.f;
		legWidth = scale * 1.75f;

		heart.setRadius(scale);
		heart.setOrigin(heart.getRadius(), heart.getRadius());						//sets up player heart shape to be drawn
		heart.setFillColor(sf::Color::Red);
		heart.setPosition(startPos, startPos);

		head.setRadius(headRadius);													//sets up player head 
		head.setOrigin(head.getRadius(), head.getRadius());
		head.setFillColor(playerColor);
		head.setPosition(startPos, startPos - bodyHeight / 4.f);

		body.setSize(sf::Vector2f(bodyLength, bodyHeight));							//player body
		body.setFillColor(playerColor);
		body.setOrigin(bodyLength / 2.f, 0);
		body.setPosition(sf::Vector2f(startPos, startPos - bodyLength / 4.f));

		arms.setSize(sf::Vector2f(armLength, armHeight));							//players arms as 1 rectangle object
		arms.setFillColor(playerColor);
		arms.setOrigin(armLength / 2.f, armHeight / 2.f);
		arms.setPosition(startPos, startPos);

		gun1.setSize(sf::Vector2f(gunHeight, gunLength));							//players gun
		gun1.setFillColor(sf::Color::Blue);
		gun1.setOrigin(gunHeight / 2.f, gunLength / 2.f);
		gun1.setPosition(startPos + armLength / 2.f, startPos);

		gun2.setSize(sf::Vector2f(gunLength, gunHeight));							//players gun
		gun2.setFillColor(sf::Color::Blue);
		gun2.setOrigin(gunLength / 3.f, gunHeight / 2.f);
		gun2.setPosition(startPos + armLength / 2.f, startPos - gunLength / 2.f);
		
		leg1.setSize(sf::Vector2f(legWidth, legLength));							//players first leg
		leg1.setFillColor(playerColor);
		leg1.setOrigin(sf::Vector2f(legWidth / 2.f, 0));
		leg1.setRotation(35);
		leg1.setPosition(startPos - bodyLength / 3.f, startPos + (3.f/4.f) * bodyHeight);

		leg2.setSize(sf::Vector2f(legWidth, legLength));							//players second leg
		leg2.setFillColor(playerColor);
		leg2.setOrigin(sf::Vector2f(legWidth / 2.f, 0));
		leg2.setRotation(325);
		leg2.setPosition(startPos + bodyLength / 3.f, startPos + (3.f/4.f) * bodyHeight);

		playerBody[0] = body;					//adds each item to array to be drawn
		playerBody[1] = arms;
		playerBody[2] = gun1;
		playerBody[3] = gun2;
		playerBody[4] = leg1;
		playerBody[5] = leg2;

	}

	void drawPlayer(sf::RenderWindow &window)
	{

		for (int i = 0; i < 6; i++)
		{
			window.draw(playerBody[i]);
		}
		
		window.draw(head);
		window.draw(heart);

	}

	void setPosition(float newPosX, float newPosY)
	{
		heart.setPosition(newPosX, newPosY);

		head.setPosition(newPosX, newPosY - bodyHeight / 4);

		playerBody[BODY].setPosition(sf::Vector2f(newPosX, newPosY - bodyLength / 4.f));

		playerBody[ARMS].setPosition(newPosX, newPosY);

		playerBody[GUN1].setPosition(newPosX + armLength / 2.f, newPosY);

		playerBody[GUN2].setPosition(newPosX + armLength / 2.f, newPosY - gunLength / 2.f);

		playerBody[LEG1].setPosition(newPosX - bodyLength / 3.f, newPosY + (3.f / 4.f) * bodyHeight);

		playerBody[LEG2].setPosition(newPosX + bodyLength / 3.f, newPosY + (3.f / 4.f) * bodyHeight);

	}

	sf::Vector2f getPosition()					//Function returns players position at his heart for collisions
	{
		return heart.getPosition();
	}

	sf::Vector2f getGunPosition()						//Returns position of gun for shooting
	{
		return playerBody[GUN2].getPosition();
	}

	sf::FloatRect getHeartBounds()
	{
		return heart.getGlobalBounds();
	}

	void movePlayershape(sf::Vector2f moveVect)
	{
		for (int i = 0; i < 6; i++)
		{
			playerBody[i].move(moveVect);
		}

		head.move(moveVect);
		heart.move(moveVect);
	}

	float getUpperBounds()									//returns player's upper, lower, left and right bounds for boundry checking
	{
		return head.getPosition().y - head.getRadius();			//the head is the highest point on the character, and its position is retrieved at its center
	}

	float getLowerBounds()
	{
		return playerBody[LEG1].getPosition().y + legLength;			//players lowerBounds with respect 
	}

	float getLeftBounds()
	{
		return playerBody[ARMS].getPosition().x - armLength / 2;		//left and right bounds with respect to the players arms
	}

	float getRightBounds()
	{
		return playerBody[ARMS].getPosition().x + armLength / 2;		//left and right bounds with respect to the players arms
	}

};

//END CLASS PLAYERSHAPE








//BEGIN CLASS PLAYER

class Tower;				//forward declaration of class tower so player has access

class Player
{

private:

	int playerNumber;
	int score;
	float health;
	float maxHealth;
	float shieldSize;
	float healthBarWidth;
	sf::Vector2f playerPosition;

	sf::Vector2f healthBarPosition;		
	sf::RectangleShape healthBarRed;							//representaion of player's lost health
	sf::RectangleShape healthBarGreen;							//visual representation of player's health
	sf::RectangleShape shield;							//representaiton of player's shield (if applicable)

	sf::Text healthText;
	sf::Font arial;								//Declares font to use for text drawing

	enum direction {STILL, UP, LEFT, DOWN, RIGHT};				//declares enum direction to handle player movement
	direction playerDirection;
	sf::Vector2f moveVect = sf::Vector2f(STILL, STILL);
	
	PlayerShape playerShape;

	Bullet bullet;											//declares bullet object to be used to fill vector of active bullets
	std::vector<Bullet> activeBullets;

	sf::CircleShape largeFollowArea;					//Furthist distance away which followers will follow you after gaining interest
	sf::CircleShape smallFollowArea;					// minimum distance you need to be to a follower for it to begin following you

	Tower *towerPTR;

	int laserLength;									//each player has individual stats for the laser a tower shoots
	int laserWidth;
	sf::Color laserColor;

public: 

		//CONSTRUCTOR 
	Player(sf::RenderWindow &window, int pNumber = 1, float startHealth = 300.f, float startShieldSize = 0,
		int startScore = 0, float smallRadius = 60.f, float largeRadius = 180.f, float areaOutline = 4.f,
		int laserL = 100.f, int laserW = 1, sf::Color laserC = sf::Color::Cyan)
	{
		playerNumber = pNumber;
		health = startHealth;
		maxHealth = startHealth;
		shieldSize = startShieldSize;
		score = startScore;

		playerShape = PlayerShape();

		playerDirection = STILL;
		playerPosition = playerShape.getPosition();

		healthBarWidth = 30.f;
		healthBarPosition = sf::Vector2f(window.getSize().x / 3.f, 20.f);
		sf::Vector2f startHealthBarSize = sf::Vector2f(startHealth, healthBarWidth);

		healthBarRed.setSize(startHealthBarSize);								//initiates red health bar
		healthBarRed.setPosition(healthBarPosition);
		healthBarRed.setFillColor(sf::Color::Red);
																				//initiates green health bar on top of it
		healthBarGreen.setSize(startHealthBarSize);
		healthBarGreen.setPosition(healthBarPosition);
		healthBarGreen.setFillColor(sf::Color::Green);

		shield.setSize(sf::Vector2f(shieldSize, healthBarWidth));								//Player not initiated with shield, 0 size
		shield.setPosition(healthBarPosition);
		shield.setFillColor(sf::Color::Blue);

		setText(healthText, arial);		// loads text for putting health in string format

		largeFollowArea.setRadius(largeRadius);
		largeFollowArea.setOrigin(largeFollowArea.getRadius(), largeFollowArea.getRadius());
		largeFollowArea.setPosition(playerShape.getPosition());
		largeFollowArea.setOutlineColor(sf::Color::Green);
		largeFollowArea.setOutlineThickness(areaOutline);
		largeFollowArea.setFillColor(sf::Color::Transparent);
		

		smallFollowArea.setRadius(smallRadius);
		smallFollowArea.setOrigin(smallFollowArea.getRadius(), smallFollowArea.getRadius());
		smallFollowArea.setPosition(playerShape.getPosition());
		smallFollowArea.setOutlineColor(sf::Color::Blue);
		smallFollowArea.setOutlineThickness(areaOutline);
		smallFollowArea.setFillColor(sf::Color::Transparent);

		laserLength = laserL;
		laserWidth = laserW;
		laserColor = laserC;

	}

	//ALL GET METHODS OF CLASS PLAYER
	int getPlayerNumber()
	{
		return playerNumber;
	}

	int getScore()
	{
		return score;
	}

	float getHealth()
	{
		return health;
	}

	PlayerShape getPlayerShape()
	{
		return playerShape;
	}

	sf::Vector2f getPosition()
	{
		return playerPosition;
	}

	sf::Vector2f getGunPosition()
	{
		return playerShape.getGunPosition();
	}

	sf::FloatRect getPlayerBounds()
	{
		return playerShape.getHeartBounds();
	}

	sf::FloatRect getSmallFollowAreaBounds()
	{
		return smallFollowArea.getGlobalBounds();
	}

	float getSmallFollowAreaRadius()
	{
		return smallFollowArea.getRadius();
	}

	sf::FloatRect getLargeFollowAreaBounds()
	{
		return largeFollowArea.getGlobalBounds();
	}

	float getLargeFollowAreaRadius()
	{
		return largeFollowArea.getRadius();
	}

	int getLaserLength()
	{
		return laserLength;
	}

	int getLaserWidth()
	{
		return laserWidth;
	}

	sf::Color getLaserColor()
	{
		return laserColor;
	}


	//ALL SET METHODS OF CLASS PLAYER
	void setHealth(float newHealth)
	{
		health = newHealth;
	}

	int setScore(int newScore)
	{
		score = newScore;
	}

	void setPosition(sf::Vector2f newPos)
	{
		playerShape.setPosition(newPos.x, newPos.y);
	}


	//METHODS OF CLASS PLAYER MANAGING SCORE
	int adjScore(int adj)
	{
		score += adj;
	}


	//METHODS RELATED TO MOVING PLAYER DIRECTLY
	void movePlayer(int dir, bool towerCollision, sf::Vector2f towerPos,
		float towerRadius, int speed = 5)					//moves player based on int speed and int direction (enum dir) provided by main function
	{

		bool movingIntoTower = false;								//local variable to check if a player tries to move into a tower bounds
		//std::cout << "Inputted direction: " << dir << std::endl;

		switch (dir)
		{
		case UP:
			moveVect = sf::Vector2f(STILL, -speed);
			break;

		case LEFT:
			moveVect = sf::Vector2f(-speed, STILL);
			break;
		case DOWN:
			moveVect = sf::Vector2f(STILL, speed);
			break;

		case RIGHT:
			moveVect = sf::Vector2f(speed, STILL);
			break;
		}

		if (towerCollision)
		{
			//std::cout << "dist from tow center " << distanceFrom(playerPosition + moveVect, towerPos) << std::endl;
			movingIntoTower = distanceFrom(playerPosition + moveVect, towerPos) <= towerRadius;
		}

		if (movingIntoTower)
		{
			moveVect = -moveVect / 5.f;
		}

		playerShape.movePlayershape(moveVect);		//function in playershape has default argument move set to 5
		playerPosition += moveVect;


		largeFollowArea.setPosition(playerShape.getPosition());			//Follow circles stay around players
		smallFollowArea.setPosition(playerShape.getPosition());
	}

	float distanceFrom(sf::Vector2f object1Pos, sf::Vector2f object2Pos)											//calculates vector distance from player or tower object
	{
		float xDist = abs(object1Pos.x - object2Pos.x);			//calculates x and y distances away follower is from player
		float yDist = abs(object1Pos.y - object2Pos.y);

		return pow(xDist * xDist + yDist * yDist, 0.5);							//calculates vector for distance from follower to player
	}



	//METHODS RELATED TO MANAGING A PLAYER'S HEALTH
	bool adjHealth(float adj)
	{
		if (health == 0)			//First checks to see if health is already 0, and returns immediately if so
			return true;

		bool usingShield = shieldSize + adj <= maxHealth && shieldSize + adj > 0;

		if (usingShield && health == maxHealth)				//if they player has a shield, add/subtract from the shield
		{
			shieldSize += adj;
		}
			

		else if (health + adj <= maxHealth)				//if the health + adjustment is less than max health then deal with health
		{
			health += adj;
		}
			
		else if (health + adj > maxHealth && !usingShield)		//if the adjustment is greater than max health and the player is not using a shield
		{
			health = maxHealth;									//set health to max and add difference to shield
			shieldSize += (health + adj - maxHealth);
		}

		sf::Vector2f  healthBarSize = sf::Vector2f(health, healthBarWidth);
		sf::Vector2f shieldBarSize = sf::Vector2f(shieldSize, healthBarWidth);

		healthText.setString(std::to_string(static_cast<int>(health)) + "/"
			+ std::to_string(static_cast<int>(maxHealth)));				//updates graphics and text
		healthBarGreen.setSize(healthBarSize);
		shield.setSize(shieldBarSize);

		return false;
	}


	//SETS TEXT FOR NUMERICAL DISPLAY OF HEALTH OVERLAYED ONTO BARS
	void setText(sf::Text &healthText, sf::Font &arial)
	{

		if (!arial.loadFromFile("arial.ttf")) 	//loads font to use for text drawing
		{
			std::cout << "Error loading text" << std::endl;
		}
		int textSize = 40;
		sf::Vector2f centerHealthBar = sf::Vector2f(90.f, -10.f);		//vector adjusts health string text display for centering

		healthText.setFont(arial);
		healthText.setCharacterSize(textSize);
		healthText.setFillColor(sf::Color::White);
		healthText.setPosition(healthBarPosition + centerHealthBar);
		healthText.setString(std::to_string(static_cast<int>(health)) + "/"
			+ std::to_string(static_cast<int>(maxHealth)));

	}


	//METHODS RELATING TO PLAYERS INERACTION WITH TOWERS




	//DRAWING METHODS OF CLASS PLAYER
	void drawPlayer(sf::RenderWindow &window)
	{
		playerShape.drawPlayer(window);
	}

	void drawHealthBar(sf::RenderWindow &window)
	{
		window.draw(healthBarRed);
		window.draw(healthBarGreen);
		window.draw(shield);

		window.draw(largeFollowArea);
		window.draw(smallFollowArea);

		window.draw(healthText);
	}

		
};


