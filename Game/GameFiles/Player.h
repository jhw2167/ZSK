#pragma once
//header file to construct and design the player object for the game

//project includes
#include "../pch/stdafx.h"
#include "Bullet.h"
#include "FollowerShape.h"



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

	sf::RectangleShape playerBody[6];				
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
		/*  Constructor  */
	PlayerShape(float scale = 2.5f, sf::Color pColor = sf::Color::Red,
		sf::Vector2f startPos = sf::Vector2f(100.f, 100.f));
	
	/* Setter Functions  */
	void setPosition(sf::Vector2f const &newPos);

	void setPlayerShape(float scale);
	

	void setColor(sf::Color &pColor, sf::Color bColor = sf::Color::Black);


	/*  Getter Functions  */
	sf::Vector2f getPosition();
	//Function returns players position at his heart for collisions

	sf::Vector2f getGunPosition();
	//Returns position of gun for shooting
	
	sf::FloatRect getHeartBounds();
	
	float getLeftBounds();
	//returns player's upper, lower, left and right bounds for boundry checking

	float getUpperBounds();
	//player's head is highest point on their body

	float getRightBounds();
	//left and right bounds with respect to the players arms

	float getLowerBounds();
	//players lowerBounds with respect 

	sf::Color getPlayerColor();

	sf::Color getBodyColor();


	//MOVE
	void movePlayershape(sf::Vector2f &moveVect);


	//DRAW FUNCTIONS
	void drawPlayer(sf::RenderWindow &window);

};

//END CLASS PLAYERSHAPE








//BEGIN CLASS PLAYER
class Follower;
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
	int lives;
	bool gameOver;

	float shield;
	float maxShield;
	float shieldRegen;
	//units: float_val / sec (60 frames)
	int invulnerability;		
	//units: #frames of invln

	sf::Vector2f healthBarSize;
	//standard value, does NOT change with damage taken
	//changes with window size
	sf::Vector2f healthBarPosition;
	sf::Vector2f healthBarOrigin;
	sf::RectangleShape healthBarRed;							//representaion of player's lost health
	sf::RectangleShape healthBarGreen;							//visual representation of player's health
	sf::RectangleShape shieldBar;							//representaiton of player's shield (if applicable)

	sf::Text healthText;
	static sf::Font arial;								//Declares font to use for text drawing

	sf::Text lifeText;
	static PlayerShape lifeFigure;

	sf::Text scoreText;
	static FollowerShape scoreFigure;

	enum direction {STILL, UP, LEFT, DOWN, RIGHT};				//declares enum direction to handle player movement
	float playerSpeed;
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
	float smallFolRad;
	float minLargeFolRad;
	float maxLargeFolRad;
	bool snap;

	int laserLength;			//Max distance tower projectiles travel for player
	int laserWidth;				//Max width of player projectiles, levels 1->2->3
	
	sf::CircleShape dot = sf::CircleShape(4.f);
	sf::RectangleShape box;

	float wLength;
	float wHeight;

public: 

		//CONSTRUCTOR 
	Player(sf::RenderWindow &window, int pNumber = 1, int startLives = 3, float scale = 2.5f, float startHealth = 300.f,
		float startMaxHealth = 300.f, float startShield = 100.f, float startMaxShield = 100.f, 
		float mSpeed = 6.f, int startScore = 0, float smallRadius = 70.f,
		float maxLargeRadius = 240.f, int laserL = 100.f, int laserW = 1, bool showBox = false);


	//INITIALIZE METHODS FOR CLASS PLAYER
	void initHealthBar(sf::RenderWindow &window, float sHealth, float sMaxHealth);

	void initShieldBar(sf::RenderWindow &window, float sShield, float sMaxShield);
	
	void initHealthText();

	void initScore();

	void initLives(int newLives);

	void initSmallFollowerRadius(float newRadius);

	void initLargeFollowerRadius(float newRadius);
	//End init methods


	//ALL SET METHODS OF CLASS PLAYER
	void setLives(int newLives);

	void setHealth(float newHealth);

	void setInvulnFrames(int newFrames);

	void centerHealthText();

	void setShield(float newShield);

	void setShieldRegen(float newRegen);

	void setScore(int newScore);

	void setplayerSpeed(float newSpeed);

	void setPosition(sf::Vector2f newPos);

	void setPlayerBox(PlayerShape &shape, bool showBoxes);

	void setSmallFollowerRadius(float newRadius);

	void setLargeFollowerRadius(float newRadius);

	void setMinLFR(float newRadius);

	void setMaxLFR(float newRadius);

	void setLaserLength(int laserL);

	void setLaserWidth(int laserW);

	void setWindowDims(sf::RenderWindow &window);


	//ALL GET METHODS OF CLASS PLAYER
	int getPlayerNumber();

	int getScore();
	
	float getHealth();
	
	float getShield();

	PlayerShape getPlayerShape();

	sf::Color getPlayerColor();

	float getplayerSpeed();

	sf::Vector2f getPosition();

	sf::Vector2f getGunPosition();

	sf::FloatRect getPlayerBounds();

	sf::FloatRect getHeartBounds();

	sf::FloatRect getSmallFollowAreaBounds();

	float getSmallFollowAreaRadius();

	sf::FloatRect getLargeFollowAreaBounds();

	float getLargeFollowAreaRadius();

	float getMinLFR(); 

	int getLaserLength();

	int getLaserWidth();

	bool isGameOver();

	//METHODS OF CLASS PLAYER MANAGING SCORE
	void adjScore(int adj); 

	//METHODS RELATED TO MOVING PLAYER DIRECTLY
	void movePlayer(sf::Vector2f &mVect);

	void moveLogic(int dir, int towerCollision, sf::Vector2f const &towerPos,
		float towerRadius);

	//calculates vector distance from player or tower object	
	float circle(float x, float radius); 


	//METHODS RELATED TO MANAGING A PLAYER'S HEALTH
	void takeDamage(float dmg);

	void regenShield();

	void loseLife();

	//METHODS RELATING TO PLAYERS INERACTION WITH TOWERS
	sf::Vector2f towerCollisions(int dir, int towerNum, sf::Vector2f const &towerPos,
		float towerRadius); 
	

	float invSpeedSq(float x, float y, float radius);

	sf::Vector2f avoidTower(sf::Vector2f dir, sf::Vector2f relPos, int towerNum);


	//METHODS RELATING TO MANAGINE PLAYERS BULLETS
	void shoot(sf::Vector2i const &cursorPos);

	void addBullet(sf::Vector2i const &cursorPos); 

	void moveBullets();

	void deleteBullet(int i);

	void checkBulletInBounds(sf::RenderWindow &window);


	//METHODS RELATING TO FOLLOWERS
	int shootFollower(sf::FloatRect const &followerBounds);

	int dmgFollower(int i);

	void growLargeFollowArea(float growRate = 2.f);


	//DRAWING METHODS OF CLASS PLAYER
	void drawPlayer(sf::RenderWindow &window);

	void drawHealthBar(sf::RenderWindow &window);

	void drawBullets(sf::RenderWindow &window);

	void drawScore(sf::RenderWindow &window); 
};


