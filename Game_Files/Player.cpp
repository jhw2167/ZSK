//PlayerObject.cpp class tethered to .h
//Defines all player object methods
//initializes player object static variables

#include "Player.h"

/******************************/
/*  DEFINE PLAYERSHAPE CLASS  */
/*****************************/

	/*	Private Members	*/

//End Private members

	/*  Public Members	*/
PlayerShape::PlayerShape(float scale, sf::Color pColor,
		sf::Vector2f startPos) 
	{
		setPlayerShape(scale);
		setColor(pColor);
		setPosition(startPos);
	}

	/*	PlayerShape Setters	*/
void PlayerShape::setPosition(sf::Vector2f const &newPos)
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

void PlayerShape::setPlayerShape(float scale)
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

void PlayerShape::setColor(sf::Color &pColor, sf::Color bColor)
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

	/*	PlayerShape Accessors	*/
sf::Vector2f PlayerShape::getPosition()	{
		return heart.getPosition();
		//Function returns players position at his heart for collisions
	}

sf::Vector2f PlayerShape::getGunPosition()						//Returns position of gun for shooting
	{
		return playerBody[GUN2].getPosition();
	}

sf::FloatRect PlayerShape::getHeartBounds()
	{
		return heart.getGlobalBounds();
	}

	//returns player's upper, lower, left and right bounds for boundry checking
float PlayerShape::getLeftBounds()
	{
		return playerBody[ARMS].getPosition().x - armLength / 2;		
		//left and right bounds with respect to the players arms
	}

float PlayerShape::getUpperBounds()						
	{
		return head.getPosition().y - head.getRadius();			
		//the head is the highest point on the character, 
		//and its position is retrieved at its center
	}

float PlayerShape::getRightBounds()
	{
		return playerBody[ARMS].getPosition().x + armLength / 2;		
		//left and right bounds with respect to the players arms
	}

float PlayerShape::getLowerBounds()
	{
		return playerBody[LEG1].getPosition().y + legLength;			
		//players lowerBounds with respect 
	}

sf::Color PlayerShape::getPlayerColor()
	{
		return playerColor;
	}

sf::Color PlayerShape::getBodyColor() {
		return bodyColor;
	}

	//MOVE
void PlayerShape::movePlayershape(sf::Vector2f &moveVect)
	{
		for (int i = 0; i < 6; i++)
		{
			playerBody[i].move(moveVect);
		}

		head.move(moveVect);
		heart.move(moveVect);
	}


	//DRAW FUNCTIONS
void PlayerShape::drawPlayer(sf::RenderWindow &window)
	{

		for (int i = 0; i < 6; i++)
		{
			window.draw(playerBody[i]);
		}

		window.draw(head);
		window.draw(heart);

	}


//END CLASS PLAYERSHAPE




/******************************/
/*  DEFINE PLAYER CLASS  */
/*****************************/


	/*  Static Members of Player Class  */

float Player::areaOutline = 4.f;
sf::Color Player::pColors[] = { sf::Color::Red, sf::Color::Blue,
	sf::Color::Green, sf::Color::Yellow };

FollowerShape Player::scoreFigure = FollowerShape(sf::Color::Black, 3.f);
PlayerShape Player::lifeFigure = PlayerShape(2.5f);

sf::Font Player::arial;



/*  Forward Declarations  */
class Follower;
class Tower;				//forward declaration of class tower so player has access

/*  Private Members  */

//End Private

	
/* Public Members  */

Player::Player(sf::RenderWindow &window, int pNumber, int startLives, float scale, float startHealth,
		float startMaxHealth, float startShield, float startMaxShield, float mSpeed, int startScore, float smallRadius,
		float maxLargeRadius, int laserL, int laserW, bool showBox)
	{
		//Init Window Dims
		setWindowDims(window);

		//Initialize basic player components
		playerNumber = pNumber;
		playerColor = pColors[pNumber - 1];
		score = startScore;
		playerSpeed = mSpeed;
		initLives(startLives);
		gameOver = false;

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


	/*  Init Methods  */
void Player::initHealthBar(sf::RenderWindow &window, float sHealth, float sMaxHealth)
	{
		maxHealth = sMaxHealth;
		
		float healthBarX = window.getSize().x / 2.f;
		float healthBarY = window.getSize().y / 40.f;

		float hLength = window.getSize().x / 5.f;
		float hHeight = window.getSize().y / 30.f;

		healthBarPosition = sf::Vector2f(healthBarX, healthBarY);
		healthBarSize = sf::Vector2f(hLength, hHeight);
		healthBarOrigin = healthBarSize / 2.f;

		healthBarRed.setSize(healthBarSize);			//initiates red (background) health bar
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

void Player::initShieldBar(sf::RenderWindow &window, float sShield, float sMaxShield)
	{
		maxShield = sMaxShield;
		shieldRegen = 1.f;

		setShield(sShield);									//Player initiated with size 100 shield
		shieldBar.setOrigin(healthBarOrigin);
		shieldBar.setPosition(healthBarPosition);
		shieldBar.setFillColor(sf::Color::Blue);
	}

void Player::initHealthText()
	{
		// loads text for putting health in string format
		if (!arial.loadFromFile("Fonts/arial.ttf")) 	//loads font to use for text drawing
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

void Player::initScore()
	{
		int textSize = 45;

		scoreText.setFont(arial);
		scoreText.setCharacterSize(textSize);
		scoreText.setFillColor(sf::Color::Black);

		sf::Vector2f pos = sf::Vector2f(wLength / 1.54f, 0.f);

		scoreText.setPosition(pos);
		setScore(0.f);


		if (playerNumber == 1) {
			sf::Vector2f adj = sf::Vector2f(-25.f, 25.f);
			scoreFigure.setPosition(pos + adj);

		}
	}

void Player::initLives(int newLives)
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

void Player::initSmallFollowerRadius(float newRadius)
{
		setSmallFollowerRadius(newRadius);
		smallFollowArea.setOrigin(newRadius, newRadius);
		smallFollowArea.setPosition(playerPosition);

		smallFollowArea.setOutlineThickness(areaOutline);
		smallFollowArea.setOutlineColor(sf::Color::Blue);
		smallFollowArea.setFillColor(sf::Color::Transparent);
}

void Player::initLargeFollowerRadius(float newRadius)
{
		largeFollowArea.setRadius(newRadius);
		largeFollowArea.setOrigin(newRadius, newRadius);
		largeFollowArea.setPosition(playerPosition);

		largeFollowArea.setOutlineThickness(areaOutline);
		largeFollowArea.setOutlineColor(sf::Color::Green);
		largeFollowArea.setFillColor(sf::Color::Transparent);
}
	//End Init Methods


	/* SET METHODS */
void Player::setLives(int newLives) {
		lives = newLives;

		std::string newText = "x" + std::to_string(lives);
		lifeText.setString(newText);
	}

void Player::setHealth(float newHealth)
	{
		health = newHealth;
		float newLength = (health / maxHealth) * healthBarSize.x;

		sf::Vector2f  newSize = sf::Vector2f(newLength, healthBarSize.y);
		healthBarGreen.setSize(newSize);

		healthText.setString(std::to_string(static_cast<int>(health)) + "/"
			+ std::to_string(static_cast<int>(maxHealth)));				//updates graphics and text
		centerHealthText();

	}

void Player::centerHealthText()
	{
		sf::Vector2f textDims = sf::Vector2f(healthText.getLocalBounds().width,
			healthText.getLocalBounds().height);
		sf::Vector2f centerText = sf::Vector2f(0, -6.f);	//requires bit of adj to center text 

		if (health < 10)				//more adj so it looks nice
			centerText.x += 15.f;
		else if (health < 100)
			centerText.x += 10.f;

		healthText.setOrigin(textDims / 2.f);
		healthText.setPosition(healthBarPosition + centerText);
	}

void Player::setShield(float newShield)
	{
		shield = newShield;
		float newLength = (shield / maxShield) * healthBarSize.x;

		sf::Vector2f  shieldBarSize = sf::Vector2f(newLength, healthBarSize.y);

		healthText.setString(std::to_string(static_cast<int>(shield)) + "/"
			+ std::to_string(static_cast<int>(maxShield)));				//updates graphics and text
		shieldBar.setSize(shieldBarSize);

	}

void Player::setShieldRegen(float newRegen) {
	shieldRegen = newRegen;
}

void Player::setScore(int newScore)
	{
		score = newScore;

		std::string newText = "x" + std::to_string(score);
		scoreText.setString(newText);
	}

void Player::setplayerSpeed(float newSpeed) {
		playerSpeed = newSpeed;
	}

void Player::setPosition(sf::Vector2f newPos)
	{
		playerPosition = newPos;
		playerShape.setPosition(newPos);
		pBox.setPosition(newPos);

		largeFollowArea.setPosition(playerShape.getPosition());			//Follow circles stay around players
		smallFollowArea.setPosition(playerShape.getPosition());
	}

void Player::setPlayerBox(PlayerShape &shape, bool showBoxes)
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

void Player::setSmallFollowerRadius(float newRadius)
	{
		smallFollowArea.setRadius(newRadius);
	}

void Player::setLargeFollowerRadius(float newRadius) {
		largeFollowArea.setRadius(newRadius);
		largeFollowArea.setOrigin(newRadius, newRadius);
	}

void Player::setMinLFR(float newRadius) {
		minLargeFolRad = newRadius;
		largeFollowArea.setRadius(newRadius);
	}

void Player::setMaxLFR(float newRadius) {
		maxLargeFolRad = newRadius;
	}

void Player::setLaserLength(int laserL) {
		laserLength = laserL;
	}

void Player::setLaserWidth(int laserW) {
		laserWidth = laserW;
	}

void Player::setWindowDims(sf::RenderWindow &window)
	{
		wLength = window.getSize().x;
		wHeight = window.getSize().y;
	}


	/*  ACCESSOR METHODS  */
int Player::getPlayerNumber() {
		return playerNumber;
}

int Player::getScore() {
	return score;
}

float Player::getHealth()
{
	return health;
}

float Player::getShield() {
	return shield;
}

PlayerShape Player::getPlayerShape() {
	return playerShape;
}

sf::Color Player::getPlayerColor() {
	return playerColor;
}

float Player::getplayerSpeed() {
	return playerSpeed;
}

sf::Vector2f Player::getPosition() {
	return playerPosition;
}

sf::Vector2f Player::getGunPosition() {
	return playerShape.getGunPosition();
}

sf::FloatRect Player::getPlayerBounds() {
	return pBox.getGlobalBounds();
}

sf::FloatRect Player::getHeartBounds() {
	return playerShape.getHeartBounds();
}

sf::FloatRect Player::getSmallFollowAreaBounds() {
	return smallFollowArea.getGlobalBounds();
}

float Player::getSmallFollowAreaRadius() {
		return smallFollowArea.getRadius();
}

sf::FloatRect Player::getLargeFollowAreaBounds() {
		return largeFollowArea.getGlobalBounds();
}

float Player::getLargeFollowAreaRadius() {
	return largeFollowArea.getRadius();
}

float Player::getMinLFR() {
	return minLargeFolRad;
}

int Player::getLaserLength() {
	return laserLength;
}

int Player::getLaserWidth() {
	return laserWidth;
}

bool Player::isGameOver() {
	return gameOver;
}


	//METHODS OF CLASS PLAYER MANAGING SCORE
void Player::adjScore(int adj) {
	setScore(score + adj);
}


	//METHODS RELATED TO MOVING PLAYER DIRECTLY
void Player::movePlayer(sf::Vector2f &mVect)
{
	playerShape.movePlayershape(mVect);		//function in playershape has default argument move set to 5
	pBox.move(mVect);
	playerPosition += mVect;

	largeFollowArea.setPosition(playerShape.getPosition());			//Follow circles stay around players
	smallFollowArea.setPosition(playerShape.getPosition());
}

void Player::moveLogic(int dir, int towerCollision, sf::Vector2f const &towerPos,
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


float Player::distanceFrom(sf::Vector2f &object1Pos, sf::Vector2f const &object2Pos)											//calculates vector distance from player or tower object
{
	float xDist = abs(object1Pos.x - object2Pos.x);			//calculates x and y distances away follower is from player
	float yDist = abs(object1Pos.y - object2Pos.y);

	return pow(xDist * xDist + yDist * yDist, 0.5);							//calculates vector for distance from follower to player
}

float Player::circle(float x, float radius) {				//formula for a circle!
	return sqrt(pow(radius, 2) - pow(x, 2));
}


	//METHODS RELATED TO MANAGING A PLAYER'S HEALTH
void Player::takeDamage(float dmg)
{
	//dmg is a POSITIVE value inherently, i.e to reduce health pass
	//positive damage values
	float combinedHealth = health + shield - dmg;

	float newShield = std::min(std::max(combinedHealth - maxHealth, 0.f), maxShield);
	float newHealth = std::max(std::min(combinedHealth - newShield, maxHealth), -1.f);
	//Sets new health and shield values with max and min functions

	if (combinedHealth > maxHealth) {
		setShield(newShield);
	}	
	else if (combinedHealth >= 0) 
	{

		static int setOnce = true;
		if (setOnce) {
			setShield(0);
			setOnce = false;
		}
		
		setHealth(newHealth);
	}
	else if (combinedHealth <= 0) {
		loseLife();
	}

}

void Player::regenShield()
{
	static short counter = 0;

	if (shield > 0 && shield < maxShield) {
		counter++;

		if (counter >= 60) {
			setShield(shield + shieldRegen);
			counter = 0;
		}
	}

}

void Player::loseLife()
{
	if (lives > 0)
	{
		setLives(--lives);
		setHealth(maxHealth);
		setShield(maxShield);
	}
	else {
		gameOver = true;
	}
		
}


//METHODS RELATING TO PLAYERS INERACTION WITH TOWERS
sf::Vector2f Player::towerCollisions(int dir, int towerNum, sf::Vector2f const &towerPos,
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

float Player::invSpeedSq(float x, float y, float radius)
{	//x and y are position floats, returns y_s^2
	//Using player position, ratio of x^2 and y^2 coords on quarter circle from {0, 100}
	//must equal ratio of speeds x_s^2 and y_s^2 on bounds {0, playerSpeed}

	float ratio = (pow(x, 2) / pow(y, 2));
	return pow(radius, 2) / (ratio + 1);
}

sf::Vector2f Player::avoidTower(sf::Vector2f dir, sf::Vector2f relPos, int towerNum)
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
void Player::shoot(sf::Vector2i const &cursorPos)
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

void Player::addBullet(sf::Vector2i const &cursorPos) {
	activeBullets.push_back(Bullet(getGunPosition(), cursorPos));
}

void Player::moveBullets()
{
	for (size_t i = 0; i < activeBullets.size(); i++) {
		activeBullets[i].moveBullet();
	}
}

void Player::deleteBullet(int i) {
	activeBullets.erase(activeBullets.begin() + i);
}

void Player::checkBulletInBounds(sf::RenderWindow &window)
{
	for (size_t i = 0; i < activeBullets.size(); i++) {
		if (activeBullets[i].isOutOBounds(window)) {
			deleteBullet(i);
		}
	}
}


//METHODS RELATING TO FOLLOWERS
int Player::shootFollower(sf::FloatRect const &followerBounds)
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

int Player::dmgFollower(int i)
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

void Player::growLargeFollowArea(float growRate)
{
	float newRad = largeFollowArea.getRadius() + growRate;

	if (maxLargeFolRad >= newRad)
		setLargeFollowerRadius(newRad);
}


//DRAWING METHODS OF CLASS PLAYER
void Player::drawPlayer(sf::RenderWindow &window)
{
	window.draw(pBox);
	playerShape.drawPlayer(window);

	drawScore(window);
	drawHealthBar(window);
	drawBullets(window);
}

void Player::drawHealthBar(sf::RenderWindow &window)
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

void Player::drawBullets(sf::RenderWindow &window)
{
	for (size_t i = 0; i < activeBullets.size(); i++) {
		activeBullets[i].drawBullet(window);
	}
}

void Player::drawScore(sf::RenderWindow &window) {
	window.draw(scoreText);
	scoreFigure.draw(window);

	window.draw(lifeText);
	lifeFigure.drawPlayer(window);
}


