//Implementation of Tower.h class

#include "Tower.h"

	/*  Init Static variables  */

	/*  Public Methods  */
	

	/*  Constructors  */
Tower::Tower(sf::RenderWindow const &window, const int tNumber)
//Constructs minimal tower objcet
{
	initVars(tNumber, window);
	initLaserTexture();
	initTowerShape(window);
	setPosition(window, tNumber);
	initLaser();
}
//End Constructors


	/*  Init Methods  */
void Tower::initVars(const int tNumber, sf::RenderWindow const &window) {
	win_ptr = &window;
	towerNumber = tNumber;
	towerOwnedBy = NOTOWNED;
	isFiring = false;
}

void Tower::initTowerShape(sf::RenderWindow const &window)
{
	//setRadius and origin at center
	float tRadius = std::min(window.getSize().x, window.getSize().y) / 8.f;
	setRadius(tRadius);
	
	//fill color
	towerShape.setFillColor(zsk::art::secColor);

	//similiarly set vars for towerOutline
	if (towerNumber > 0) {
		towerOutline.setFillColor(zsk::art::playerColors.at(towerNumber - 1));
	}
	

	float thickness = 4.f;
	towerOutline.setOutlineThickness(thickness);
	towerOutline.setOutlineColor(zsk::art::secColor);
}

void Tower::initLaserTexture()
{
	if (!lTexture.loadFromFile("Art/Sprites/laser.png")) {
		cout << "Error loading laser textures from images\n";
	}

	//set laser texture onto laser sprite
	lTexture.setSmooth(true);
	laser.setTexture(lTexture);
	if (towerNumber > 0) {
		changeLaserColor(towerNumber - 1);
	}

	//set laser aspects
	laser.setOrigin(0, laser.getLocalBounds().height / 2.f);
}

void Tower::initLaser()
{
	/*
		Pulls a png laser image from library, pastes it to a texture,
		the texture in turn applies to the sprite
	*/
	
	//set laser rotation
	sf::Vector2f lPos = laser.getPosition();

	float winL = win_ptr->getSize().x;
	float winH = win_ptr->getSize().y;
	sf::Vector2f center = sf::Vector2f(winL / 2.f, winH / 2.f);

	float l1 = laser.getLocalBounds().width;
	float l2 = zsk::distanceFrom(lPos, center);
	float l3 = zsk::distanceFrom(lPos + sf::Vector2f(l1,0), center);

	//L1 is simply length of the laser
	//L2 is distance between laser origin (at tower) and map center
	//L3 is distance between the "far" laser point and the map center

	double radAngle = zsk::lawCosINV(l1, l2, l3);
	double degAngle = zsk::radsToDegs(radAngle);

	if (lPos.y < winH / 2.f)
		laser.setRotation(degAngle);
	else
		laser.setRotation(-degAngle);
	//set negative angle if we are below the origin
}
//End Inits


	/*  Setter methods  */
void Tower::setRadius(float tRadius) {
	
	towerRadius = tRadius;

	towerShape.setRadius(towerRadius);
	towerShape.setOrigin(towerRadius, towerRadius);

	const float newRad = 1.06 * tRadius;
	towerOutline.setRadius(newRad);
	towerOutline.setOrigin(newRad, newRad);
}

void Tower::setPosition(sf::RenderWindow const &window, int tNumber)
{
	//sets tower position to one of the four corners
	towerNumber = tNumber;

	//tower's number denotation determines its position
	sf::Vector2f newPos = sf::Vector2f(0, 0);
	sf::Vector2f laserPos = sf::Vector2f(0, 0);

	switch (towerNumber) {
	case 1:
		//do nothing
		laserPos = sf::Vector2f(towerRadius / 2.f, towerRadius / 2.f);
		break;
	case 2:
		newPos = sf::Vector2f(window.getSize().x, 0);
		laserPos = sf::Vector2f(-towerRadius / 2.f, towerRadius / 2.f);
		break;
	case 3:
		newPos = sf::Vector2f(0, window.getSize().y);
		laserPos = sf::Vector2f(towerRadius / 2.f, -towerRadius / 2.f);
		break;
	case 4:
		newPos = sf::Vector2f(window.getSize().x, window.getSize().y);
		laserPos = sf::Vector2f(-towerRadius / 2.f, -towerRadius / 2.f);
		break;
	case 0:														
		//case zero tower not intented to be shown or utilized, 
		//its instantiation helps with mechanics such as checking tower collisions
		newPos = sf::Vector2f(-100.f, -100.f);					
		laserPos = sf::Vector2f(-100.f, -100.f);
		break;
	}
	towerShape.setPosition(newPos);
	towerOutline.setPosition(newPos);
	laser.setPosition(laserPos + newPos);

	towerPosition = newPos;
	//sets towerPosition var equal to placement of circle shape for easy access
}
//End setters


	/*  Accessor Methods  */
sf::FloatRect Tower::getTowerGlobalBounds() {
	return towerShape.getGlobalBounds();
}

sf::Vector2f Tower::getPosition() {
	return towerPosition;
}

float Tower::getTowerRadius() {
	return towerRadius;
}

sf::CircleShape Tower::getTowerShape() {
	return towerShape;
}

int Tower::getTowerOwnership() {
	return towerOwnedBy;
}

bool Tower::isLaserFiring() const {
	return isFiring;
}
//End Accessor Methods


//TOWER OWNERSHIP METHODS
void Tower::changeOwner(int newOwner)
{
	/*
		adjust tower ownership and makes changes
		as necesary
	*/
	towerOwnedBy = newOwner;
	changeLaserColor(newOwner-1);
}


	/*  Functions  */

//TOWER COLLISIONS
bool Tower::checkTowerCollision(Player &player)
{
	bool collision = player.getPlayerBounds().intersects(
		towerShape.getGlobalBounds());

	return collision;
}

//if (distanceFrom(playerPos) <= towerRadius)
	//return true;


//TOWER MECHANICS


//LASER BASED METHODS
void Tower::changeLaserColor(const int newOwner)
{
	/*
		Load base laser image and change the color to the color
		corresponding to the player number of the new owner
	*/

	sf::Image img;
	img.loadFromFile("Art/Sprites/laser.png");

	sf::Vector2u s = img.getSize();
	sf::Color oldColor = img.getPixel(s.x / 2.f, s.y / 2.f);
	sf::Color newColor = zsk::art::playerColors.at(newOwner);

	zsk::art::changePixelRange(img, oldColor, newColor);

	lTexture.loadFromImage(img);
	laser.setTexture(lTexture);
	//laser color now changed
}


//TOWER DRAW METHODS
void Tower::drawTowers(sf::RenderWindow &window) 
{
	window.draw(towerOutline);
	window.draw(towerShape);
	
	if (isFiring) {
		//cout << "Get texture in draw: " << laser.getTexture() << endl;
		//getchar();
		window.draw(laser);
	}
		
	
}

	/*  Destructor  */

Tower::~Tower() {
}


/*  Copy Constructor  */

Tower::Tower(const Tower & rhs)
{
	this->isFiring = rhs.isFiring;
	this->lTexture.loadFromImage(rhs.lTexture.copyToImage());
	//copy texture by building a new one from an image
	this->laser = rhs.laser;
	this->laser.setTexture(this->lTexture);

	//tower vars
	this->towerNumber = rhs.towerNumber;
	this->towerRadius = rhs.towerRadius;
	this->towerOutline = rhs.towerOutline;
	this->towerOwnedBy = rhs.towerOwnedBy;
	this->towerPosition = rhs.towerPosition;
	this->towerShape = rhs.towerShape;
}

