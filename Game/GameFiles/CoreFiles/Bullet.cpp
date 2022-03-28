#include "Bullet.h"
//BulletObject.cpp for implementation of Bulet Class


/*	BULLET CONSTRUCTOR	*/

Bullet::Bullet(const sf::Vector2f& startPos, const int bStrip,
	const int bPen, const float scale, const float speed,
	const sf::Color& color) : GameObj(ObjType::BUL)
	//Bullet constructor initializes size, shape and position 
	//of bullet object
{
	//cout << "Calling bullet constr, id: " << id << endl;
	setBulletPosition(startPos);
	setBulletVelocity(startPos, speed);

	initBullet(scale, bStrip, bPen, color);
	orient();

	strip = bStrip;			//by default bullets strip 1 layer (strips=1) and deletes
	pen = bPen;				// after colliding with 1 zombie (pen = 1)
}

//END CONSTRUCTOR


/*  Bullet Initialize Functions  */
void Bullet::initBullet(const float scale,
	const int bStrip, const int bPen, const sf::Color& bColor)
{
	float bulletLength = scale * 2.f;
	float bulletHeight = scale;

	bBody.setSize(sf::Vector2f(bulletLength, bulletHeight));
	bBody.setFillColor(sf::Color::Black);
	bBody.setOrigin(bulletLength, bulletHeight / 2.f);				
	//origin of bullet set at bullet top so circleShape
	//"bTop" can be set to same position

	bTop.setRadius(scale / 2.f);
	bTop.setFillColor(bColor);
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
	const float speed)		//moves bullet by adding unit vector to bullet shapes move function
{
	sf::Vector2i cursorPos = mouse_ptr->getPosition();
	float yCoord = cursorPos.y - playerPos.y;
	float xCoord = cursorPos.x - playerPos.x;

	float mag = static_cast<float>(sqrt(pow(xCoord, 2) + pow(yCoord, 2)));

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

const sf::FloatRect& Bullet::getGlobalBounds() const {
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
void Bullet::orient()
{
	/*
		Calculated the angle to rotate the bullet object
		and applies it to the shape
	*/

	sf::Vector2i cursorPos = mouse_ptr->getPosition();
	float xDif = cursorPos.x - pos.x;
	float yDif = pos.y - cursorPos.y;

	float radAngle = std::atan(yDif / xDif);
	float angle = static_cast<float>(zsk::radsToDegs(radAngle));

	float circleX = pos.x;
	float circleY = pos.y;

	if (xDif < 0) {
		radAngle += static_cast<float>(zsk::pi);
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

bool Bullet::isOutOBounds()
{
	float xPos = bTop.getPosition().x;
	float yPos = bTop.getPosition().y;

	bool xOut = (xPos > window_ptr->getSize().x) || (xPos < 0);
	bool yOut = (yPos > window_ptr->getSize().y) || (yPos < 0);

	return xOut || yOut;
}


/*		UPDATE		*/
STATE Bullet::update() {
	return STATE::GAME;
}
/***************/



//DRAW FUNCTIONS
void Bullet::drawBullet() {
	window_ptr->draw(bBody);
	window_ptr->draw(bTop);
}


//COPY CONSTRUCTOR
Bullet::Bullet(const Bullet& rhs) :
	GameObj(rhs)
{
	this->bBody = rhs.bBody;
	this->bTop = rhs.bTop;
	this->velocity = rhs.velocity;
	this->strip = rhs.strip;
	this->pen = rhs.pen;
}

//End Bullet Class
