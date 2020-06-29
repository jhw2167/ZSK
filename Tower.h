#pragma once


#include "Player.h"

class Tower {

private:
	float towerRadius;		
	int towerNumber; 
	//towers will be circleShapes in each of the four coners of the map
	//labels towers, 0, 1, 2, 3

	enum towerOwned {NOTOWNED, PLAYER1, PLAYER2, PLAYER3, PLAYER4};
	towerOwned towerOwnedBy;
	
	sf::Vector2f towerPosition;

	sf::CircleShape towerShape;
	sf::Sprite laser1;						
	//Laser will be comprised of a series of drawn sprites

	sf::RectangleShape laser;

public:
	
		/*  Constructors */
	Tower(sf::RenderWindow const &window, int tNumber = 0);


		/*  Init Methods  */
	void initTowerShape(sf::RenderWindow const &window);


		/*  Setter methods  */
	void setRadius(float tRadius);
	void setPosition(sf::RenderWindow const &window, int tNumber);



		/*  Accessor Methods  */
	sf::FloatRect getTowerGlobalBounds();
	sf::Vector2f getPosition();
	float getTowerRadius();
	sf::CircleShape getTowerShape();


	//TOWER OWNERSHIP METHODS
	bool isTowerOwned(sf::Vector2i mousePos, towerOwned i);
	int getTowerOwnership();
	
	/*  Functions  */

	//TOWER COLLISIONS
	bool checkTowerCollision(Player &player);

	//if (distanceFrom(playerPos) <= towerRadius)
		//return true;

	float distanceFrom(sf::Vector2f objectPos);



	//TOWER MECHANICS


	//ACTIVATING LASER






	//TOWER DRAW METHODS
	void drawTowers(sf::RenderWindow &window);

};
