//manages Follower object that spawned randomly
#pragma once

//Project includes
#include "FollowerShape.h"
#include "Player.h"
#include "../../../BaseCode/pch/stdafx.h"

class Follower : 
	public GameObj
{
private:

	/*  Shape related  */
	FollowerShape fShape;
	sf::RectangleShape fBox;		
	//sets transparent box around follower for mechanics

	/*  Basic Stats */
	int health;
	int dmgDone;
	sf::Text healthText;


	/*  Merging  */
	int mergeCount;
	static int maxMerge;

	/*  Position and Velocity  */
	bool followingPlayer;
	const static float speedBN;
	bool breakNeck;
	const static int dmgBN;
	/*  breakNeck(BN) speed gives followers heightened dmg,
	and locks their targeting*/

	sf::Vector2f fVelocity;									//speed and direction vector for moving followers
	float momentum;											//followers will gain speed as they follower a player
	int aUp, aLeft, aDown, aRight = 0;						//static ints will track how many times a follower has been accelerating in a given direction
	enum direction {STILL = 0, UP, LEFT, DOWN, RIGHT};		//declares enum direction to handle player movement


	/* Player targeting  */
	int retargetRate;
	int retargetCount;

	int redirectRate;
	int redirectCount;

	float playersOldX;
	float playersOldY;


	/* Collision Info */
	int towerColNum;;
	sf::Vector2f bounce;
	static const sf::Vector2f globBounce;
	//vector with random x y coordinates for collisions

	/*  Window Variables */
	unsigned int windowLength;
	unsigned int windowHeight;

	/*  Miscellaneous  */
	float towerRadius;
	sf::CircleShape dot = sf::CircleShape(1.f);

		/*  Private Functions  */

	//Collisions
	void merge(std::list<Follower>& fols,
		std::list<Follower>::iterator& fol_it);

	void setMinusBounce();

	void fixCenterVelocity();

	//Misc.
	void centerHeathText();

public:

Follower(sf::RenderWindow &window, float tRadius, sf::Color fColor = sf::Color::Black,
	int startHealth = 1, int startDmg = 1, int retrgtRate = 1, int redirRate = 2,
	float scale = 3.5f, bool showBoxes = true);


	//INITIALIZE FOLLOWER
	void initFollowerBox(FollowerShape &shape, bool showBoxes = true);

	void initHealthText();

	void randomSpawn();
	//End Init Methods


	/*  Setter Methods  */
	void setFollowerColor(const sf::Color &color);

	void setPosition(const sf::Vector2f& newPos);

	void setVelocity(const sf::Vector2f& vel);

	void setHealth(int newHealth);

	void setDamage(int newDmg);

	void setBounce(const sf::Vector2f& bnc);
	//End Setters


	/*  Accessor Methods  */
	sf::Vector2f getFollowerPosition();

	sf::Vector2f getFollowerVelocity();

	const sf::FloatRect& getGlobalBounds() const;

	int getHealth();

	int getDamage();

	int getMergeCount();

	sf::Vector2f getBounce();
	//End Accessor Methods


		/*  Functions  */

	//SET UP AND MANAGE FOLLOWER MOVEMENT
	void setNewVelocity(sf::Vector2f const &destinationVector, float speed = 3.f);


	//MOVE FOLLOWER LOGIC
	void moveLogic(bool collision, Player &player, std::vector<Tower> &towers);

	void moveFollower(sf::Vector2f const &vel);

	bool isBreakNeck(bool wasFollowing);

	//ACCELERATES FOLLOWER
	void accelerate(Player &player, bool decelerate = false);

	bool isFollowingPlayer(Player &player);


	//OUT OF BOUNDS AND FOLLOWER COLLISION BEHAVIOR
	void outOfBounds(sf::Vector2f &pos, bool col = false);

	bool towerCollision(Tower &tower);

	bool followerCollision(std::list<Follower>& fols,
		std::list<Follower>::iterator fol_it);

	//DAMAGE DEALING AND GIVING
	const int takeDamage(int dmg);

	/*		UPDATE		*/
	STATE update();

	void moveFollower();

	void shootFollower();

	void attackPlayer();

	//all need implementing

	//DRAW FOLLWER ASPECTS
	void drawFollower(sf::RenderWindow &window);

	//COPY CONSTRUCTOR
	Follower(const Follower &rhs);
};
	

