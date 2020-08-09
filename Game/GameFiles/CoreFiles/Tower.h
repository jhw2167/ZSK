#pragma once

//project includes
#include "../../../BaseCode/pch/stdafx.h"
#include "Player.h"

class Tower {

private:
	float towerRadius;		
	int towerNumber; 
	//towers will be circleShapes in each of the four coners of the map
	//labels towers, 0, 1, 2, 3

	enum towerOwned {NOTOWNED = 0, PLAYER1, PLAYER2, PLAYER3, PLAYER4};
	int towerOwnedBy;
	
	sf::Vector2f towerPosition;
	sf::CircleShape towerShape;
	sf::CircleShape towerOutline;

	/* Tower laser Vars  */
	
	sf::Texture laserTexture;
	sf::Sprite laser;
	bool isFiring;

	enum playerColors
	{
		P1_COLOR = 0,
		P2_COLOR,
		P3_COLOR,
		P4_COLOR,
	};

public:
	
		/*  Constructors */
	Tower(sf::RenderWindow const &window, const int tNumber = 0);


		/*  Init Methods  */
	void initVars(const int tNumber);
	void initTowerShape(sf::RenderWindow const &window);
	void initLaser();


		/*  Setter methods  */
	void setRadius(float tRadius);
	void setPosition(sf::RenderWindow const &window, int tNumber);


		/*  Accessor Methods  */
	sf::FloatRect getTowerGlobalBounds();

	sf::Vector2f getPosition();

	float getTowerRadius();

	sf::CircleShape getTowerShape();

	int getTowerOwnership();

	bool isLaserFiring() const;

	//TOWER OWNERSHIP METHODS
	void changeOwner(int newOwner);
	

	/*  Functions  */

	//TOWER COLLISIONS
	bool checkTowerCollision(Player &player);

	float distanceFrom(sf::Vector2f objectPos);



	//TOWER MECHANICS


	//Laser Based Methods
	void changeLaserColor(const int newOwner);

	//TOWER DRAW METHODS
	void drawTowers(sf::RenderWindow &window);

};
