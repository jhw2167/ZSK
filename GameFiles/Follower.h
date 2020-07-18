//manages Follower object that spawned randomly
#pragma once

//Project includes
#include "FollowerShape.h"
#include "Tower.h"
#include "../pch/stdafx.h"

class Follower
{
private:

	static int f_id;			//all followers have same f_id value that increments
	int id;						//each follower has unique id

	/*  Shape related  */
	FollowerShape fShape;
	sf::RectangleShape fBox;		
	//sets transparent box around follower for mechanics

	/*  Basic Stats */
	int health;
	int dmgDone;
	sf::Text healthText;
	static sf::Font arial;

	/*  Merging  */
	int mergeCount;
	static int maxMerge;

	/*  Position and Velocity  */
	sf::Vector2f fPosition;
	bool followingPlayer;

	sf::Vector2f fVelocity;									//speed and direction vector for moving followers
	float momentum;											//followers will gain speed as they follower a player
	int aUp, aLeft, aDown, aRight = 0;						//static ints will track how many times a follower has been accelerating in a given direction
	enum direction {STILL = 0, UP, LEFT, DOWN, RIGHT};		//declares enum direction to handle player movement

	short retargetRate;
	short retargetCount;

	short redirectRate;
	short redirectCount;

	float playersOldX;
	float playersOldY;


	sf::Vector2f bounce;			
	//vector with random x y coordinates for collisions

	/*  Window Variables */
	float windowLength;
	float windowHeight;

	/*  Miscellaneous  */
	float towerRadius;

		/*  Private Functions  */

	void merge(std::list<Follower>& fols,
		std::list<Follower>::iterator& fol_it);

	void setMinusBounce();

	void fixCenterVelocity();

public:

Follower(sf::RenderWindow &window, float tRadius, sf::Color fColor = sf::Color::Black,
	int startHealth = 1, int startDmg = 1, short retrgtRate = 10, short redirRate = 2, 
	float scale = 2.5f, bool showBoxes = true);


	//INITIALIZE FOLLOWER
	void initFollowerBox(FollowerShape &shape, bool showBoxes = true);

	void initHealthText();

	void randomSpawn();
	//End Init Methods


	/*  Setter Methods  */
	void setFollowerColor(sf::Color &color);

	void setPosition(sf::Vector2f &newPos);

	void setVelocity(sf::Vector2f &vel);

	void setHealth(int newHealth);

	void setDamage(int newDmg);
	//End Setters

	/*  Accessor Methods  */
	sf::Vector2f getFollowerPosition();

	sf::Vector2f getFollowerVelocity();

	sf::FloatRect getFollowerGlobalBounds();

	int get_id();

	int getHealth();

	int getDamage();

	int getMergeCount();
	//End Accessor Methods


		/*  Functions  */

	//SET UP AND MANAGE FOLLOWER MOVEMENT
	void setNewVelocity(sf::Vector2f const &destinationVector, float speed = 3.f);


	//MOVE FOLLOWER LOGIC
	void moveLogic(bool collision, Player &player, std::vector<Tower> &towers);

	void moveFollower(sf::Vector2f const &vel);

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

	//DRAW FOLLWER ASPECTS
	void drawFollower(sf::RenderWindow &window);




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
	

