//PlayerObject.cpp class tethered to .h
//Defines all player object methods
//initializes player object static variables

#include "Player.h"

/******************************/
/*  DEFINE PLAYERSHAPE CLASS  */
/*****************************/

/*  CNTRL + M + O collapses all*/

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
sf::Vector2f PlayerShape::getPosition() const	{
		return heart.getPosition();
		//Function returns players position at his heart for collisions
	}

sf::Vector2f PlayerShape::getGunPosition() const						//Returns position of gun for shooting
	{
		return playerBody[GUN2].getPosition();
	}

const sf::FloatRect PlayerShape::getHeartBounds() const {
		return heart.getGlobalBounds();
	}

	//returns player's upper, lower, left and right bounds for boundry checking
float PlayerShape::getLeftBounds() const
	{
		return playerBody[ARMS].getPosition().x - armLength / 2;		
		//left and right bounds with respect to the players arms
	}

float PlayerShape::getUpperBounds() const						
{
		return head.getPosition().y - head.getRadius();			
		//the head is the highest point on the character, 
		//and its position is retrieved at its center
}

float PlayerShape::getRightBounds() const
	{
		return playerBody[ARMS].getPosition().x + armLength / 2;		
		//left and right bounds with respect to the players arms
	}

float PlayerShape::getLowerBounds() const
	{
		return playerBody[LEG1].getPosition().y + legLength;			
		//players lowerBounds with respect 
	}

sf::Color PlayerShape::getPlayerColor() const
	{
		return playerColor;
	}

sf::Color PlayerShape::getBodyColor() const {
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
void PlayerShape::drawPlayer(const std::shared_ptr<sf::RenderWindow>& window_ptr) {
	for (int i = 0; i < 6; i++) {
		window_ptr->draw(playerBody[i]);
	}
	window_ptr->draw(head);
	window_ptr->draw(heart);
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

//Editing values
bool Player::showBoxes = true;



/*  Forward Declarations  */
class Follower;
//class Tower;				
//forward declaration of class tower so player has access

	
/* Public Members  */

Player::Player(int pNumber, int startLives, float scale, int startHealth,
		int startMaxHealth, int startShield, int startMaxShield, float mSpeed, int startScore, float smallRadius,
		float maxLargeRadius, int laserL, int laserW, bool showBox) 
			: GameObj(ObjType::PLR)
	{

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
		sf::Vector2f startPos = sf::Vector2f(window_ptr->getSize().x / 2.f,
			window_ptr->getSize().y / 2.f);
		playerShape = PlayerShape(scale, playerColor, startPos);
		setPlayerBox(playerShape);

		setPosition(startPos);

		//initialize player spawn health and shield bars
		initHealthBar(startHealth, startMaxHealth);
		initShieldBar(startShield, startMaxShield);
		initHealthText();
		invulnerability = 30;

		//Initialize large and small follower areas
		smallFolRad = smallRadius;
		maxLargeFolRad = maxLargeRadius;
		minLargeFolRad = smallRadius + 20.f;
		initSmallFollowerRadius(smallRadius);
		initLargeFollowerRadius(minLargeFolRad);
		snap = false;

		//Initialize Laser attributes
		setLaserLength(laserL);
		setLaserWidth(laserW);
		//laser color = playercolor

		initScore();
	}


	/*  Init Methods  */
void Player::initHealthBar(int sHealth, int sMaxHealth)
	{
		maxHealth = sMaxHealth;
		
		float healthBarX = window_ptr->getSize().x / 2.f;
		float healthBarY = window_ptr->getSize().y / 40.f;

		float hLength = window_ptr->getSize().x / 5.f;
		float hHeight = window_ptr->getSize().y / 30.f;

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

void Player::initShieldBar(int sShield, int sMaxShield)
	{
		maxShield = sMaxShield;
		shieldRegen = 1;

		setShield(sShield);									//Player initiated with size 100 shield
		shieldBar.setOrigin(healthBarOrigin);
		shieldBar.setPosition(healthBarPosition);
		shieldBar.setFillColor(sf::Color::Blue);
	}

void Player::initHealthText()
	{
		// loads text for putting health in string format
		
		int textSize = 35;
		float thickness = 2.f;
		sf::Vector2f centerHealthBar = sf::Vector2f(-60.f, -8.f);		//vector adjusts health string text display for centering

		healthText.setFont(zsk::art::arial);
		healthText.setCharacterSize(textSize);
		healthText.setFillColor(zsk::art::primColor);
		healthText.setOutlineColor(zsk::art::secColor);
		healthText.setOutlineThickness(thickness);
		centerHealthText();
	}

void Player::initScore()
{
	int textSize = 45;

	scoreText.setFont(zsk::art::arial);
	scoreText.setCharacterSize(textSize);
	scoreText.setFillColor(zsk::art::secColor);

	sf::Vector2f pos = sf::Vector2f(window_ptr->getSize().x / 1.54f, 0.f);

	scoreText.setPosition(pos);
	setScore(0);


	if (playerNumber == 1) {
		sf::Vector2f adj = sf::Vector2f(-25.f, 25.f);
		scoreFigure.setPosition(pos + adj);

	}
}

void Player::initLives(int newLives)
{
		int textSize = 45;

		lifeText.setFont(zsk::art::arial);
		lifeText.setCharacterSize(textSize);
		lifeText.setFillColor(zsk::art::secColor);

		sf::Vector2f pos = sf::Vector2f(window_ptr->getSize().x / 1.33f, 0.f);

		lifeText.setPosition(pos);
		setLives(newLives);

		
		sf::Vector2f adj = sf::Vector2f(-24.f, 22.f);
		lifeFigure.setPosition(pos + adj);
}

void Player::initSmallFollowerRadius(float newRadius)
{
		setSmallFollowerRadius(newRadius);
		smallFollowArea.setOrigin(newRadius, newRadius);
		smallFollowArea.setPosition(pos);

		smallFollowArea.setOutlineThickness(areaOutline);
		smallFollowArea.setOutlineColor(sf::Color::Blue);
		smallFollowArea.setFillColor(sf::Color::Transparent);
}

void Player::initLargeFollowerRadius(float newRadius)
{
		largeFollowArea.setRadius(newRadius);
		largeFollowArea.setOrigin(newRadius, newRadius);
		largeFollowArea.setPosition(pos);

		largeFollowArea.setOutlineThickness(areaOutline);
		largeFollowArea.setOutlineColor(sf::Color::Green);
		largeFollowArea.setFillColor(sf::Color::Transparent);
}
	//End Init Methods


	/* SET METHODS */
void Player::setLives(const int newLives) {
		lives = newLives;

		std::string newText = "x" + std::to_string(lives);
		lifeText.setString(newText);
	}

void Player::setHealth(const int newHealth)
	{
		health = newHealth;
		float newLength = (health / maxHealth) * healthBarSize.x;

		sf::Vector2f  newSize = sf::Vector2f(newLength, healthBarSize.y);
		healthBarGreen.setSize(newSize);

		healthText.setString(std::to_string(static_cast<int>(health)) + "/"
			+ std::to_string(static_cast<int>(maxHealth)));				//updates graphics and text
		centerHealthText();

	}

void Player::setInvulnFrames(const int newFrames){
	invulnerability = newFrames;
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

void Player::setShield(const int newShield)
	{
		shield = newShield;
		float newLength = (shield / maxShield) * healthBarSize.x;

		sf::Vector2f  shieldBarSize = sf::Vector2f(newLength, healthBarSize.y);

		healthText.setString(std::to_string(static_cast<int>(shield)) + "/"
			+ std::to_string(static_cast<int>(maxShield)));				//updates graphics and text
		shieldBar.setSize(shieldBarSize);

	}

void Player::setShieldRegen(const int newRegen) {
	shieldRegen = newRegen;
}

void Player::setScore(const int newScore)
	{
		score = newScore;

		std::string newText = "x" + std::to_string(score);
		scoreText.setString(newText);

		//We may need to adjust spacing too
		sf::Vector2f adj = sf::Vector2f(22.f, 0);
		sf::Vector2f newTextPos = lifeText.getPosition() + adj;
		sf::Vector2f newFigPos = lifeFigure.getPosition() + adj;

		static int set = 0;
		bool adj_if = (score == 1000) ||
			(score == 100) ||
			(score == 10);

		if (adj_if) {
			set++;
		}
		else if (set > int(std::log10(score))) {
			adj = -adj;
			set--;
		}
		else
			adj = adj * 0;

		lifeText.move(adj);
		lifeFigure.movePlayershape(adj);
		
	}

void Player::setplayerSpeed(const float newSpeed) {
		playerSpeed = newSpeed;
	}

void Player::setPosition(const sf::Vector2f& newPos)
{
	pos = newPos;
	playerShape.setPosition(newPos);
	pBox.setPosition(newPos);

	//Follow circles stay around players
	largeFollowArea.setPosition(playerShape.getPosition());	
	smallFollowArea.setPosition(playerShape.getPosition());
}

void Player::setPlayerBox(const PlayerShape &shape)
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

void Player::setSmallFollowerRadius(const float newRadius) {
		smallFollowArea.setRadius(newRadius);
		smallFollowArea.setOrigin(newRadius, newRadius);
}

void Player::setLargeFollowerRadius(const float newRadius) {
		largeFollowArea.setRadius(newRadius);
		largeFollowArea.setOrigin(newRadius, newRadius);
	}

void Player::setMinLFR(const float newRadius) {
		minLargeFolRad = newRadius;
		largeFollowArea.setRadius(newRadius);
	}

void Player::setMaxLFR(const float newRadius) {
		maxLargeFolRad = newRadius;
	}

void Player::setLaserLength(const int laserL) {
		laserLength = laserL;
	}

void Player::setLaserWidth(const int laserW) {
		laserWidth = laserW;
	}


	/*  ACCESSOR METHODS  */
int Player::getPlayerNumber() const {
		return playerNumber;
}

int Player::getScore() const {
	return score;
}

int Player::getHealth() const {
	return health;
}

int Player::getShield() const {
	return shield;
}

const PlayerShape& Player::getPlayerShape() const {
	return playerShape;
}

sf::Color Player::getPlayerColor() const {
	return playerColor;
}

float Player::getplayerSpeed() const {
	return playerSpeed;
}

sf::Vector2f Player::getPosition() const {
	return pos;
}

sf::Vector2f Player::getGunPosition() const {
	return playerShape.getGunPosition();
}

sf::FloatRect Player::getPlayerBounds() const {
	return pBox.getGlobalBounds();
}

sf::FloatRect Player::getHeartBounds() const {
	return playerShape.getHeartBounds();
}

sf::FloatRect Player::getSmallFollowAreaBounds() const {
	return smallFollowArea.getGlobalBounds();
}

float Player::getSmallFollowAreaRadius() const {
		return smallFollowArea.getRadius();
}

sf::FloatRect Player::getLargeFollowAreaBounds() const {
		return largeFollowArea.getGlobalBounds();
}

float Player::getLargeFollowAreaRadius() const {
	return largeFollowArea.getRadius();
}

float Player::getMinLFR() const {
	return minLargeFolRad;
}

int Player::getLaserLength() const {
	return laserLength;
}

int Player::getLaserWidth() const {
	return laserWidth;
}

bool Player::isGameOver() const {
	return gameOver;
}


const sf::FloatRect Player::getGlobalBounds() const {
	return playerShape.getHeartBounds();
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
	pos += mVect;

	largeFollowArea.setPosition(playerShape.getPosition());			//Follow circles stay around players
	smallFollowArea.setPosition(playerShape.getPosition());
}

void Player::moveLogic(int dir)
{
	/* Check for tower collisions */
	int towerCollision = 0;
	sf::Vector2f towerPos;
	float towerRadius;

	for (const auto& col : collisions) {
		if (col->getType() == ObjType::TOW) {
			Tower* t = dynamic_cast<Tower*>(col);
			towerCollision = t->getTowerNum();
			towerPos = t->getPosition();
			towerRadius = t->getTowerRadius();
		}
	}

	
	moveVect = sf::Vector2f(STILL, STILL);

	//switch statement gives moveVect direction
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

	moveVect *= playerSpeed;		//gives moveVect its magnitude
	if (towerCollision > 0) {
		moveVect = towerCollisions(dir, towerCollision, towerPos, towerRadius);
	}

	movePlayer(moveVect);

}


double Player::circle(float x, float radius) {				//formula for a circle!
	return sqrt(pow(radius, 2) - pow(x, 2));
}


	//METHODS RELATED TO MANAGING A PLAYER'S HEALTH
void Player::takeDamage(int dmg)
{
	if (invulnerability > 0) {
		invulnerability--;
		//lose a frame of invulnerability every tick,
		//until it goes away, then apply damage
	}
	else {

		if (shield > 0) {
			int newShield = std::max(shield - dmg, 0);
			setShield(newShield);
		}
		else if (health > 0) {
			int newHealth = std::max(health - dmg, 0);
			setHealth(newHealth);
		}
		else {
			loseLife();
		}
	}
	
}

void Player::regenShield()
{
	static int counter = 0;

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

	switch (towerNum)		//We want to keep players from intersecting towers completely
	{						//So we set the hard barrier at their bounding box, pBox
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
	sf::Vector2f destination = sf::Vector2f(pos + moveVect + pBoxAdj);
	bool movingIntoTower = zsk::distanceFrom(destination, towerPos) <= towerRadius;

	sf::Vector2f safeSpeed = moveVect;
	if (movingIntoTower) {
		sf::Vector2f relCoords = abs(towerPos - pos);
		safeSpeed = avoidTower(dirVect, relCoords, towerNum);
	}

	return safeSpeed;
}

double Player::invSpeedSq(float x, float y, float radius)
{	//x and y are position floats, returns y_s^2
	//Using player position, ratio of x^2 and y^2 coords on quarter circle from {0, 100}
	//must equal ratio of speeds x_s^2 and y_s^2 on bounds {0, playerSpeed}

	float ratio = static_cast<float>((pow(x, 2) / pow(y, 2)));
	return pow(radius, 2) / (ratio + 1);
}

sf::Vector2f Player::avoidTower(sf::Vector2f dir, sf::Vector2f relPos, int towerNum)
{
	sf::Vector2f safeSpeed = sf::Vector2f(0, 0);
	//safepos is speed that keeps player outside of towerbounds

	safeSpeed.y = static_cast<float>(invSpeedSq(relPos.x, relPos.y, playerSpeed));
	safeSpeed.x = static_cast<float>(pow(playerSpeed, 2)) - safeSpeed.y;

	safeSpeed.x = sqrt(safeSpeed.x) * dir.x;
	safeSpeed.y = sqrt(safeSpeed.y) * dir.y;

	return safeSpeed;
}


//METHODS RELATING TO MANAGINE PLAYERS BULLETS
void Player::shoot()
{
	static int temperShooting = 0;					
	//tempershooting will prevent players from shooting excessively

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (temperShooting > 10)
		{
			//adds bullet to vector of active bullets
			addBullet();		
			temperShooting = 0;
		}
		else
			temperShooting--;
	}
	temperShooting++;			
	//variable is iterated continuosly to allow multiple shots
}

void Player::addBullet() {
	std::shared_ptr<Bullet> b(new Bullet(getGunPosition()));
	activeBullets.push_front(b);
}

void Player::moveBullets() {
	for (auto& bullet: activeBullets) {
		bullet->moveBullet();
	}
} 

void Player::deleteBullet(std::list<std::shared_ptr<Bullet>>::iterator& b) 
{
	//Remove the bullet from our list, after this function
	//the bullet should still be refereneced by a shared_ptr in
	//the objs vector

	printf("delete bullet: %d, at mem loc: %p\n", b->get()->getID(), b._Ptr);
	activeBullets.erase(b);
}

void Player::checkBulletInBounds()
{
	for (auto b = activeBullets.begin(); b != activeBullets.end();) {
		if (b->get()->isOutOBounds()) {
			cout << "Bullet OOB\n";
			activeBullets.erase(b);
		}
		++b;
	}
}


//METHODS RELATING TO FOLLOWERS
int Player::shootFollower(sf::FloatRect const &followerBounds)
{
	/*
		Shoot follower is currently obselete, collisions are 
		handled generally in gamestate class.  Provided numerics may be
		calculated here.
	*/

	/*
		
		for (size_t i = 0; i < activeBullets.size(); i++) {
		if ( .getGlobalBounds().intersects(
			followerBounds)) {
			//checks to see if bullet intersects each follower

			int dmg = dmgFollower(i);
			adjScore(dmg);

			return dmg;
		}
	}
	*/

	return 0;
}

int Player::dmgFollower(int i)
{
	/*
		Use player's bullet list to deal damage 
		to followers.

		Recall List does not allow access operations
		in constant time, pass a ptr to the bullet
		obj instead of the index.
	*/

	/*

	//bullet needs to know its strip
	int dmg = activeBullets[i].getStrip();
	int pen = activeBullets[i].getPen();
	pen--;

	if (pen < 1)
		activeBullets.erase(activeBullets.begin() + i);
	else
		activeBullets[i].setPen(pen);

	*/
	int dmg = 0;
	return dmg;

	//if the follower has health = 1, the follower is deleted
	//else its health is reduced
	//This should be performed in follower class, player only
	//needs to know if it shot a follower
}

void Player::growLargeFollowArea(bool grow, float growRate)
{
	/*
		Large follower area grows upon holding right
		click, then snaps back when the player releases
		the button; the small followerRadius also needs to 
		snap in for s a short bit handled by bool snap
	*/

	//potential issues with snap being false with mutiple players

	if (grow) 
	{
		float newRad = largeFollowArea.getRadius() + growRate;

		if (maxLargeFolRad >= newRad) {
			setLargeFollowerRadius(newRad);
		}
		if (newRad >= 0.8 * maxLargeFolRad) {
			snap = true;
		}
			
	}
	else if (snap)
	{
		
		float newRad = 0; // smallFollowArea.getRadius() * 0.25;
		setSmallFollowerRadius(newRad);
		setLargeFollowerRadius(newRad);
		snap = false;
		
	} 
	else {

		float newRad = largeFollowArea.getRadius() + growRate;

		if (minLargeFolRad >= newRad) {
			setLargeFollowerRadius(newRad);
		}
		else {
			setLargeFollowerRadius(minLargeFolRad);
		}
	}
		
	float newSmallRad = smallFollowArea.getRadius() + 0.5f * growRate;
	
	if (smallFolRad >= newSmallRad) {
		setSmallFollowerRadius(newSmallRad);
	}

}


/*****************************/
/*			UPDATE			*/
STATE Player::update()
{
	//move player and handle collisions
	movePlayerLogic();

	//shooting mechanics
	shootingMechanics();

	//Misc Mechanics
		// - growing LFA
		// - regen Shield
	miscMechanics();

	return STATE::GAME;
}

//Move PLayer Logic
void Player::movePlayerLogic()
{
	/*
		- Determines player direction via keypressed event 
		- Considers if the player is in bounds and can move in
		that direction
		- passes the direction of travel to moveLogic if
		the player is not "still"
	*/

	Direction dir = STILL;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || 
			sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (playerShape.getUpperBounds() > 0)
			dir = UP;
	}
	//move player left if not at left bounds
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (playerShape.getLeftBounds() > 0)
			dir = LEFT;
	}
	//down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (playerShape.getLowerBounds() < window_ptr->getSize().y)
			dir = DOWN;
	}
	//and right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (playerShape.getRightBounds() < window_ptr->getSize().x)
			dir = RIGHT;
	}

	//move player given direction
	if (dir != STILL)
		moveLogic(dir);
}

//Shooting Mechanics
void Player::shootingMechanics()
{
	shoot();
	moveBullets();
	checkBulletInBounds();
}

//Miscellaneous Mechanics
void Player::miscMechanics()
{
	//Grow follow area
	growLargeFollowArea(sf::Mouse::isButtonPressed(sf::Mouse::Right));

	//regen shield
	regenShield();
}



/***************************/

//DRAWING METHODS OF CLASS PLAYER
void Player::drawPlayer()
{
	window_ptr->draw(pBox);
	playerShape.drawPlayer(window_ptr);

	drawScore();
	drawHealthBar();
	drawBullets();
}

void Player::drawHealthBar()
{

	window_ptr->draw(healthBarRed);
	window_ptr->draw(healthBarGreen);
	window_ptr->draw(shieldBar);

	window_ptr->draw(largeFollowArea);
	window_ptr->draw(smallFollowArea);

	window_ptr->draw(healthText);
	//window.draw(dot);	//for troubleshooting
	//window.draw(box);
}

void Player::drawBullets()
{
	for (auto b = activeBullets.begin(); b != activeBullets.end();) {
		b->get()->drawBullet();
		++b;
	}
}

void Player::drawScore() {
	window_ptr->draw(scoreText);
	scoreFigure.draw(window_ptr);

	window_ptr->draw(lifeText);
	lifeFigure.drawPlayer(window_ptr);
}


//COPY CONSTRUCTOR
Player::Player(const Player& rhs)
	: GameObj(rhs)
{
	this->playerNumber = rhs.playerNumber;
	this->score = rhs.score;
	this->playerColor = rhs.playerColor;
	this->health = rhs.health;
	this->maxHealth = rhs.maxHealth;
	this->lives = rhs.lives;
	this->gameOver = rhs.gameOver;
	this->shield = rhs.shield;
	this->maxShield = rhs.maxShield;
	this->shieldRegen = rhs.shieldRegen;
	this->invulnerability = rhs.invulnerability;
	this->healthBarSize = rhs.healthBarSize;
	this->healthBarPosition = rhs.healthBarPosition;
	this->healthBarOrigin = rhs.healthBarOrigin;
	this->healthBarRed = rhs.healthBarRed;
	this->healthBarGreen = rhs.healthBarGreen;
	this->shieldBar = rhs.shieldBar;
	this->healthText = rhs.healthText;
	this->lifeText = rhs.lifeText;
	this->scoreText = rhs.scoreText;
	this->playerSpeed = rhs.playerSpeed;
	this->playerDirection = rhs.playerDirection;
	this->moveVect = rhs.moveVect;
	this->playerShape = rhs.playerShape;
	this->pBox = rhs.pBox;
	this->activeBullets = rhs.activeBullets;
	this->largeFollowArea = rhs.largeFollowArea;
	this->smallFollowArea = rhs.smallFollowArea;
	this->smallFolRad = rhs.smallFolRad;
	this->minLargeFolRad = rhs.minLargeFolRad;
	this->maxLargeFolRad = rhs.maxLargeFolRad;
	this->snap = rhs.snap;
	this->laserLength = rhs.laserLength;
	this->laserWidth = rhs.laserWidth;
}


