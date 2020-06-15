//manages Follower object that spawned randomly

//SFML Includes
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

//Std Lib includes
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
#include <random>
#include <cstdlib>

//Project includes
#include "TowerObject.h"


//Start with FollowerShape class
class FollowerShape
{
private:

	sf::CircleShape head;			//shape vars for followers set up in constructor
	sf::CircleShape shield;
	sf::RectangleShape leg1;
	sf::RectangleShape leg2;

	float headRadius;				//size variables scaled by "fSize"							
	float shieldRadius;				// in setSize
	float legLength;
	float legWidth;
	float legAngle;

	float fSize;				//scales up follow size
	sf::Color fColor;
	sf::Vector2f fPos;

public:

	FollowerShape(sf::Color color = sf::Color::Black, float scale = 2.f)
	{
		//setUp follower Shape and size
		legAngle = 35;
		setSize(scale);
		//set follower color
		setColor(color);
	}

	//setter methods
	void setSize(float scale)
	{
		headRadius = scale * 5.f;
		legLength = scale * 10.f;
		legWidth = scale * 2.f;

		head.setRadius(headRadius);
		head.setOrigin(head.getRadius() , head.getRadius());
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

	void setColor(sf::Color color)
	{
		head.setFillColor(color);
		leg1.setFillColor(color);
		leg2.setFillColor(color);

		fColor = color;
	}

	void setPosition(sf::Vector2f newPos)
	{
		head.setPosition(newPos);
		leg1.setPosition(newPos);
		leg2.setPosition(newPos);

		fPos = newPos;
	}
	//***END SETTER METHODS***



	//getter methods
	float getSize() {
		return fSize;
	}

	sf::Color getColor() {
		return fColor;
	}

	sf::Vector2f getPosition() {
		return fPos;
	}

	sf::FloatRect getGlobalBounds()
		//taken as global bounds of follower's circleShape head
	{
		return head.getGlobalBounds();
	}

	//bounds with respect to center of follower head at fPos
	float getLeftBounds()
	{
		return fPos.x - headRadius;			
	}

	float getUpperBounds()
	{
		return fPos.y - headRadius;			
	}

	float getRightBounds()
	{
		return fPos.x + headRadius;				
	}

	float getLowerBounds()
	{
		float degsToRads = 3.14159 / 180;
		float dist = 2 * headRadius * cos(legAngle * degsToRads);
		return fPos.y + dist;
	}

	float getHeadRadius() {
		return headRadius;
	}

	//***END GETTER METHODS***

	//other Methods
	void move(sf::Vector2f moveVect)
	{
		head.move(moveVect);
		leg1.move(moveVect);
		leg2.move(moveVect);

		fPos += moveVect;
	}

	void draw(sf::RenderWindow &window)
	{
		window.draw(head);
		window.draw(leg1);
		window.draw(leg2);
	}
};









class Follower
{
private:

	static int f_id;			//all followers have same f_id value that increments
	int id;						//each follower has unique id

	FollowerShape fShape;

	int health;
	int dmgDone;
	sf::Text healthText;
	static sf::Font arial;

	sf::Vector2f fPosition;
	bool followingPlayer;

	sf::Vector2f fVelocity;									//speed and direction vector for moving followers
	float momentum;											//followers will gain speed as they follower a player
	int aUp, aLeft, aDown, aRight = 0;						//static ints will track how many times a follower has been accelerating in a given direction
	enum direction {STILL = 0, UP, LEFT, DOWN, RIGHT};		//declares enum direction to handle player movement

	int retargetRate;
	int retargetCount;

	float playersOldX;
	float playersOldY;


	sf::Vector2f bounce;			//vector with random x y coordinates for collisions
	sf::RectangleShape fBox;		//sets transparent box around follower for mechanics

	float windowLength;
	float windowHeight;

	float towerRadius;

public:

	Follower(sf::RenderWindow &window, float tRadius, sf::Color fColor = sf::Color::Black, int startHealth = 1, int retrgtRate = 10,
		float scale = 2.f, bool showBoxes = true)
	{
		id = f_id++;

		//showBoxes = true;
		fShape = FollowerShape(fColor, scale);
		initFollowerBox(fShape, showBoxes);

		initHealthText();
		setHealth(startHealth);

		windowLength = window.getSize().x ;
		windowHeight = window.getSize().y;

		followingPlayer = false;
		momentum = 1.01;
		aUp = aLeft = aDown = aRight = 0;
		bounce = sf::Vector2f(5.f, 5.f);

		retargetRate = retrgtRate;
		retargetCount = 0;

		playersOldX = 0;			//initializations critical to move function
		playersOldY = 0;

		towerRadius = tRadius;
		randomSpawn();

	}


	//INITIALIZE FOLLOWER
	void initFollowerBox(FollowerShape &shape, bool showBoxes = true)
	{
		float length = shape.getRightBounds() - shape.getLeftBounds();
		float height = shape.getLowerBounds() - shape.getUpperBounds();

		fBox = sf::RectangleShape(sf::Vector2f(length, height));

		sf::Color outlineColor = sf::Color::Transparent;

		if (showBoxes) {
			outlineColor = sf::Color::Black;
		}

		float thickness = 1.f;
		fBox.setFillColor(sf::Color::Transparent);
		fBox.setOutlineThickness(thickness);
		fBox.setOutlineColor(outlineColor);

		fBox.setOrigin(length / 2.f, shape.getHeadRadius());
	}


	void initHealthText() {

		if (!arial.loadFromFile("arial.ttf")) { 	//loads font to use for text drawing
			std::cout << "Error loading text" << std::endl;
		}
		int textSize = 30;

		healthText.setFont(arial);
		healthText.setCharacterSize(textSize);
		healthText.setFillColor(sf::Color::Red);
	
		float h = healthText.getLocalBounds().height;
		float l = healthText.getLocalBounds().width;
		healthText.setOrigin(l / 2.f, h / 2.f);

		std::cout << "Loaded txt settings: " << std::endl;
	}

	void randomSpawn()
	{
		static int spawnerClock = 0;		//clock will rotate zombie's spawnlocale around the map

		float xLine1 = 0.f;				//zombies will spawn at random locations on these lines and feed into the map
		float xLine2 = windowLength;
		float yLine1 = 0.f;
		float yLine2 = windowHeight;

		static int srand(time(0));

		float randTopBotSpawn = (rand() % ((int)windowHeight - ( 2 * (int)towerRadius) ) + (int)towerRadius);
		//random spawnpoint between two towers on top and bottom of map
		float randLeftRightSpawn = (rand() % ((int)windowLength - ( 2 * (int)towerRadius) ) + (int)towerRadius);

		sf::Vector2f newPos = sf::Vector2f();
		if (!followingPlayer)			//if not following player (all cases when follower is newly spawned), spawn point is randomized
		{
			switch (spawnerClock % 4)
			{
			case 0:
				newPos = sf::Vector2f(xLine1, randTopBotSpawn);
				break;

			case 1:
				newPos = sf::Vector2f(randLeftRightSpawn, yLine1);
				break;

			case 2:
				newPos = sf::Vector2f(xLine2, randTopBotSpawn);
				break;

			case 3:
				newPos = sf::Vector2f(randLeftRightSpawn, yLine2);
				break;
			}
		}

		setPosition(newPos);

		setNewVelocity(sf::Vector2f(windowLength / 2.f, windowHeight / 2.f));			
		//initializes follower velocity starting from its random spawn to the center of the map
	
		spawnerClock++;			//increments spawnerClock to adjust Spawns
	}

	

	//SET FOLLOWER ATTRIBUTES
	void setFollowerColor(sf::Color &color) {
		fShape.setColor(color);
	}

	void setPosition(sf::Vector2f &newPos)
	{
		fShape.setPosition(newPos);
		fBox.setPosition(newPos);
		fPosition = newPos;

		healthText.setPosition(newPos);

	}

	void setVelocity(sf::Vector2f &vel) {
		fVelocity = vel;
	}

	void setHealth(int newHealth) {
		health = newHealth;
		healthText.setString(std::to_string(newHealth));
	}

	//GET FOLLOWER ATTRIBUTES
	sf::Vector2f getFollowerPosition()
	{
		return fPosition;
	}

	sf::Vector2f getFollowerVelocity()
	{
		return fVelocity;
	}

	sf::FloatRect getFollowerGlobalBounds() {			//taken as global bounds of follower's circleShape head
		return fBox.getGlobalBounds();
	}

	int get_id()	{
		return id;
	}



	//SET UP AND MANAGE FOLLOWER MOVEMENT
	void setNewVelocity(sf::Vector2f destinationVector, float speed = 3.f)		//moves follower by adding unit vector to move function
	{

		float yCoord = destinationVector.y - fShape.getPosition().y;				//destination vector is either player position or random movement
																					//when follower is not following player
		float xCoord = destinationVector.x - fShape.getPosition().x;

		float mag = sqrt(pow(xCoord, 2) + pow(yCoord, 2));			//finds magnitude of vector to create unit vector

		float xVelocity = ((xCoord / mag) * speed * pow(momentum, aRight + aLeft));
		float yVelocity = ((yCoord / mag) * speed * pow(momentum, aUp + aDown));
		
		sf::Vector2f toPass = sf::Vector2f(xVelocity, yVelocity);

		setVelocity(toPass);

		//creates follower velocity vector as function of direction vector and speed
	}

	
	//MOVE FOLLOWER LOGIC
	void moveLogic(bool collision, Player &player, std::vector<Tower> &towers)
	{
		isFollowingPlayer(player);			//checks to see if following player
		
		if (followingPlayer)				//if not following player it does not need to reset its velocity
		{
			bool decelerate = fShape.getGlobalBounds().intersects(player.getHeartBounds());

			accelerate(player, decelerate);						
			//follower accerlates if following a player or decelerate if they contact him

			if (retargetCount % retargetRate == 0)
				setNewVelocity(player.getPosition());
			else
				retargetCount++;
		}
		
		

		for (size_t i = 0; i < towers.size() ; i++) {	//checks each tower for potential collision
			towerCollision(towers[i]);
		}

		sf::Vector2f newPos = fShape.getPosition() + fVelocity;
		if (collision) {
			newPos += bounce;
			outOfBounds(newPos, collision);
			moveFollower(fVelocity + bounce);
		}
		else {
			outOfBounds(newPos);
			moveFollower(fVelocity);
		}
	}

	void moveFollower(sf::Vector2f vel) {
		fShape.move(vel);			
		fBox.move(vel);

		healthText.move(vel);

		fPosition = fShape.getPosition();
	}

	//ACCELERATES FOLLOWER
	void accelerate(Player &player, bool decelerate = false)					//accelerates the follower over time based on passed value from main
	{
		float playersCurrX = player.getPosition().x;			//floats get player's position to determine which direction hes traveling
		float playersCurrY = player.getPosition().y;

		bool movingLeft = playersCurrX < playersOldX;			//bools determine which direction player has been traveling
		bool movingRight = playersCurrX > playersOldX;

		bool movingUp = playersCurrY < playersOldY;
		bool movingDown = playersCurrY > playersOldY;


		if (movingLeft)
		{
			aRight = 0;
			aLeft++;											//counts number of times follwer is accelerated
		}
		else if (movingRight)
		{
			aLeft = 0;					
			aRight++;
		}

		if (movingUp)
		{
			aDown = 0;
			aUp++;
		}
		else if (movingDown)
		{
			aUp = 0;
			aDown++;
		}

		playersOldX = playersCurrX;					//sets the new old coordinates equal to current coordinates for next function call
		playersOldY = playersCurrY;
		
		if (decelerate)	{					// all exponents set to 0 to decelerate follower
			aUp = aLeft = aDown = aRight = 0;
		}
		
	}

	bool isFollowingPlayer(Player &player)
	{
		bool wasFollowing = followingPlayer;

		if (!followingPlayer)
			followingPlayer = distanceFrom(player.getPosition()) <= player.getSmallFollowAreaRadius();
		else
			followingPlayer = distanceFrom(player.getPosition()) <= player.getLargeFollowAreaRadius();

		if (wasFollowing && !followingPlayer)
			setNewVelocity(player.getPosition());

		return followingPlayer;
	}

	float distanceFrom(sf::Vector2f objectPos)					//calculates vector distance from player or tower object
	{
		float xDist = abs(objectPos.x - fShape.getPosition().x);			//calculates x and y distances away follower is from player
		float yDist = abs(objectPos.y - fShape.getPosition().y);

		return pow(xDist * xDist + yDist * yDist, 0.5);							//calculates vector for distance from follower to player
	}

	
	//OUT OF BOUNDS AND FOLLOWER COLLISION BEHAVIOR
	void outOfBounds(sf::Vector2f pos, bool col = false)
	{
		float buffer = 0.f;
		//need an off screen boundry for the velocity reversal or follower gets
		//stuck moving further outside
		bool xOut = pos.x < 0 || pos.x > windowLength;
		bool yOut = pos.y < 0 || pos.y > windowHeight;

		if (!col)
		{
			if (xOut)
				fVelocity.x = -fVelocity.x;

			if (yOut)
				fVelocity.y = -fVelocity.y;
		}
		else
		{
			if (xOut)
			{
				fVelocity.x = -fVelocity.x;
				bounce.x = -bounce.x;
			}
				
			if (yOut)
			{
				fVelocity.y = -fVelocity.y;
				bounce.y = -bounce.y;
			}
				
		}
	
	}

	bool towerCollision(Tower tower)				//if there is a tower collision, redirect follower's velocity
	{
		bool towerCollision = distanceFrom(tower.getPosition()) <= tower.getTowerRadius();

		if (towerCollision) {
			fVelocity = -fVelocity;
		}
		return towerCollision;
	}

	bool followerCollision(std::vector<Follower> &activeFollowers, int i)		//checks for a collision with passed object follower and returns bool
	{
		bool collision = false;

		for (size_t j = i + 1; j < activeFollowers.size(); j++)
		{
			if (activeFollowers.at(i).getFollowerGlobalBounds().intersects(			//compare the followers at different elem position
				activeFollowers.at(j).getFollowerGlobalBounds()))
			{
				activeFollowers.at(j).setMinusBounce();	
				collision = true;
			}

		}
		return collision;
	}

	void setMinusBounce()
	{
		static int bounceType = 0;

		switch (bounceType % 4)
		{
		case 0:
			bounce = bounce;			//no change to bounce vector
			break;

		case 1:
			bounce.x = -bounce.x;		//bounces off in negative X direction
			break;

		case 2:
			bounce.y = -bounce.y;		//negative y direction
			break;

		case 3:
			bounce = -bounce;			//both negative directions
			break;
		}

		bounceType++;					//increments to cycle through bounce types

	}

	void fixCenterVelocity()
	{
		sf::Vector2f center = sf::Vector2f(windowLength / 2.f, windowHeight / 2.f);
		setNewVelocity(center);
	}

	//DRAW FOLLWER ASPECTS
	void drawFollower(sf::RenderWindow &window)
	{
		fShape.draw(window);
		window.draw(fBox);
		window.draw(healthText);
	}


	/*
	
	Follower(const Follower &f2)
	{
		f_id = f2.f_id;
		int id = f2.id;

		fShape = FollowerShape(f2.fShape);
		fBox = f2.fBox;

		health = f2.health;
		dmgDone = f2.dmgDone;
		//arial = f2.arial;
		//arial.loadFromFile("arial.ttf");
		healthText = f2.healthText;
		healthText.setFont(arial);


		fPosition = f2.fPosition;
		followingPlayer = f2.followingPlayer;

		fVelocity = f2.fVelocity;
		momentum = f2.momentum;
		aUp, aLeft, aDown, aRight = 0;
		//enum direction { STILL = 0, UP, LEFT, DOWN, RIGHT };

		retargetRate = f2.retargetRate;
		retargetCount = f2.retargetCount;

		playersOldX = f2.playersOldX;
		playersOldY = f2.playersOldY;

		bounce = f2.bounce;

		windowLength = f2.windowLength;
		windowHeight = f2.windowHeight;

		towerRadius = f2.towerRadius;
	}



	
	*/
	//COPY CONSTRUCTOR

};
	

