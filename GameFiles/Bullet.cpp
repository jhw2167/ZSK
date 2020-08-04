#include "Bullet.h"
//BulletObject.cpp for implementation of Bulet Class


/*	BULLET CONSTRUCTOR	*/

Bullet::Bullet(const sf::Vector2f& startPos,
	const sf::Vector2i& cursorPos, int bStrip,
	int bPen, float scale)
	//Bullet constructor initializes size, shape and position 
	//of bullet object
{
	setBulletPosition(startPos);
	setBulletVelocity(startPos, cursorPos);

	initBullet(scale, bStrip, bPen);
	orient(cursorPos);

	strip = bStrip;			//by default bullets strip 1 layer (strips=1) and deletes
	pen = bPen;				// after colliding with 1 zombie (pen = 1)
}

//END CONSTRUCTOR

/*  Bullet Initialize Functions  */
void Bullet::initBullet(const float scale,
	const int bStrip, const int bPen)
{
	float bulletLength = scale * 2.f;
	float bulletHeight = scale;

	bBody.setSize(sf::Vector2f(bulletLength, bulletHeight));
	bBody.setFillColor(sf::Color::Black);
	bBody.setOrigin(bulletLength, bulletHeight / 2.f);				
	//origin of bullet set at bullet top so circleShape
	//"bTop" can be set to same position

	bTop.setRadius(scale / 2.f);
	bTop.setFillColor(sf::Color::Black);
	bTop.setOrigin(bTop.getRadius(), bTop.getRadius());

	strip = bStrip;			//by default bullets strip 1 layer (strips=1) and deletes
	pen = bPen;				// after colliding with 1 zombie (pen = 1)


}



/*	BULLET SET FUNCTIONS	*/

void Bullet::setBulletPosition(const sf::Vector2f& newPos)				
{
	//setPosition function

	bBody.setPosition(newPos);
	bTop.setPosition(newPos);
	pos = newPos;
}

void Bullet::setBulletVelocity(const sf::Vector2f& playerPos,
	const sf::Vector2i& cursorPos, const float speed)		//moves bullet by adding unit vector to bullet shapes move function
{
	float yCoord = cursorPos.y - playerPos.y;
	float xCoord = cursorPos.x - playerPos.x;

	float mag = sqrt(pow(xCoord, 2) + pow(yCoord, 2));

	velocity = sf::Vector2f((xCoord / mag) * speed, (yCoord / mag) * speed);
	//creates bullet velocity vector as function of direction vector and speed												
}

void Bullet::setStrip(const int bStrip) {
	strip = bStrip;
}

void Bullet::setPen(const int bPen) {
	pen = bPen;
}

//End Set Functions


/*	BULLET ACCESSOR FUNCTIONS	*/
sf::Vector2f Bullet::getBulletPosition() const  {
	return pos;
}
//get bullets position function used for collisions 

sf::FloatRect Bullet::getBulletGlobalBounds() const {
	return bTop.getGlobalBounds();
}
//taken as global bounds of of bullets circlceShape top

int Bullet::getStrip() const {
	return strip;
}

int Bullet::getPen() const {
	return pen;
}
//End Accessor Methods


/*  Private Functions  */
void Bullet::orient(const sf::Vector2i& cursorPos)
{
	/*
		Calculated the angle to rotate the bullet object
		and applies it to the shape
	*/

	float xDif = cursorPos.x - pos.x;
	float yDif = pos.y - cursorPos.y;

	float radAngle = std::atan(yDif / xDif);
	float angle = zsk::radsToDegs(radAngle);

	float circleX = pos.x;
	float circleY = pos.y;

	if (xDif < 0) {
		radAngle += zsk::pi;
		circleX += (std::cos(radAngle)) * bBody.getSize().x;
		circleY -= std::sin(radAngle) * bBody.getSize().x;
	}

	bBody.setRotation(-angle);
	bTop.setPosition(circleX, circleY);
}


/*	OTHER PUBLIC FUNCTIONS	*/
void Bullet::moveBullet() {
	bBody.move(velocity);
	bTop.move(velocity);

	pos += velocity;
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



sf::Vector2f operator*(sf::Vector2f v1, int const& a)
{
	sf::Vector2f ret;
	ret.x = v1.x * a;
	ret.y = v1.y * a;

	return ret;
}


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
