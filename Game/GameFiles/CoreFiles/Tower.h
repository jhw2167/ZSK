#pragma once

//project includes
#include "../../../BaseCode/pch/stdafx.h"
#include "../GameObj.h"
//#include "Player.h"

class Tower:
	public GameObj
{

private:

	/*  Basic Properties  */
	float towerRadius;		
	int towerNumber; 
	//towers will be circleShapes in each of the four coners of the map
	//labels towers, 0, 1, 2, 3

	enum towerOwned {NOTOWNED = 0, PLAYER1, PLAYER2, PLAYER3, PLAYER4};
	int towerOwnedBy;
	
	sf::CircleShape towerShape;
	sf::CircleShape towerOutline;

	/* Tower laser Vars  */
	sf::Texture lTexture;
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
	Tower(const int tNumber = 0);


		/*  Init Methods  */
	void initVars(const int tNumber);
	void initTowerShape();
	void initLaserTexture();
	void initLaser();


		/*  Setter methods  */
	void setRadius(float tRadius);
	void setPosition(int tNumber);


		/*  Accessor Methods  */
	int getTowerNum() const;
	const sf::FloatRect getGlobalBounds() const;
	sf::Vector2f getPosition() const;
	float getTowerRadius() const ;
	sf::CircleShape getTowerShape() const;
	int getTowerOwnership() const ;
	bool isLaserFiring() const;

	//TOWER OWNERSHIP METHODS
	void changeOwner(int newOwner);
	

	/*  Functions  */

	//TOWER COLLISIONS

	//TOWER MECHANICS


	//Laser Based Methods
	void changeLaserColor(const int newOwner);

	/*		UPDATE		*/
	STATE update();
	/***************/


	//TOWER DRAW METHODS
	void drawTowers();

	/*  Destructor  */
	~Tower();

	/*  Copy Constructor  */
	Tower(const Tower& rhs);
};
