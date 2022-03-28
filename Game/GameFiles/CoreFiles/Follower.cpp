//Implementation of Follower.h class

#include "Follower.h"

	/*  Static Initializations  */

int Follower::maxMerge = 3;
const sf::Vector2f Follower::globBounce
	= sf::Vector2f(5.f, 5.f);
const float Follower::speedBN = 10.f;
const int Follower::dmgBN = 5;
float Follower::towerRadius = 100.f;



	/*  Constructor  */
Follower::Follower(sf::Color fColor, int startHealth, 
	int startDmg, int retrgtRate, int redirRate, float scale, bool showBoxes)
	: GameObj(ObjType::FOL)
{
	//showBoxes = true;
	fShape = FollowerShape(fColor, scale);
	initFollowerBox(fShape, showBoxes);

	initHealthText();
	setHealth(startHealth);

	setDamage(startDmg);

	followingPlayer = false;
	momentum = 1.01f;
	aUp = aLeft = aDown = aRight = 0;
	breakNeck = false;

	retargetRate = retrgtRate;
	retargetCount = 0;

	redirectRate = redirRate;
	redirectCount = 0;
	towerColNum = -1;

	playersOldX = 0;
	playersOldY = 0;
	//initializations critical to move function

	randomSpawn();

	mergeCount = 1;

	/* circleShape
	*/

	dot.setFillColor(sf::Color::Red);
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

	int textSize = 26;

	healthText.setFont(zsk::art::arial);
	healthText.setCharacterSize(textSize);
	healthText.setFillColor(sf::Color::White);

}

void Follower::randomSpawn()
{

	zsk::vect xRange = { towerRadius, window_ptr->getPosition().x - towerRadius };
	zsk::vect yRange = { towerRadius, window_ptr->getPosition().y - towerRadius };
	//x and y ranges where follower can spawn

	zsk::vect spawnPt = zsk::randomSpawn(xRange, yRange);
	//a random spawn point generated between towers on the screen
	//and stored in a vector
	zsk::vect sideNums = { 1, 4 };
	int spawnSide = static_cast<int>(zsk::randomSpawn(sideNums).a);
	//clock will rotate zombie's spawnlocale around the map

	/*
		if (initialSpawns > 0) {
			spawnSide = 0;
			initialSpawns--;
		}
	*/

	sf::Vector2f newPos = sf::Vector2f(spawnPt.a, spawnPt.b);
	float windowLength = static_cast<float>(window_ptr->getPosition().x);
	float windowHeight = static_cast<float>(window_ptr->getPosition().y);

		switch (spawnSide)
		{
		case 0:
			//no action, spawnpoint remains the same
			break;

		case 1:
			//spawn left
			newPos.x = 0.f;
			break;

		case 2:
			//spawn top
			newPos.y = 0.f;
			break;

		case 3:
			//spawn right
			newPos.x = windowLength;
			break;

		case 4:
			//spawn bot
			newPos.y = windowHeight;
		}
	

	setPosition(newPos);

	setNewVelocity(sf::Vector2f(windowLength / 2.f, windowHeight / 2.f));
	//initializes follower velocity starting from its random spawn to the center of the map

}
//End init functions


	/*  Setter Methods  */
void Follower::setFollowerColor(const sf::Color &color) {
	fShape.setColor(color);
}

void Follower::setPosition(const sf::Vector2f& newPos)
{
	pos = newPos;

	fShape.setPosition(newPos);
	fBox.setPosition(newPos);
	healthText.setPosition(newPos);

}

void Follower::setVelocity(const sf::Vector2f& vel) {
	fVelocity = vel;
}

void Follower::setHealth(int newHealth) {
	health = newHealth;
	healthText.setString(std::to_string(newHealth));

	float l = healthText.getLocalBounds().width / 2.f;
	float h = healthText.getLocalBounds().height / 1.3f;

	if (health == 1)
		l = 7.f;

	if (health < 10) {
		healthText.setCharacterSize(26);
	}
	else if (health >= 10) {
		healthText.setCharacterSize(22);
		l += 2.f;
	}

	healthText.setOrigin(l , h);
	healthText.setPosition(pos);
}

void Follower::setDamage(int newDmg) {
	dmgDone = newDmg;
}

void Follower::setBounce(const sf::Vector2f& bnc) {
	bounce = bnc;
}

//STATIC Setters
void Follower::setTowerRadius(const float tRadius) {
	towerRadius = tRadius;
}
//End Setters


	/*  Accessor Methods  */
sf::Vector2f Follower::getFollowerPosition() const {
	return pos;
}

sf::Vector2f Follower::getFollowerVelocity() const  {
	return fVelocity;
}

const sf::FloatRect Follower::getGlobalBounds() const {			
	//taken as global bounds of follower's circleShape head
	return fBox.getGlobalBounds();
}

int Follower::getHealth() const {
	return health;
}

int Follower::getDamage() const {
	return dmgDone;
}

int Follower::getMergeCount() const {
	return mergeCount;
}

sf::Vector2f Follower::getBounce() const {
	return bounce;
}

//End Accessor Methods


/*  Functions  */
void Follower::centerHeathText() 
{
	sf::Vector2f textDims = sf::Vector2f(healthText.getLocalBounds().width,
		healthText.getLocalBounds().height);
	sf::Vector2f centerText = sf::Vector2f(0, -6.f);	//requires bit of adj to center text 


	healthText.setOrigin(textDims / 2.f);
	healthText.setPosition(healthText.getPosition() + centerText);
}


//MOVE FOLLOWER LOGIC
void Follower::moveLogic(bool collision, Player &player, std::vector<Tower> &towers)
{
	//**NEED TO UPDATE HERE** - these vars dont need to be passed, all info can
	// be acquired from the gameObjs vector
	//collision - check "cols" vector for colisions of type FOL
	//player	-	add for loop to check all players
	//towers	- parse through LL @ towers section given by 
	//				static object point


	/*
		Function: moveLogic()
		-	We check to see if our follower currently IS following a player
		-	if YES
				- We accelerate/decellerate follower as appropriate

		-	We check for potential collission with tower and assign a tower number
		in order to carry this iformation

		-	If there is a collision with another follower, that information
		is passed and we "bounce" in a random direction.
	*/

	isFollowingPlayer(player);			//checks to see if following player


	if (followingPlayer)				
	{
		
		bool decelerate = fShape.getGlobalBounds().intersects(player.getHeartBounds());

		accelerate(player, decelerate);
		//follower accerlates if following a player or decelerate if they contact him

		if (retargetCount % retargetRate == 0)
		{
			setNewVelocity(player.getPosition());
			retargetCount = 1;
		}
		retargetCount++;
	}


	if (towerColNum == -1)
	{
		for (size_t i = 0; i < towers.size(); i++) {
			//checks each tower for potential collision

			if (towerCollision(towers[i])) {
				towerColNum = i;
				break;
			}
			else
				towerColNum = -1;
		}
	}
	else if (towerCollision(towers[towerColNum])) {
		//no change, we are still colliding with tower
	} 
	else {
		towerColNum = -1;
	}


	sf::Vector2f newPos = fShape.getPosition() + fVelocity;
	if (collision) 
	{
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

	pos = fShape.getPosition();
	dot.setPosition(fBox.getPosition());
}

bool Follower::isBreakNeck(bool wasFollowing)
{
	if (wasFollowing && !followingPlayer) {
		float speed = static_cast<float>(zsk::magnitude(fVelocity.x, fVelocity.y));

		if (speed >= speedBN) {
			breakNeck = true;
			fVelocity = fVelocity * 2;
			dmgDone *= dmgBN;
		}
		//Double our speed and set breakNeck to true;
	}

	return breakNeck;
}

void Follower::setNewVelocity(sf::Vector2f const &destinationVector, float speed)
{
	//moves follower by adding unit vector to move function

	float yCoord = destinationVector.y - fShape.getPosition().y;
	//destination vector is either player position or random movement
	//when follower is not following player

	float xCoord = destinationVector.x - fShape.getPosition().x;

	float mag = static_cast<float>(zsk::magnitude(xCoord, yCoord));
	//finds magnitude of vector to create unit vector

	if (breakNeck) {
		speed = speedBN;
	}

	float xVelocity = ((xCoord / mag) * speed * static_cast<float>(pow(momentum, aRight + aLeft)));
	float yVelocity = ((yCoord / mag) * speed * static_cast<float>(pow(momentum, aUp + aDown)));

	sf::Vector2f toPass = sf::Vector2f(xVelocity, yVelocity);

	setVelocity(toPass);

	//creates follower velocity vector as function of direction vector and speed
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


	if (movingLeft) {
		aRight = 0;
		aLeft++;											
		//counts number of times follwer is accelerated
	}
	else if (movingRight) {
		aLeft = 0;
		aRight++;
	}

	if (movingUp) {
		aDown = 0;
		aUp++;
	}
	else if (movingDown) {
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

		if (breakNeck)
		{
			breakNeck = false;
			fVelocity = fVelocity * 0.5;
			dmgDone /= dmgBN;

		}
		
	}

}

bool Follower::isFollowingPlayer(Player &player)
{
	bool wasFollowing = followingPlayer;

	if (!followingPlayer)
		followingPlayer = zsk::distanceFrom(this->pos, player.getPosition()) 
		<= player.getSmallFollowAreaRadius() + 2 * fShape.getHeadRadius();
	else
		followingPlayer = zsk::distanceFrom(this->pos, player.getPosition()) 
		<= player.getLargeFollowAreaRadius() + 2 * fShape.getHeadRadius();

	if (!wasFollowing && followingPlayer && !breakNeck){
		player.setInvulnFrames(10);
		//if you just start following a player, give them short term
		//invulnerabillity so players dont needlessly take dmg when
		//getting fols to follow them
	}

	isBreakNeck(wasFollowing);

	return followingPlayer;
}


//OUT OF BOUNDS AND FOLLOWER COLLISION BEHAVIOR
void Follower::outOfBounds(sf::Vector2f &pos, bool col)
{
	float buffer = 0.f;
	//need an off screen boundry for the velocity reversal or follower gets
	//stuck moving further outside
	bool xOut = pos.x < 0 || pos.x > window_ptr->getPosition().x;
	bool yOut = pos.y < 0 || pos.y > window_ptr->getPosition().y;

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
	bool towerCollision = zsk::distanceFrom(this->pos,
		tower.getPosition()) <= tower.getTowerRadius() +
		fShape.getHeadRadius();

	if (towerCollision) {
		fVelocity = -fVelocity;
		++redirectCount;
		//cout << "redir count: " << redirectCount << endl;
	}
	else {
		redirectCount = 0;
	}
		

	if (redirectCount > 5 ){
		fixCenterVelocity();
		redirectCount++;
	}

	if (redirectCount > 25){
		redirectCount = 0;
	}

	return towerCollision;
}

bool Follower::followerCollision(std::list<Follower> &fols,
	std::list<Follower>::iterator fol_it)
{
	//checks for a collision with passed object follower and returns bool

	bool collision = false;

	for (auto fol_it2 = ++fol_it; fol_it2 != fols.end();)
	{
		if (this->getGlobalBounds().intersects(			
			fol_it2->getGlobalBounds()))
			//compare the followers at different indexes
		{
			if (mergeCount + fol_it2->getMergeCount() < maxMerge) {
				merge(fols, fol_it2);
			}
			else {
				fol_it2->setMinusBounce();

				if (this->getGlobalBounds().contains(
					fol_it2->getPos() + fol_it2->getBounce() )){
					this->setMinusBounce();
				}
				fol_it2++;
			}
			
			collision = true;
		}
		else {
			fol_it2++;
		}
	}

	return collision;
}

void Follower::setMinusBounce()
{
	zsk::vect range = { 0, 4 };
	int bounceType = static_cast<int>(zsk::randomSpawn(range).a);

	bounce = globBounce;

	switch (bounceType)
	{
	case 0:		
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

}
		//private

void Follower::fixCenterVelocity() {
	float centerX = window_ptr->getPosition().x / 2.f;
	float centerY = window_ptr->getPosition().y / 2.f;
	setNewVelocity(sf::Vector2f(centerX, centerY));
}
		//private

void Follower::merge(std::list<Follower>& fols,
	std::list<Follower>::iterator& fol_it) {

	/*
		If the followers are capable of merging, then we 
		"merge" them by combining their health, dmgDone
		and potentially speed
	*/

	int newHealth = health + fol_it->getHealth();
	setHealth(newHealth);
	
	int newDmg = dmgDone + fol_it->getDamage();
	setDamage(newDmg);

	breakNeck = std::max(breakNeck, fol_it->breakNeck);

	mergeCount++;
	fol_it = fols.erase(fol_it);
}
		//private

//DAMAGE DEALING AND GIVING
const int Follower::takeDamage(int dmg)
{
	int newHealth = health - dmg;

	if (mergeCount > 1)
		mergeCount--;
	
	if (newHealth <= 0)	{
		return 0;
	}
	else{
		setHealth(newHealth);
		return newHealth;
	}
}





	/*	UPDATE	*/

STATE Follower::update() 
{
	/*
		Routine update function for followers, each follower
		updates *each frame* and these functions are called
		in each frame
			- Involves moving and interacting with other game objs
	*/

	moveFollower();

	shootFollower();

	attackPlayer();

	return STATE::GAME;
}


void Follower::moveFollower()
{
	//move yourself "indivual" follower
	//		- We must inspect follower's collisions then move

}

void Follower::shootFollower() {
	//Check if follower has been attacked

}

void Follower::attackPlayer()
{
	//check if you're dealing damage
}



/*		Private Update Functions	*/


/******************/

//DRAW FOLLWER ASPECTS
void Follower::drawFollower()
{
	fShape.draw(window_ptr);
	window_ptr->draw(fBox);
	window_ptr->draw(healthText);
	window_ptr->draw(dot);
}


//COPY CONSTRUCTOR
Follower::Follower(const Follower &rhs) : GameObj(rhs)
{
	//Basics
	this->fShape = rhs.fShape;
	this->fBox = rhs.fBox;

	this->health = rhs.health;
	this->dmgDone = rhs.dmgDone;
	this->healthText = rhs.healthText;

	//Merging
	this->mergeCount = rhs.mergeCount;

	//Position and velocity
	this->followingPlayer = rhs.followingPlayer;
	this->fVelocity = rhs.fVelocity;
	this->breakNeck = rhs.breakNeck;
	this->momentum = rhs.momentum;
	aUp, aLeft, aDown, aRight = 0;
	//enum direction { STILL = 0, UP, LEFT, DOWN, RIGHT };

	//Player targeting
	this->retargetRate = rhs.retargetRate;
	this->retargetCount = rhs.retargetCount;
	this->redirectRate = rhs.redirectRate;
	this->redirectCount = rhs.redirectCount;

	this->playersOldX = rhs.playersOldX;
	this->playersOldY = rhs.playersOldY;

	//Follower bounds
	this->bounce = rhs.bounce;
	this->towerColNum = rhs.towerColNum;
}
