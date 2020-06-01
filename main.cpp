
//Main cpp file for running ZSK, include main.h for all includes
//and forward declared functions

#include "main.h"

int main(int argc, char *argv[])
{
	//coutTests();				//calls cout tests for creating cout variable statements

	float windowLength = 1200.f;
	float windowHeight = 800.f;

	sf::RenderWindow window(sf::VideoMode(static_cast<int>(windowLength), static_cast<int>(windowHeight)), "Zombie Slayer Killer");
	window.setFramerateLimit(60);

	int numberOfPlayers = 1;
	Player player1(window);							//Must declare and initialize drawn objects AFTER window is created

	std::vector<Bullet> activeBullets;				//key vectors for managing bullets and followers
	std::vector<Follower> activeFollowers;
	std::vector<Tower> towers;
	int numberOfTowers = 4;


	initializeTowers(window, towers, numberOfTowers);		//sets up towers for play
	

	while (window.isOpen())
	{
		//clock_t myClock = clock();

		sf::Event event;
		
		sf::Mouse mouseObject;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

		}

		//MANAGE PLAYER

		//MOVE

		movePlayerLogic(player1, towers, windowLength, windowHeight);					
		//Calls move player function if keyboard is activated


		//SHOOTING
		shootingMechanics(window, mouseObject, player1, activeBullets);		
		//Directs shooting mechanics


		//MANAGE FOLLOWERS
		followerMechanics(window, mouseObject, player1, activeFollowers,
			activeBullets, towers);										//Directs follower mechanics

		//HANDLING THE WINDOW
		window.clear(sf::Color::White);		
		//clears and draws elements in window


		//DRAWING

		player1.drawPlayer(window);			//drawing player related elements
		player1.drawHealthBar(window);

		drawFollowers(window, activeFollowers);
		drawBullets(window, activeBullets);
		drawTowers(window, towers);

		//DISPLAY

		window.display();

	}


	return 0;
}
//END MAIN METHOD

void movePlayerLogic(Player &player1, std::vector<Tower> &towers, float windowLength, float windowHeight)
{
	int towerNum = checkTowerCollision(player1, towers);		//towerNum is initialized to element number  of tower player is colliding with
																//or 0 if no collision
	float playerMoveSpeed = 5.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))			//moves player up if not at upwardbounds
	{
		if (player1.getPlayerShape().getUpperBounds() > 0)
			player1.movePlayer(1, towerNum, towers.at(towerNum).getPosition(),
				towers.at(towerNum).getTowerRadius(), playerMoveSpeed);
				/*Second parameter in function call accepts bool type, integer type is passed because any int > 0, (i.e. tower num 1,2,3 or 4)
				is interpreted as bool TRUE, if checkTowerColliion() fails to 
				find colliding tower, it passes tower at elem 0 which is out of bounds*/
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))			//move player left if not at left bounds
	{
		if (player1.getPlayerShape().getLeftBounds() > 0)
			player1.movePlayer(2, towerNum, towers.at(towerNum).getPosition(),
				towers.at(towerNum).getTowerRadius(), playerMoveSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))			//down
	{
		if (player1.getPlayerShape().getLowerBounds() < windowHeight)
			player1.movePlayer(3, towerNum, towers.at(towerNum).getPosition(),
				towers.at(towerNum).getTowerRadius(), playerMoveSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))			//and right
	{
		if (player1.getPlayerShape().getRightBounds() < windowLength)
			player1.movePlayer(4, towerNum, towers.at(towerNum).getPosition(),
				towers.at(towerNum).getTowerRadius(), playerMoveSpeed);
	}

}
//END PLAYER MOVEMENT LOGIC


//BEGIN SHOOTING MECHANICS AND RELEVANT FUNCTIONS
void shootingMechanics(sf::RenderWindow &window, sf::Mouse mouseObject, Player player1, std::vector<Bullet> &activeBullets)
{
	static int temperShooting = 0;					//tempershooting will prevent players from shooting excessively

	if (temperShooting > 10)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			activeBullets.push_back(addBullet(mouseObject.getPosition(window), player1));		//adds bullet to vector of active bullets
			temperShooting = 0;
		}
	}
	temperShooting++;					//variable is iterated continuosly to allow multiple shots

	moveBullets(activeBullets);

	drawBullets(window, activeBullets);

	deleteBullets(window, activeBullets);

}

//ADD BULLETS
Bullet addBullet(sf::Vector2i cursorVect, Player &player1)				
//calls bulletObject to shoot out a bullet from player to cursor
{
	Bullet bullet(player1.getGunPosition(), cursorVect);
	return bullet;
}


//MOVE BULLETS
void moveBullets(std::vector<Bullet> &activeBullets)
{
	for (size_t i = 0; i < activeBullets.size(); i++)
	{
		activeBullets[i].moveBullet();
	}
}

//DELETE BULLETS
void deleteBullets(sf::RenderWindow &window, std::vector<Bullet> &activeBullets)
{
	for (size_t i = 0; i < activeBullets.size(); i++)
	{
		if (activeBullets[i].isOutOBounds(window))
		{
			activeBullets.erase(activeBullets.begin() + i);
		}
		
	}
	
}


//DRAW BULLETS
void drawBullets(sf::RenderWindow &window, std::vector<Bullet> &activeBullets)				//function to tell bullet objects to draw themselves
{
	for (size_t i = 0; i < activeBullets.size(); i++)
	{
		activeBullets[i].drawBullet(window);
	}

}

//END SHOOTING MECHANICS AND RELEVANT FUNCTIONS


//*********************************************//
//BEGINS FOLLWER MECHANICS AND RELVANT FUNCTONS

void followerMechanics(sf::RenderWindow &window, sf::Mouse mouseObject,
	Player &player1, std::vector<Follower> &activeFollowers, std::vector<Bullet> &activeBullets,
	std::vector<Tower> &towers)
{

	static int temperSpawnRate = 0; temperSpawnRate++;				//moderates spawn rate
	static int maxFollowers = 32;
	static int tmperRate = 10;
	
	if ((temperSpawnRate % tmperRate == 0) && (activeFollowers.size() < maxFollowers))
	{
		activeFollowers.push_back(spawnFollower(window, player1));				//adds new follower to vector of active follower
		//std::cout << "Spawning num: " << activeFollowers.size() << std::endl;
	}
	
	moveFollowers(player1, activeFollowers, towers);					//moves followers
	shootFollowers(activeFollowers, activeBullets);
	attackPlayer(player1, activeFollowers);

}


//SPAWNS FOLLOWERS THEN ADDS TO VECTOR
Follower spawnFollower(sf::RenderWindow &window, Player &player1)				//calls follower object to set followers position and velocity
{
	Follower follower(window);
	follower.randomSpawn();

	return follower;
}


//MOVES FOLLOWERS BASED ON VELOCITY CALCULATION IN FOLLOWER OBJECT
void moveFollowers(Player &player1, std::vector<Follower> &activeFollowers, std::vector<Tower> &towers)
{
	for (size_t i = 0; i < activeFollowers.size(); i++)
	{
		activeFollowers[i].moveFollower(activeFollowers[i].followerCollision(activeFollowers, i), player1, towers);
		//checks follower for follower collision then moves and adjust velocity as necesary
		//if follower is in collision with another follower, function "bounces" them off each other
		//otherwise just moves follwer at current velocity
	}

}

//HANDLES FOLLOWER BULLET INTERACTIONS
void shootFollowers(std::vector<Follower> &activeFollowers, std::vector<Bullet> &activeBullets)
{

	for (size_t i = 0; i < activeBullets.size(); i++)
	{
		for (size_t j = 0; j < activeFollowers.size(); j++)
		{
			if (activeBullets.at(i).getBulletGlobalBounds().intersects(			//checks to see if bullet intersects each follower
				activeFollowers.at(j).getFollowerGlobalBounds()))
			{
				//std::cout << "size BEFORE:  " << activeBullets.size() << std::endl;
				activeBullets.erase(activeBullets.begin() + i);
				//std::cout << "    size AFTER:  " << activeBullets.size() << std::endl;
				activeFollowers.erase(activeFollowers.begin() + j);
				break;
			}
		}
	}
}

//HANDELS FOLLOWERS ATTACKING A PLAYER; REDUCES PLAYER'S HEALTH
void attackPlayer(Player &player1, std::vector<Follower> &activeFollowers)
{
	for (size_t i = 0; i < activeFollowers.size(); i++)
	{
		if (activeFollowers[i].getFollowerGlobalBounds().intersects(player1.getPlayerBounds()))		//if a follwer insects the player's global bounds
		{
			player1.adjHealth(-1);	//reduce player's health
		}
	}

}


//DRAWS FOLLOWERS IN WINDOW
void drawFollowers(sf::RenderWindow &window, std::vector<Follower> &activeFollowers)				//function to tell Follower objects to draw themselves
{

	for (size_t i = 0; i < activeFollowers.size(); i++)
	{
		activeFollowers[i].drawFollower(window);
	}

}

//END FUNCTIONS HANDLING FOLLOWERS
//***************************************//



//***************************************//
//BEGIN FUNCTIONS MANAGING TOWERS

void initializeTowers(sf::RenderWindow &window, std::vector<Tower> &towers, int numberOfTowers)		//sets up towers for game
{
	Tower newTower;

	for (size_t i = 0; i < numberOfTowers + 1; i++)			//adds an additional tower out of play that assists with mechanics
	{
		towers.push_back(newTower);
		towers[i].setPosition(window, i);
	}
}


int checkTowerCollision(Player &player1, std::vector<Tower> &towers) 
{
	int collidingTower = 0;		//tower num (1-4) of colliding tower, or 0 for none
	//We can make this better, only check for collision if close to tower
	for (size_t i = 0; i < towers.size(); i++)
	{
		if (towers[i].checkTowerCollision(player1.getPosition()))
			collidingTower = i;
	}

	return collidingTower;
}


//HANDLING TOWER DRAWING
void drawTowers(sf::RenderWindow &window, std::vector<Tower> &towers)
{
	for (size_t i = 0; i < towers.size(); i++) 
	{
		towers[i].drawTowers(window);
	}
}