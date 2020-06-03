
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

	enum direction {STILL = 0, UP, LEFT, DOWN, RIGHT};							
	//declares enum direction to handle player movement

	sf::Color playerColor;
	sf::Color bodyColor;

public:

	PlayerShape(float scale = 10.f, sf::Color pColor = sf::Color::Red,
		sf::Vector2f startPos = sf::Vector2f(100.f, 100.f) )										
	{	
		setPlayerShape(scale);
		setColor(pColor);
		setPosition(startPos);
	}

	//SET FUNCTIONS
	void setPosition(sf::Vector2f newPos)
	{
		heart.setPosition(newPos);

		head.setPosition(newPos.x, newPos.y - bodyHeight / 2.f);

		playerBody[BODY].setPosition(sf::Vector2f(newPos.x, newPos.y - bodyLength / 4.f));

		playerBody[ARMS].setPosition(newPos);

		playerBody[GUN1].setPosition(newPos.x + armLength / 2.f, newPos.y);

		playerBody[GUN2].setPosition(newPos.x + armLength / 2.f, newPos.y - gunLength / 2.f);

		playerBody[LEG1].setPosition(newPos.x - bodyLength / 3.f, newPos.y + (3.f / 4.f) * bodyHeight);

		playerBody[LEG2].setPosition(newPos.x + bodyLength / 3.f, newPos.y + (3.f / 4.f) * bodyHeight);

	}

	void setPlayerShape(float scale)
	{
		//"scale" places players size relative to window, color is color of players heart
		heartRadius = scale;
		headRadius = scale * 2.f;

		bodyHeight = scale * 8.f;
		bodyLength = scale * 3.f;

		armLength = scale * 16.f;
		armHeight = scale * 1.5f;

		gunLength = scale * 4.f;
		gunHeight = scale * 1.5f;

		legLength = scale * 6.f;
		legWidth = scale * 1.75f;

		heart.setRadius(scale);
		heart.setOrigin(heart.getRadius(), heart.getRadius());						//sets up player heart shape to be drawn

		head.setRadius(headRadius);													//sets up player head 
		head.setOrigin(head.getRadius(), head.getRadius());

		body.setSize(sf::Vector2f(bodyLength, bodyHeight));							//player body
		body.setOrigin(bodyLength / 2.f, 0);

		arms.setSize(sf::Vector2f(armLength, armHeight));							//players arms as 1 rectangle object
		arms.setOrigin(armLength / 2.f, armHeight / 2.f);

		gun1.setSize(sf::Vector2f(gunHeight, gunLength));							//players gun
		gun1.setOrigin(gunHeight / 2.f, gunLength / 2.f);

		gun2.setSize(sf::Vector2f(gunLength, gunHeight));							//players gun
		gun2.setOrigin(gunLength / 3.f, gunHeight / 2.f);

		leg1.setSize(sf::Vector2f(legWidth, legLength));							//players first leg
		leg1.setOrigin(sf::Vector2f(legWidth / 2.f, 0));
		leg1.setRotation(35);

		leg2.setSize(sf::Vector2f(legWidth, legLength));							//players second leg
		leg2.setOrigin(sf::Vector2f(legWidth / 2.f, 0));
		leg2.setRotation(325);

		playerBody[0] = body;					//adds each item to array to be drawn
		playerBody[1] = arms;
		playerBody[2] = gun1;
		playerBody[3] = gun2;
		playerBody[4] = leg1;
		playerBody[5] = leg2;
	}

	void setColor(sf::Color pColor, sf::Color bColor = sf::Color::Black)
	{
		heart.setFillColor(pColor);
		head.setFillColor(bColor);
		playerBody[BODY].setFillColor(bColor);
		playerBody[ARMS].setFillColor(bColor);
		playerBody[GUN1].setFillColor(pColor);
		playerBody[GUN2].setFillColor(pColor);
		playerBody[LEG1].setFillColor(bColor);
		playerBody[LEG2].setFillColor(bColor);

		playerColor = pColor;
		bodyColor = bColor;
	}

	//GET FUNCTIONS
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

	float getLeftBounds()
	{
		return playerBody[ARMS].getPosition().x - armLength / 2;		//left and right bounds with respect to the players arms
	}

	float getUpperBounds()									//returns player's upper, lower, left and right bounds for boundry checking
	{
		return head.getPosition().y - head.getRadius();			//the head is the highest point on the character, and its position is retrieved at its center
	}

	float getRightBounds()
	{
		return playerBody[ARMS].getPosition().x + armLength / 2;		//left and right bounds with respect to the players arms
	}

	float getLowerBounds()
	{
		return playerBody[LEG1].getPosition().y + legLength;			//players lowerBounds with respect 
	}

	sf::Color getPlayerColor()
	{
		return playerColor;
	}

	sf::Color getBodyColor()
	{
		return bodyColor;
	}

	//MOVE
	void movePlayershape(sf::Vector2f moveVect)
	{
		for (int i = 0; i < 6; i++)
		{
			playerBody[i].move(moveVect);
		}

		head.move(moveVect);
		heart.move(moveVect);
	}


	//DRAW FUNCTIONS
	void drawPlayer(sf::RenderWindow &window)
	{

		for (int i = 0; i < 6; i++)
		{
			window.draw(playerBody[i]);
		}

		window.draw(head);
		window.draw(heart);

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

	sf::Color playerColor;
	static sf::Color pColors[];
	

	float health;
	float maxHealth;

	float shield;
	float maxShield;

	static float healthBarWidth;
	sf::Vector2f healthBarPosition;		
	sf::RectangleShape healthBarRed;							//representaion of player's lost health
	sf::RectangleShape healthBarGreen;							//visual representation of player's health
	sf::RectangleShape shieldBar;							//representaiton of player's shield (if applicable)

	sf::Text healthText;
	sf::Font arial;								//Declares font to use for text drawing

	enum direction {STILL, UP, LEFT, DOWN, RIGHT};				//declares enum direction to handle player movement
	direction playerDirection;
	sf::Vector2f playerPosition;
	sf::Vector2f moveVect;
	
	PlayerShape playerShape;
	sf::RectangleShape pBox;

	Bullet bullet;											//declares bullet object to be used to fill vector of active bullets
	std::vector<Bullet> activeBullets;

	static float areaOutline;				//outline thickness of large and small follower circles
	sf::CircleShape largeFollowArea;				//Furthest distance away which followers will follow you after gaining interest
	sf::CircleShape smallFollowArea;				// minimum distance you need to be to a follower for it to begin following you

	Tower *towerPTR;

	int laserLength;			//Max distance tower projectiles travel for player
	int laserWidth;				//Max width of player projectiles, levels 1->2->3
	sf::Color laserColor;

public: 

		//CONSTRUCTOR 
	Player(sf::RenderWindow &window, sf::Vector2f startPos, int pNumber = 1, float scale = 2.f, float startHealth = 300.f, 
		float startMaxHealth = 300.f, float startShield = 100.f, float startMaxShield = 100.f, int startScore = 0, float smallRadius = 60.f,
		float largeRadius = 180.f, int laserL = 100.f, int laserW = 1,  bool showBox = true)
	{
		//Initialize basic player components
		playerNumber = pNumber;
		playerColor = pColors[pNumber - 1];
		score = startScore;

		playerDirection = STILL;
		moveVect = sf::Vector2f(STILL, STILL);

		//Initialize player box and position
		playerShape = PlayerShape(scale, playerColor, startPos);
		setPlayerBox(playerShape, showBox);
		setPosition(startPos);

		//initialize player spawn health and shield bars
		initHealthBar(window, startHealth, startMaxHealth);
		initShieldBar(window, startShield, startMaxShield);
		initHealthText(healthText, arial);

		
		
		//Initialize large and small follower areas
		initSmallFollowerRadius(smallRadius);
		initLargeFollowerRadius(largeRadius);

	
		laserLength = laserL;
		laserWidth = laserW;
		laserColor = playerColor;

	}

	//initialize METHODS FOR CLASS PLAYER

	//SETS TEXT FOR NUMERICAL DISPLAY OF HEALTH OVERLAYED ONTO BARS
	void initHealthText(sf::Text &healthText, sf::Font &arial)
	{
		// loads text for putting health in string format
		if (!arial.loadFromFile("arial.ttf")) 	//loads font to use for text drawing
		{
			std::cout << "Error loading text" << std::endl;
		}
		int textSize = 35;
		sf::Vector2f centerHealthBar = sf::Vector2f(90.f, -8.f);		//vector adjusts health string text display for centering

		healthText.setFont(arial);
		healthText.setCharacterSize(textSize);
		healthText.setFillColor(sf::Color::White);
		healthText.setPosition(healthBarPosition + centerHealthBar);
	}

	void initHealthBar(sf::RenderWindow &window, float sHealth, float sMaxHealth)
	{
		maxHealth = sMaxHealth;

		float healthBarX = window.getSize().x / 3.f;
		float healthBarY = window.getSize().y / 40.f;

		healthBarPosition = sf::Vector2f(healthBarX , healthBarY);
		sf::Vector2f startHealthBarSize = sf::Vector2f(sMaxHealth, healthBarWidth);

		healthBarRed.setSize(startHealthBarSize);			//initiates red (background) health bar
		healthBarRed.setPosition(healthBarPosition);
		healthBarRed.setFillColor(sf::Color::Red);

		
		setHealth(sHealth);								//initiates green health bar on top of it
		healthBarGreen.setPosition(healthBarPosition);
		healthBarGreen.setFillColor(sf::Color::Green);
	}

	void initShieldBar(sf::RenderWindow &window, float sShield, float sMaxShield) 
	{
		maxShield = sMaxShield;

		setShield(sShield);									//Player initiated with size 100 shield
		shieldBar.setPosition(healthBarPosition);
		shieldBar.setFillColor(sf::Color::Blue);
	}

	void initSmallFollowerRadius(float newRadius)
	{
		setSmallFollowerRadius(newRadius);
		smallFollowArea.setOrigin(newRadius, newRadius);
		smallFollowArea.setPosition(playerPosition);

		std::cout << "small circle at x pos: " << smallFollowArea.getPosition().x << std::endl;
		std::cout << "small circle at y pos: " << smallFollowArea.getPosition().y << std::endl;

		smallFollowArea.setOutlineThickness(areaOutline);
		smallFollowArea.setOutlineColor(sf::Color::Blue);
		smallFollowArea.setFillColor(sf::Color::Transparent);
	}

	void initLargeFollowerRadius(float newRadius)
	{
		largeFollowArea.setRadius(newRadius);
		largeFollowArea.setOrigin(newRadius, newRadius);
		largeFollowArea.setPosition(playerPosition);

		largeFollowArea.setOutlineThickness(areaOutline);
		largeFollowArea.setOutlineColor(sf::Color::Green);
		largeFollowArea.setFillColor(sf::Color::Transparent);
	}

	//ALL SET METHODS OF CLASS PLAYER
	void setHealth(float newHealth)
	{
		health = newHealth;

		sf::Vector2f  healthBarSize = sf::Vector2f(health, healthBarWidth);

		healthText.setString(std::to_string(static_cast<int>(health)) + "/"
			+ std::to_string(static_cast<int>(maxHealth)));				//updates graphics and text
		healthBarGreen.setSize(healthBarSize);

	}

	void setShield(float newShield)
	{
		shield = newShield;

		sf::Vector2f  shieldBarSize = sf::Vector2f(shield * 3.f, healthBarWidth);

		healthText.setString(std::to_string(static_cast<int>(health + shield)) + "/"
			+ std::to_string(static_cast<int>(maxHealth)));				//updates graphics and text
		shieldBar.setSize(shieldBarSize);

	}

	int setScore(int newScore)
	{
		score = newScore;
	}

	void setPosition(sf::Vector2f newPos)
	{
		playerPosition = newPos;
		playerShape.setPosition(newPos);
		pBox.setPosition(newPos);
	}

	void setPlayerBox(PlayerShape &shape, bool showBoxes)
	{
		float length = shape.getRightBounds() - shape.getLeftBounds();
		float height = shape.getLowerBounds() - shape.getUpperBounds();

		pBox = sf::RectangleShape(sf::Vector2f(length, height));

		sf::Color outlineColor = sf::Color::Transparent;
		if (showBoxes)
			outlineColor = sf::Color::Black;

		float thickness = 2.f;
		pBox.setFillColor(sf::Color::Transparent);
		pBox.setOutlineThickness(thickness);
		pBox.setOutlineColor(outlineColor);

		pBox.setOrigin(length / 2.f, shape.getPosition().y - shape.getUpperBounds());
	}

	void setSmallFollowerRadius(float newRadius)
	{
		smallFollowArea.setRadius(newRadius);
	}

	void setLargeFollowerRadius(float newRadius)
	{
		largeFollowArea.setRadius(newRadius);
	}

	void setLaserLength()
	{

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

	float getShield() {
		return shield;
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
		pBox.move(moveVect);
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
	void takeDamage(float dmg)
	{
		//dmg is a POSITIVE value inherently, i.e to reduce health pass
		//positive damage values
		float combinedHealth = health + shield - dmg;

		float newShield = std::min( std::max(combinedHealth - maxHealth, 0.f), maxShield);
		float newHealth = std::max(std::min(combinedHealth - newShield, maxHealth), 0.f);
		//Sets new health and shield values with max and min functions

		setHealth(newHealth);
		setShield(newShield);
	}


	//METHODS RELATING TO PLAYERS INERACTION WITH TOWERS




	//DRAWING METHODS OF CLASS PLAYER
	void drawPlayer(sf::RenderWindow &window)
	{
		playerShape.drawPlayer(window);
		window.draw(pBox);
	}

	void drawHealthBar(sf::RenderWindow &window)
	{
		window.draw(healthBarRed);
		window.draw(healthBarGreen);
		window.draw(shieldBar);

		window.draw(largeFollowArea);
		window.draw(smallFollowArea);

		window.draw(healthText);
	}

		
};


