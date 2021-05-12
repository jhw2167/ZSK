//Implementation file for FollowerShape.h

#include "FollowerShape.h"

	/*	Constructor	*/
FollowerShape::FollowerShape(sf::Color color, float scale)
{
	//setUp follower Shape and size
	legAngle = 35;
	setSize(scale);
	//set follower color
	setColor(color);
}


	/*	Setter Methods	*/
void FollowerShape::setSize(float scale)
{
	headRadius = scale * 5.f;
	legLength = scale * 10.f;
	legWidth = scale * 2.f;

	head.setRadius(headRadius);
	head.setOrigin(head.getRadius(), head.getRadius());
	//origin at center of head

	leg1.setSize(sf::Vector2f(legWidth, legLength));
	leg1.setOrigin(sf::Vector2f(legWidth / 2.f, 0));
	leg1.setRotation(legAngle);
	//Origin at center, left side of leg

	leg2.setSize(sf::Vector2f(legWidth, legLength));
	leg2.setOrigin(sf::Vector2f(legWidth / 2.f, 0));
	leg2.setRotation(360 - legAngle);
	//Origin at center, left side of leg

	fSize = scale;
}

void FollowerShape::setColor(sf::Color color)
{
	head.setFillColor(color);
	leg1.setFillColor(color);
	leg2.setFillColor(color);

	fColor = color;
}

void FollowerShape::setPosition(sf::Vector2f newPos)
{
	head.setPosition(newPos);
	leg1.setPosition(newPos);
	leg2.setPosition(newPos);

	fPos = newPos;
}
//***END SETTER METHODS***


	/*	Accessor Methods	*/
float FollowerShape::getSize() {
	return fSize;
}

sf::Color FollowerShape::getColor() {
	return fColor;
}

sf::Vector2f FollowerShape::getPosition() {
	return fPos;
}

sf::FloatRect FollowerShape::getGlobalBounds()
//taken as global bounds of follower's circleShape head
{
	return head.getGlobalBounds();
}

//bounds with respect to center of follower head at fPos
float FollowerShape::getLeftBounds()
{
	return fPos.x - headRadius;
}

float FollowerShape::getUpperBounds()
{
	return fPos.y - headRadius;
}

float FollowerShape::getRightBounds()
{
	return fPos.x + headRadius;
}

float FollowerShape::getLowerBounds()
{
	float degsToRads = static_cast<float>(3.14159 / 180);
	float dist = 2 * headRadius * cos(legAngle * degsToRads);
	return fPos.y + dist;
}

float FollowerShape::getHeadRadius() {
	return headRadius;
}

//***END GETTER METHODS***


/*	Functions	*/
void FollowerShape::move(sf::Vector2f moveVect)
{
	head.move(moveVect);
	leg1.move(moveVect);
	leg2.move(moveVect);

	fPos += moveVect;
}


/*	Draw*/
void FollowerShape::draw(const std::shared_ptr<sf::RenderWindow>& window_ptr)
{
	window_ptr->draw(head);
	window_ptr->draw(leg1);
	window_ptr->draw(leg2);
}