//Implementation of Tower.h class

#include "Tower.h"

	/*  Init Static variables  */
sf::Image Tower::img;

sf::Texture Tower::laserTexture;

	/*  Public Methods  */
	

	/*  Constructors  */
Tower::Tower(sf::RenderWindow const &window, int tNumber)
//Constructs minimal tower objcet
{
	towerNumber = tNumber;

	initTowerShape(window);
	setPosition(window, tNumber);
	towerOwnedBy = NOTOWNED;

	if (tNumber == 0){
		initLasers();
	}
}
//End Constructors


	/*  Init Methods  */
void Tower::initTowerShape(sf::RenderWindow const &window)
{
	float tRadius = std::min(window.getSize().x, window.getSize().y) / 8.f;
	setRadius(tRadius);

	towerShape.setFillColor(sf::Color::Black);
	towerShape.setOrigin(towerRadius, towerRadius);
}

void Tower::addLaserTextures(const sf::Color & color)
{
}

void Tower::initLasers()
{
	/*
		Static method "initLasers" builds a colored laser
		texture from an lase laser and creates a generic laser sprite
		thereafter that will adjust its color based on the player that
		owns the given tower
	*/

	if (!img.loadFromFile("Art/Sprites/base_laser.png")) {
		cout << "Error loading laser images\n";
	}
	zsk::art::changePixelRange(img, sf::Color::Red, sf::Color::Black);
	img.saveToFile("Sprites/base_laser1.png");

	if (!laserTexture.loadFromImage(img)){
		cout << "Error loading laser textures from images\n";
	}
	
	laser.setTexture(laserTexture);
	sf::Vector2f pos1 = sf::Vector2f(300.f, 300.f);
	laser.setPosition(pos1);

}


//End Inits


	/*  Setter methods  */
void Tower::setRadius(float tRadius) {
	towerRadius = tRadius;
	towerShape.setRadius(towerRadius);
}

void Tower::setPosition(sf::RenderWindow const &window, int tNumber)
{
	//sets tower position to one of the four corners
	towerNumber = tNumber;

	//tower's number denotation determines its position

	switch (towerNumber) {
	case 1:
		towerShape.setPosition(0, 0);
		break;
	case 2:
		towerShape.setPosition(window.getSize().x, 0);
		break;
	case 3:
		towerShape.setPosition(0, window.getSize().y);
		break;
	case 4:
		towerShape.setPosition(window.getSize().x, window.getSize().y);
		break;
	case 0:														//case zero tower not intented to be shown or utilized, 
		towerShape.setPosition(-100.f, -100.f);					//its instantiation helps with mechanics such as checking tower collisions
		break;
	}

	towerPosition = towerShape.getPosition();						
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


//TOWER OWNERSHIP METHODS
bool Tower::isTowerOwned(sf::Vector2i mousePos, towerOwned i)
{
	if (towerShape.getGlobalBounds().contains(mousePos.x, mousePos.y));
	towerOwnedBy = i;

	return towerOwnedBy;				
	//will return either 0 for unowned or >0 integer that equates to true boolean
}

int Tower::getTowerOwnership() {
	return towerOwnedBy;
}
//End Accessor Methods


	/*  Functions  */

//TOWER COLLISIONS
bool Tower::checkTowerCollision(Player &player)
{
	bool collision = player.getPlayerBounds().intersects(towerShape.getGlobalBounds());
	return collision;
}

//if (distanceFrom(playerPos) <= towerRadius)
	//return true;

float Tower::distanceFrom(sf::Vector2f objectPos)
//calculates vector distance from player or tower object
{
	float xDist = abs(objectPos.x - towerPosition.x);			//calculates x and y distances away follower is from player
	float yDist = abs(objectPos.y - towerPosition.y);

	return pow(xDist * xDist + yDist * yDist, 0.5);							//calculates vector for distance from follower to player
}


//TOWER MECHANICS


//ACTIVATING LASER


//TOWER DRAW METHODS
void Tower::drawTowers(sf::RenderWindow &window) {
	window.draw(towerShape);

	window.draw(laser);
}
