#pragma once
//header file to construct and design the player object for the game

//project includes
#include "../../../BaseCode/pch/stdafx.h"
#include "Bullet.h"
#include "FollowerShape.h"
#include "Tower.h"



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
	sf::Vector2f getPosition() const;
	//Function returns players position at his heart for collisions

	sf::Vector2f getGunPosition() const;
	//Returns position of gun for shooting
	
	const sf::FloatRect& getHeartBounds() const;
	
	float getLeftBounds() const;
	//returns player's upper, lower, left and right bounds for boundry checking

	float getUpperBounds() const;
	//player's head is highest point on their body

	float getRightBounds() const;
	//left and right bounds with respect to the players arms

	float getLowerBounds() const;
	//players lowerBounds with respect 

	sf::Color getPlayerColor() const;

	sf::Color getBodyColor() const;


	//MOVE
	void movePlayershape(sf::Vector2f &moveVect);


	//DRAW FUNCTIONS
	void drawPlayer(sf::RenderWindow &window);

};

//END CLASS PLAYERSHAPE








//BEGIN CLASS PLAYER
class Follower;
class Tower;				//forward declaration of class tower so player has access


class Player : 
	public GameObj
{

private:

	/* Basics */
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

	/* HUD */
	sf::Vector2f healthBarSize;
	//standard value, does NOT change with damage taken
	//changes with window size
	sf::Vector2f healthBarPosition;
	sf::Vector2f healthBarOrigin;
	sf::RectangleShape healthBarRed;							//representaion of player's lost health
	sf::RectangleShape healthBarGreen;							//visual representation of player's health
	sf::RectangleShape shieldBar;							//representaiton of player's shield (if applicable)

	sf::Text healthText;

	sf::Text lifeText;
	static PlayerShape lifeFigure;

	sf::Text scoreText;
	static FollowerShape scoreFigure;

	/* Movement */
	enum Direction {STILL, UP, LEFT, DOWN, RIGHT};				//declares enum direction to handle player movement
	float playerSpeed;
	Direction playerDirection;
	sf::Vector2f moveVect;
	
	PlayerShape playerShape;
	sf::RectangleShape pBox;

	std::list<Bullet> activeBullets;

	static float areaOutline;				//outline thickness of large and small follower circles
	sf::CircleShape largeFollowArea;				//Furthest distance away which followers will follow you after gaining interest
	sf::CircleShape smallFollowArea;				// minimum distance you need to be to a follower for it to begin following you
	float smallFolRad;
	float minLargeFolRad;
	float maxLargeFolRad;
	bool snap;

	int laserLength;			//Max distance tower projectiles travel for player
	int laserWidth;				//Max width of player projectiles, levels 1->2->3
	
	//sf::CircleShape dot = sf::CircleShape(4.f);
	//sf::RectangleShape box;

	/*** PRIVATE FUNCTIONS ***/


	//INITIALIZE METHODS FOR CLASS PLAYER
	void initHealthBar(float sHealth, float sMaxHealth);

	void initShieldBar(float sShield, float sMaxShield);

	void initHealthText();

	void initScore();

	void initLives(int newLives);

	void initSmallFollowerRadius(float newRadius);

	void initLargeFollowerRadius(float newRadius);
	//End init methods



	/*   Private Update Functions  */

	//related to moving our player
	void movePlayerLogic();
		void movePlayer(sf::Vector2f &mVect);
		void moveLogic(int dir);


	//Related to shooting
		void shootingMechanics();

	//Related to taking damage


	//miscellaneous Mechanics
		void miscMechanics();

public: 

		//CONSTRUCTOR 
	Player(int pNumber = 1, int startLives = 3, float scale = 2.5f, float startHealth = 300.f,
		float startMaxHealth = 300.f, float startShield = 100.f, float startMaxShield = 100.f, 
		float mSpeed = 6.f, int startScore = 0, float smallRadius = 70.f,
		float maxLargeRadius = 240.f, int laserL = 100.f, int laserW = 1, bool showBox = false);


	//ALL SET METHODS OF CLASS PLAYER
	void setLives(int newLives);

	void setHealth(float newHealth);

	void setInvulnFrames(int newFrames);

	void centerHealthText();

	void setShield(float newShield);

	void setShieldRegen(float newRegen);

	void setScore(int newScore);

	void setplayerSpeed(float newSpeed);

	void setPosition(const sf::Vector2f& newPos);

	void setPlayerBox(PlayerShape& shape, bool showBoxes);

	void setSmallFollowerRadius(float newRadius);

	void setLargeFollowerRadius(float newRadius);

	void setMinLFR(float newRadius);

	void setMaxLFR(float newRadius);

	void setLaserLength(int laserL);

	void setLaserWidth(int laserW);


	//ALL GET METHODS OF CLASS PLAYER
	int getPlayerNumber() const;

	int getScore() const;
	
	float getHealth() const;
	
	float getShield() const;

	const PlayerShape& getPlayerShape() const;

	sf::Color getPlayerColor() const;

	float getplayerSpeed() const;

	sf::Vector2f getPosition() const;

	sf::Vector2f getGunPosition() const;

	sf::FloatRect getPlayerBounds() const;

	sf::FloatRect getHeartBounds() const;

	sf::FloatRect getSmallFollowAreaBounds() const;

	float getSmallFollowAreaRadius() const;

	sf::FloatRect getLargeFollowAreaBounds() const;

	float getLargeFollowAreaRadius() const;

	float getMinLFR() const;

	int getLaserLength() const;

	int getLaserWidth() const;

	bool isGameOver() const;

	const sf::FloatRect& getGlobalBounds() const;

	//METHODS OF CLASS PLAYER MANAGING SCORE
	void adjScore(int adj); 

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

	void deleteBullet(std::list<Bullet>::iterator& b);

	void checkBulletInBounds(sf::RenderWindow &window);


	//METHODS RELATING TO FOLLOWERS
	int shootFollower(sf::FloatRect const &followerBounds);

	int dmgFollower(int i);

	void growLargeFollowArea(bool grow, float growRate = 2.f);


	//DRAWING METHODS OF CLASS PLAYER
	void drawPlayer(sf::RenderWindow &window);

	void drawHealthBar(sf::RenderWindow &window);

	void drawBullets(sf::RenderWindow &window);

	void drawScore(sf::RenderWindow &window); 

	/* UPDATE FUNCTION */
	STATE update();

	//COPY CONSTRUCTOR
	Player(const Player& rhs);
};


