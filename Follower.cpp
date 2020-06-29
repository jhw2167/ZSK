//Implementation of Follower.h class

#include "Follower.h"

	/*  Static Initializations  */

int Follower::f_id = 0;
sf::Font Follower::arial;



	/*  Constructor  */
Follower::Follower(sf::RenderWindow &window, float tRadius, sf::Color fColor, int startHealth 
	, short retrgtRate, short redirRate, float scale, bool showBoxes)
{
	id = f_id++;

	//showBoxes = true;
	fShape = FollowerShape(fColor, scale);
	initFollowerBox(fShape, showBoxes);

	initHealthText();
	setHealth(startHealth);

	windowLength = window.getSize().x;
	windowHeight = window.getSize().y;

	followingPlayer = false;
	momentum = 1.01;
	aUp = aLeft = aDown = aRight = 0;
	bounce = sf::Vector2f(5.f, 5.f);

	retargetRate = retrgtRate;
	retargetCount = 0;

	redirectRate = redirRate;
	redirectCount = 0;

	playersOldX = 0;
	playersOldY = 0;
	//initializations critical to move function

	towerRadius = tRadius;
	randomSpawn();

}
//End Constructor


void Follower::initFollowerBox(FollowerShape &shape, bool showBoxes)
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


void Follower::initHealthText() {

	if (!arial.loadFromFile("arial.ttf")) { 	//loads font to use for text drawing
		std::cout << "Error loading text" << std::endl;
	}
	int textSize = 28;

	healthText.setFont(arial);
	healthText.setCharacterSize(textSize);
	healthText.setFillColor(sf::Color::White);

}

void Follower::randomSpawn()
{
	static int spawnerClock = 0;		//clock will rotate zombie's spawnlocale around the map

	float xLine1 = 0.f;				//zombies will spawn at random locations on these lines and feed into the map
	float xLine2 = windowLength;
	float yLine1 = 0.f;
	float yLine2 = windowHeight;

	static int srand(time(0));

	float randTopBotSpawn = (rand() % ((int)windowHeight - (2 * (int)towerRadius)) + (int)towerRadius);
	//random spawnpoint between two towers on top and bottom of map
	float randLeftRightSpawn = (rand() % ((int)windowLength - (2 * (int)towerRadius)) + (int)towerRadius);

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
//End init functions


	/*  Setter Methods  */
void Follower::setFollowerColor(sf::Color &color) {
	fShape.setColor(color);
}

void Follower::setPosition(sf::Vector2f &newPos)
{
	fPosition = newPos;

	fShape.setPosition(newPos);
	fBox.setPosition(newPos);
	healthText.setPosition(newPos);

}

void Follower::setVelocity(sf::Vector2f &vel) {
	fVelocity = vel;
}

void Follower::setHealth(int newHealth) {
	health = newHealth;
	healthText.setString(std::to_string(newHealth));

	float h = healthText.getLocalBounds().height;
	float l = healthText.getLocalBounds().width;

	healthText.setOrigin(l, h / 1.2f);
}
//End Setters


	/*  Accessor Methods  */
sf::Vector2f Follower::getFollowerPosition() {
	return fPosition;
}

sf::Vector2f Follower::getFollowerVelocity() {
	return fVelocity;
}

sf::FloatRect Follower::getFollowerGlobalBounds() {			//taken as global bounds of follower's circleShape head
	return fBox.getGlobalBounds();
}

int Follower::get_id() {
	return id;
}
//End Accessor Methods


/*  Functions  */
void Follower::setNewVelocity(sf::Vector2f const &destinationVector, float speed)
{
	//moves follower by adding unit vector to move function

	float yCoord = destinationVector.y - fShape.getPosition().y;				
	//destination vector is either player position or random movement
	//when follower is not following player

	float xCoord = destinationVector.x - fShape.getPosition().x;

	float mag = sqrt(pow(xCoord, 2) + pow(yCoord, 2));			
	//finds magnitude of vector to create unit vector

	float xVelocity = ((xCoord / mag) * speed * pow(momentum, aRight + aLeft));
	float yVelocity = ((yCoord / mag) * speed * pow(momentum, aUp + aDown));

	sf::Vector2f toPass = sf::Vector2f(xVelocity, yVelocity);

	setVelocity(toPass);

	//creates follower velocity vector as function of direction vector and speed
}


//MOVE FOLLOWER LOGIC
void Follower::moveLogic(bool collision, Player &player, std::vector<Tower> &towers)
{
	isFollowingPlayer(player);			//checks to see if following player

	if (followingPlayer)				//if not following player it does not need to reset its velocity
	{
		bool decelerate = fShape.getGlobalBounds().intersects(player.getHeartBounds());

		accelerate(player, decelerate);
		//follower accerlates if following a player or decelerate if they contact him

		if (retargetCount % retargetRate == 0)
		{
			setNewVelocity(player.getPosition());
			retargetCount = 1;
		}
		else
			retargetCount++;
	}



	for (size_t i = 0; i < towers.size(); i++) {	
		//checks each tower for potential collision
		if (redirectCount > redirectRate)
			towerCollision(towers[i]);
		else
			redirectCount++;
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

void Follower::moveFollower(sf::Vector2f const &vel) {
	fShape.move(vel);
	fBox.move(vel);

	healthText.move(vel);

	fPosition = fShape.getPosition();
}

//ACCELERATES FOLLOWER
void Follower::accelerate(Player &player, bool decelerate)
{
	//accelerates the follower over time based on passed value from main
	
	float playersCurrX = player.getPosition().x;
	float playersCurrY = player.getPosition().y;
	//floats get player's position to determine which direction hes traveling

	bool movingLeft = playersCurrX < playersOldX;			
	bool movingRight = playersCurrX > playersOldX;
	//bools determine which direction player has been traveling

	bool movingUp = playersCurrY < playersOldY;
	bool movingDown = playersCurrY > playersOldY;


	if (movingLeft)
	{
		aRight = 0;
		aLeft++;											
		//counts number of times follwer is accelerated
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

	playersOldX = playersCurrX;		
	playersOldY = playersCurrY;
	//sets the new old coordinates equal to 
	//current coordinates for next function call

	if (decelerate) {					
		aUp = aLeft = aDown = aRight = 0;
		// all exponents set to 0 to decelerate follower
	}

}

bool Follower::isFollowingPlayer(Player &player)
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

float Follower::distanceFrom(sf::Vector2f const &objectPos)
{
	//calculates vector distance from player or tower object

	float xDist = abs(objectPos.x - fShape.getPosition().x);			
	float yDist = abs(objectPos.y - fShape.getPosition().y);
	//calculates x and y distances away follower is from player

	return pow(xDist * xDist + yDist * yDist, 0.5);		
	//calculates vector for distance from follower to player
}


//OUT OF BOUNDS AND FOLLOWER COLLISION BEHAVIOR
void Follower::outOfBounds(sf::Vector2f &pos, bool col)
{
	float buffer = 0.f;
	//need an off screen boundry for the velocity reversal or follower gets
	//stuck moving further outside
	bool xOut = pos.x < 0 || pos.x > windowLength;
	bool yOut = pos.y < 0 || pos.y > windowHeight;

	if (!col)
	//if no collision
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

bool Follower::towerCollision(Tower &tower)
{
	//if there is a tower collision, redirect follower's velocity
	bool towerCollision = distanceFrom(tower.getPosition()) <= tower.getTowerRadius();

	static int count = 0;

	if (towerCollision) {
		fVelocity = -fVelocity;
	}

	redirectCount = 0;

	return towerCollision;
}

bool Follower::followerCollision(std::vector<Follower> &activeFollowers, int i)
{
	//checks for a collision with passed object follower and returns bool

	bool collision = false;

	for (size_t j = i + 1; j < activeFollowers.size(); j++)
	{
		if (activeFollowers.at(i).getFollowerGlobalBounds().intersects(			
			activeFollowers.at(j).getFollowerGlobalBounds()))
			//compare the followers at different indexes
		{
			activeFollowers.at(j).setMinusBounce();
			collision = true;
		}

	}
	return collision;
}

void Follower::setMinusBounce()
{
	static int bounceType = 0;

	switch (bounceType % 4)
	{
	case 0:
		bounce = bounce;			
		//no change to bounce vector
		break;

	case 1:
		bounce.x = -bounce.x;		
		//bounces off in negative X direction
		break;

	case 2:
		bounce.y = -bounce.y;		
		//negative y direction
		break;

	case 3:
		bounce = -bounce;			
		//both negative directions
		break;
	}

	bounceType++;					
	//increments to cycle through bounce types

}

void Follower::fixCenterVelocity()
{
	sf::Vector2f center = sf::Vector2f(windowLength / 2.f, windowHeight / 2.f);
	setNewVelocity(center);
}

//DRAW FOLLWER ASPECTS
void Follower::drawFollower(sf::RenderWindow &window)
{
	fShape.draw(window);
	window.draw(fBox);
	window.draw(healthText);
}
