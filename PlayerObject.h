
//header file to construct and design the player object for the game

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

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

//project includes
#include "BulletObject.h"
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

	PlayerShape(float scale = 2.5f, sf::Color pColor = sf::Color::Red,
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

	float shield;
	float maxShield;

	static float healthBarHeight;
	sf::Vector2f healthBarPosition;
	sf::Vector2f healthBarOrigin;
	sf::RectangleShape healthBarRed;							//representaion of player's lost health
	sf::RectangleShape healthBarGreen;							//visual representation of player's health
	sf::RectangleShape shieldBar;							//representaiton of player's shield (if applicable)

	sf::Text healthText;
	sf::Font arial;								//Declares font to use for text drawing

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

	int laserLength;			//Max distance tower projectiles travel for player
	int laserWidth;				//Max width of player projectiles, levels 1->2->3
	
	sf::CircleShape dot = sf::CircleShape(4.f);
	sf::RectangleShape box;

	float wLength;
	float wHeight;

public: 

		//CONSTRUCTOR 
	Player(sf::RenderWindow &window, int pNumber = 1, int startLives = 3, float scale = 2.5f, float startHealth = 300.f, 
		float startMaxHealth = 300.f, float startShield = 100.f, float startMaxShield = 100.f, float mSpeed = 6.f, int startScore = 0, float smallRadius = 60.f,
		float maxLargeRadius = 240.f, int laserL = 100.f, int laserW = 1,  bool showBox = false)
	{
		//Init Window Dims
		setWindowDims(window);

		//Initialize basic player components
		playerNumber = pNumber;
		playerColor = pColors[pNumber - 1];
		score = startScore;
		playerSpeed = mSpeed;
		initLives(startLives);

		playerDirection = STILL;
		moveVect = sf::Vector2f(STILL, STILL);

		//Initialize player box and position
		sf::Vector2f startPos = sf::Vector2f(wLength / 2.f, wHeight / 2.f);
		playerShape = PlayerShape(scale, playerColor, startPos);
		setPlayerBox(playerShape, showBox);

		setPosition(startPos);

		//initialize player spawn health and shield bars
		initHealthBar(window, startHealth, startMaxHealth);
		initShieldBar(window, startShield, startMaxShield);
		initHealthText();
		
		//Initialize large and small follower areas
		smallFolRad = smallRadius;
		maxLargeFolRad = maxLargeRadius;
		minLargeFolRad = smallRadius + 20.f;
		initSmallFollowerRadius(smallRadius);
		initLargeFollowerRadius(minLargeFolRad);

		//Initialize Laser attributes
		setLaserLength(laserL);
		setLaserWidth(laserW);
		//laser color = playercolor

		initScore();

	}


	//INITIALIZE METHODS FOR CLASS PLAYER
	void initHealthBar(sf::RenderWindow &window, float sHealth, float sMaxHealth)
	{
		maxHealth = sMaxHealth;
		//float stdLength = 300.f;

		float healthBarX = window.getSize().x / 2.f;
		float healthBarY = window.getSize().y / 40.f;

		healthBarPosition = sf::Vector2f(healthBarX , healthBarY);
		healthBarOrigin = sf::Vector2f(sMaxHealth / 2.f, healthBarHeight / 2.f);
		sf::Vector2f startHealthBarSize = sf::Vector2f(sMaxHealth, healthBarHeight);

		healthBarRed.setSize(startHealthBarSize);			//initiates red (background) health bar
		healthBarRed.setOrigin(healthBarOrigin);
		healthBarRed.setPosition(healthBarPosition);
		healthBarRed.setFillColor(sf::Color::Red);
		healthBarRed.setOutlineColor(sf::Color::Black);
		healthBarRed.setOutlineThickness(4.f);

		
		setHealth(sHealth);				
		healthBarGreen.setOrigin(healthBarOrigin);		
		healthBarGreen.setPosition(healthBarPosition);
		healthBarGreen.setFillColor(sf::Color::Green);
	}

	void initShieldBar(sf::RenderWindow &window, float sShield, float sMaxShield) 
	{
		maxShield = sMaxShield;

		setShield(sShield);									//Player initiated with size 100 shield
		shieldBar.setOrigin(healthBarOrigin);
		shieldBar.setPosition(healthBarPosition);
		shieldBar.setFillColor(sf::Color::Blue);
	}

	void initHealthText()
	{
		// loads text for putting health in string format
		if (!arial.loadFromFile("arial.ttf")) 	//loads font to use for text drawing
		{
			std::cout << "Error loading text" << std::endl;
		}
		int textSize = 35;
		float thickness = 2.f;
		sf::Vector2f centerHealthBar = sf::Vector2f(-60.f, -8.f);		//vector adjusts health string text display for centering

		healthText.setFont(arial);
		healthText.setCharacterSize(textSize);
		healthText.setFillColor(sf::Color::White);
		healthText.setOutlineColor(sf::Color::Black);
		healthText.setOutlineThickness(thickness);
		centerHealthText();
	}

	void initScore()
	{
		int textSize = 45;

		scoreText.setFont(arial);
		scoreText.setCharacterSize(textSize);
		scoreText.setFillColor(sf::Color::Black);

		sf::Vector2f pos = sf::Vector2f( wLength / 1.54f, 0.f );

		scoreText.setPosition(pos);
		setScore(0.f);


		if (playerNumber == 1){
			sf::Vector2f adj = sf::Vector2f(-25.f, 25.f);
			scoreFigure.setPosition(pos + adj);

		}
	}

	void initLives(int newLives)
	{
		int textSize = 45;

		lifeText.setFont(arial);
		lifeText.setCharacterSize(textSize);
		lifeText.setFillColor(sf::Color::Black);

		sf::Vector2f pos = sf::Vector2f(wLength / 1.35f, 0.f);

		lifeText.setPosition(pos);
		setLives(newLives);

		if (playerNumber == 1) {
			sf::Vector2f adj = sf::Vector2f(-30.f, 22.f);
			lifeFigure.setPosition(pos + adj);
		}


	}

	void initSmallFollowerRadius(float newRadius)
	{
		setSmallFollowerRadius(newRadius);
		smallFollowArea.setOrigin(newRadius, newRadius);
		smallFollowArea.setPosition(playerPosition);

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
	void setLives(int newLives) {
		lives = newLives;

		std::string newText = "x" + std::to_string(lives);
		lifeText.setString(newText);
	}

	void setHealth(float newHealth)
	{
		health = newHealth;

		sf::Vector2f  healthBarSize = sf::Vector2f(health, healthBarHeight);
		healthBarGreen.setSize(healthBarSize);

		healthText.setString(std::to_string(static_cast<int>(health)) + "/"
			+ std::to_string(static_cast<int>(maxHealth)));				//updates graphics and text
		centerHealthText();

	}

	void centerHealthText()
	{
		sf::Vector2f textDims = sf::Vector2f(healthText.getLocalBounds().width,
			healthText.getLocalBounds().height);
		sf::Vector2f centerText = sf::Vector2f(0,-6.f);	//requires bit of adj to center text 
		
		if (health < 10)				//more adj so it looks nice
			centerText.x += 15.f;
		else if (health < 100)
			centerText.x += 10.f;

		healthText.setOrigin(textDims / 2.f);
		healthText.setPosition(healthBarPosition + centerText);
	}

	void setShield(float newShield)
	{
		shield = newShield;

		sf::Vector2f  shieldBarSize = sf::Vector2f(shield * 3.f, healthBarHeight);

		healthText.setString(std::to_string(static_cast<int>(health + shield)) + "/"
			+ std::to_string(static_cast<int>(maxHealth)));				//updates graphics and text
		shieldBar.setSize(shieldBarSize);

	}

	void setScore(int newScore) 
	{
		score = newScore;

		std::string newText = "x" + std::to_string(score);
		scoreText.setString(newText);
	}

	void setplayerSpeed(float newSpeed) {
		playerSpeed = newSpeed;
	}

	void setPosition(sf::Vector2f newPos)
	{
		playerPosition = newPos;
		playerShape.setPosition(newPos);
		pBox.setPosition(newPos);

		largeFollowArea.setPosition(playerShape.getPosition());			//Follow circles stay around players
		smallFollowArea.setPosition(playerShape.getPosition());
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

	void setLargeFollowerRadius(float newRadius) {
		largeFollowArea.setRadius(newRadius);
		largeFollowArea.setOrigin(newRadius, newRadius);
	}

	void setMinLFR(float newRadius) {
		minLargeFolRad = newRadius;
		largeFollowArea.setRadius(newRadius);
	}

	void setMaxLFR(float newRadius) {
		maxLargeFolRad = newRadius;
	}

	void setLaserLength(int laserL) {
		laserLength = laserL;
	}

	void setLaserWidth(int laserW) {
		laserWidth = laserW;
	}

	void setWindowDims(sf::RenderWindow &window)
	{
		wLength = window.getSize().x;
		wHeight = window.getSize().y;
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

	sf::Color getPlayerColor() {
		return playerColor;
	}

	float getplayerSpeed() {
		return playerSpeed;
	}

	sf::Vector2f getPosition()
	{
		return playerPosition;
	}

	sf::Vector2f getGunPosition()
	{
		return playerShape.getGunPosition();
	}

	sf::FloatRect getPlayerBounds() {
		return pBox.getGlobalBounds();
	}

	sf::FloatRect getHeartBounds() {
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

	float getMinLFR() {
		return minLargeFolRad;
	}

	int getLaserLength()
	{
		return laserLength;
	}

	int getLaserWidth()
	{
		return laserWidth;
	}


	//METHODS OF CLASS PLAYER MANAGING SCORE
	void adjScore(int adj) {
		setScore(score + adj);
	}

	//METHODS RELATED TO MOVING PLAYER DIRECTLY
	void movePlayer(sf::Vector2f &mVect)								
	{
		playerShape.movePlayershape(mVect);		//function in playershape has default argument move set to 5
		pBox.move(mVect);
		playerPosition += mVect;

		largeFollowArea.setPosition(playerShape.getPosition());			//Follow circles stay around players
		smallFollowArea.setPosition(playerShape.getPosition());
	}

	void moveLogic(int dir, int towerCollision, sf::Vector2f const &towerPos,
		float towerRadius)
	{
		moveVect = sf::Vector2f(STILL, STILL);			//switch statement gives moveVect direction
		bool movingIntoTower = false;

		switch (dir)
		{
		case UP:
			moveVect += sf::Vector2f(0.f, -1.f);
			break;

		case LEFT:
			moveVect += sf::Vector2f(-1.f, 0.f);
			break;
		case DOWN:
			moveVect += sf::Vector2f(0.f, 1.f);
			break;

		case RIGHT:
			moveVect += sf::Vector2f(1.f, 0.f);
			break;
		}

		moveVect *= playerSpeed;							//gives moveVect its magnitude
		if (towerCollision > 0) {
			moveVect = towerCollisions(dir, towerCollision, towerPos, towerRadius);
		}
			
		movePlayer(moveVect);
		
	}


	float distanceFrom(sf::Vector2f &object1Pos, sf::Vector2f const &object2Pos)											//calculates vector distance from player or tower object
	{
		float xDist = abs(object1Pos.x - object2Pos.x);			//calculates x and y distances away follower is from player
		float yDist = abs(object1Pos.y - object2Pos.y);

		return pow(xDist * xDist + yDist * yDist, 0.5);							//calculates vector for distance from follower to player
	}

	float circle(float x, float radius) {				//formula for a circle!
		return sqrt(pow(radius,2) - pow(x, 2));
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
	sf::Vector2f towerCollisions(int dir, int towerNum, sf::Vector2f const &towerPos,
		float towerRadius) {

		float pushX = 0.f;
		float pushY = 0.f;
		sf::Vector2f dirVect = sf::Vector2f(1, 1);		

		switch (towerNum)				//We want to keep players from intersecting towers completely
		{									//So we set the hard barrier at their bounding box, pBox
		case 1:
			pushX = -pBox.getLocalBounds().width / 2.f;
			pushY = -pBox.getLocalBounds().height / 3.f;
			dirVect = sf::Vector2f(1, 1);
			break;

		case 2:
			pushX = pBox.getLocalBounds().width / 2.f;
			pushY = -pBox.getLocalBounds().height / 3.f;
			dirVect = sf::Vector2f(-1, 1);
			break;

		case 3:
			pushX = -pBox.getLocalBounds().width / 2.f;
			pushY = pBox.getLocalBounds().height / 3.f;
			dirVect = sf::Vector2f(1, -1);
			break;

		case 4:
			pushX = pBox.getLocalBounds().width / 2.f;
			pushY = pBox.getLocalBounds().height / 3.f;
			dirVect = sf::Vector2f(-1, -1);
			break;
		}

			sf::Vector2f pBoxAdj = sf::Vector2f(pushX, pushY);
			sf::Vector2f destination = sf::Vector2f(playerPosition + moveVect + pBoxAdj);
			bool movingIntoTower = distanceFrom(destination, towerPos) <= towerRadius;

			sf::Vector2f safeSpeed = moveVect;
			if (movingIntoTower) {
				sf::Vector2f relCoords = abs(towerPos - playerPosition);
				safeSpeed = avoidTower(dirVect, relCoords, towerNum);
			}
				
			return safeSpeed;
	}

	float invSpeedSq(float x, float y, float radius)
	{	//x and y are position floats, returns y_s^2
		//Using player position, ratio of x^2 and y^2 coords on quarter circle from {0, 100}
		//must equal ratio of speeds x_s^2 and y_s^2 on bounds {0, playerSpeed}

		float ratio = (pow(x, 2) / pow(y, 2));
		return pow(radius , 2) / (ratio + 1);
	}

	sf::Vector2f avoidTower(sf::Vector2f dir, sf::Vector2f relPos, int towerNum)
	{
		sf::Vector2f safeSpeed = sf::Vector2f(0, 0); 
		//safepos is speed that keeps player outside of towerbounds

		safeSpeed.y = invSpeedSq(relPos.x, relPos.y, playerSpeed);
		safeSpeed.x = pow(playerSpeed, 2) - safeSpeed.y;

		safeSpeed.x = sqrt(safeSpeed.x) * dir.x;
		safeSpeed.y = sqrt(safeSpeed.y) * dir.y;

		return safeSpeed;
	}


	//METHODS RELATING TO MANAGINE PLAYERS BULLETS
	void shoot(sf::Vector2i const &cursorPos)
	{
		static int temperShooting = 0;					//tempershooting will prevent players from shooting excessively

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{	
			if (temperShooting > 10)
			{
				addBullet(cursorPos);		//adds bullet to vector of active bullets
				temperShooting = 0;
			}
			else
				temperShooting--;
		}
		temperShooting++;			//variable is iterated continuosly to allow multiple shots
	}

	void addBullet(sf::Vector2i const &cursorPos) {
		activeBullets.push_back(Bullet(getGunPosition(), cursorPos));
	}

	void moveBullets() 
	{
		for (size_t i = 0; i < activeBullets.size(); i++) {
			activeBullets[i].moveBullet();
		}
	}

	void deleteBullet(int i) {
		activeBullets.erase(activeBullets.begin() + i);
	}

	void checkBulletInBounds(sf::RenderWindow &window) 
	{
		for (size_t i = 0; i < activeBullets.size(); i++) {
			if (activeBullets[i].isOutOBounds(window)) {
				deleteBullet(i);
			}
		}
	}


	//METHODS RELATING TO FOLLOWERS
	int shootFollower(sf::FloatRect const &followerBounds)
	{
		for (size_t i = 0; i < activeBullets.size(); i++) {
				if (activeBullets.at(i).getBulletGlobalBounds().intersects(			//checks to see if bullet intersects each follower
					followerBounds)) {

					int dmg = dmgFollower(i);
					adjScore(dmg);

					return dmg;
				}
		}
		return 0;
	}

	int dmgFollower(int i)
	{
		//bullet needs to know its strip
		int dmg = activeBullets[i].getStrip();
		int pen = activeBullets[i].getPen();
		pen--;

		if (pen < 1)
			activeBullets.erase(activeBullets.begin() + i);
		else
			activeBullets[i].setPen(pen);

		return dmg;

		//if the follower has health = 1, the follower is deleted
		//else its health is reduced
		//This should be performed in follower class, player only
		//needs to know if it shot a follower
	}

	void growLargeFollowArea(float growRate = 2.f)
	{	
		float newRad = largeFollowArea.getRadius() + growRate;

		if (maxLargeFolRad >= newRad)
			setLargeFollowerRadius(newRad);
	}


	//DRAWING METHODS OF CLASS PLAYER
	void drawPlayer(sf::RenderWindow &window)
	{
		window.draw(pBox);
		playerShape.drawPlayer(window);

		drawScore(window);
		drawHealthBar(window);
		drawBullets(window);
	}

	void drawHealthBar(sf::RenderWindow &window)
	{
		
		window.draw(healthBarRed);
		window.draw(healthBarGreen);
		window.draw(shieldBar);

		window.draw(largeFollowArea);
		window.draw(smallFollowArea);

		window.draw(healthText);
		//window.draw(dot);	//for troubleshooting
		//window.draw(box);
	}

	void drawBullets(sf::RenderWindow &window) 
	{
		for (size_t i = 0; i < activeBullets.size(); i++) {
			activeBullets[i].drawBullet(window);
		}
	}

	void drawScore(sf::RenderWindow &window) {
		window.draw(scoreText);
		scoreFigure.draw(window);

		window.draw(lifeText);
		lifeFigure.drawPlayer(window);
	}
};


