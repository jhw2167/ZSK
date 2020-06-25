#include "BulletObject.h"
//BulletObject.cpp for implementation of Bulet Class


/*	BULLET CONSTRUCTOR	*/

Bullet::Bullet(sf::Vector2f startPos,
	sf::Vector2i cursorPos, int bStrip,
	int bPen, float scale)
	//Bullet constructor initializes size, shape and position 
	//of bullet object
{
	float bulletLength = scale * 2.f;
	float bulletHeight = scale;

	bBody.setSize(sf::Vector2f(bulletLength, bulletHeight));
	bBody.setFillColor(sf::Color::Black);
	bBody.setOrigin(bulletLength, bulletHeight / 2.f);				//origin of bullet set at bullet top so circleShape "bTop" can be set to same position
	bBody.setPosition(startPos);									//and they will be overlapping

	bTop.setRadius(scale / 2.f);
	bTop.setFillColor(sf::Color::Black);
	bTop.setOrigin(bTop.getRadius(), bTop.getRadius());
	bTop.setPosition(startPos);

	setBulletVelocity(startPos, cursorPos);

	strip = bStrip;			//by default bullets strip 1 layer (strips=1) and deletes
	pen = bPen;				// after colliding with 1 zombie (pen = 1)
}

//END CONSTRUCTOR


/*	BULLET SET FUNCTIONS	*/

void Bullet::setBulletPosition(sf::Vector2f newPos)				//setPosition function
{
	bBody.setPosition(newPos);
	bTop.setPosition(newPos);
}

void Bullet::setBulletVelocity(sf::Vector2f playerPos, sf::Vector2i cursorPos, float speed)		//moves bullet by adding unit vector to bullet shapes move function
{
	float yCoord = cursorPos.y - playerPos.y;

	float xCoord = cursorPos.x - playerPos.x;

	float mag = sqrt(pow(xCoord, 2) + pow(yCoord, 2));

	bBody.rotate(std::tan(static_cast<double>(yCoord / xCoord)));

	velocity = sf::Vector2f((xCoord / mag) * speed, (yCoord / mag) * speed);
	//creates bullet velocity vector as function of direction vector and speed												
}

void Bullet::setStrip(int bStrip) {
	strip = bStrip;
}

void Bullet::setPen(int bPen) {
	pen = bPen;
}

//End Set Functions


/*	BULLET ACCESSOR FUNCTIONS	*/
sf::Vector2f Bullet::getBulletPosition() {
	return bTop.getPosition();
}
//get bullets position function used for collisions 

sf::FloatRect Bullet::getBulletGlobalBounds() {
	return bTop.getGlobalBounds();
}
//taken as global bounds of of bullets circlceShape top

int Bullet::getStrip() {
	return strip;
}

int Bullet::getPen() {
	return pen;
}
//End Accessor Methods


/*	OTHER PUBLIC FUNCTIONS	*/
void Bullet::moveBullet() {
	bBody.move(velocity);
	bTop.move(velocity);
}

bool Bullet::isOutOBounds(sf::RenderWindow &window)
{
	float xPos = bTop.getPosition().x;
	float yPos = bTop.getPosition().y;

	bool isOut = false;

	if (xPos > window.getSize().x || xPos < 0)
	{
		isOut = true;
	}

	else if (yPos > window.getSize().y || yPos < 0)
	{
		isOut = true;
	}

	return isOut;
}


//DRAW FUNCTIONS
void Bullet::drawBullet(sf::RenderWindow &window)
{
	window.draw(bBody);
	window.draw(bTop);
}

//End Bullet Class

/*	OVERLOADED OPERATORS	*/

sf::Vector2f operator /(const sf::Vector2f v1, const sf::Vector2f v2)
{
	float x = v1.x / v2.x;
	float y = v1.y / v2.y;

	return sf::Vector2f(x, y);
}

sf::Vector2f abs(sf::Vector2f v1) {
	float x = abs(v1.x);
	float y = abs(v1.y);

	return sf::Vector2f(x, y);
}


std::ostream& operator<< (std::ostream &out, const sf::Vector2f v1)
{
	out << "Vector x: " << v1.x << std::endl;
	out << "Vector y: " << v1.y << std::endl;
	out << std::endl;

	return out;
}

std::ostream& operator<< (std::ostream &out, const sf::Vector2i v1)
{
	out << "Vector x: " << v1.x << std::endl;
	out << "Vector y: " << v1.y << std::endl;
	out << std::endl;

	return out;
}
