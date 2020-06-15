
//Main cpp file for running ZSK, include main.h for all includes
//and forward declared functions

#include "main.h"

int main(int argc, char *argv[])
{
	//coutTests();				//calls cout tests for creating cout variable statements

	//vectorTests();


	float windowLength = 1500.f;
	float windowHeight = 1200.f;

	sf::RenderWindow window(sf::VideoMode(static_cast<int>(windowLength), static_cast<int>(windowHeight)), "Zombie Slayer Killer");
	window.setFramerateLimit(60);
	sf::RectangleShape gameArea = sf::RectangleShape(sf::Vector2f(windowLength, windowHeight));
	gameArea.setFillColor(sf::Color::Transparent);
	gameArea.setOrigin(windowLength / 2.f, windowHeight / 2.f);

	int numberOfPlayers = 1;
	sf::Vector2f startPos = sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f);
	Player player1(window, startPos);							//Must declare and initialize drawn objects AFTER window is created
	std::vector<Player> players;
	players.push_back(player1);

	//std::vector<Bullet> activeBullets;				//key vectors for managing bullets and followers
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
			//std::cout << "Event is: " << event.KeyPressed << std::endl;
			if (event.type == sf::Event::Closed){
				window.close();
			}

		}

		//MANAGE PLAYER

		//MOVE PLAYER
		movePlayerLogic(window, players, towers);
		//Calls move player function if keyboard is activated

		//SHOOTING
		shootingMechanics(window, mouseObject, players);
		//Directs shooting mechanics


		//MANAGE FOLLOWERS
		followerMechanics(window, mouseObject, players, activeFollowers,
			 towers);										//Directs follower mechanics



		//HANDLING THE WINDOW
		window.clear(sf::Color::White);
		//clears and draws elements in window


		//DRAWING

		players.at(0).drawPlayer(window);			//drawing player related elements
		drawFollowers(window, activeFollowers);
		//drawBullets(window, activeBullets);
		drawTowers(window, towers);

		//DISPLAY

		window.display();

	}

	getchar();

	return 0;
}
//END MAIN METHOD



void movePlayerLogic(sf::RenderWindow &window, std::vector<Player> &players, std::vector<Tower> &towers)
{
	int towerNum = checkTowerCollision(players, towers);		//towerNum is initialized to element number  of tower player is colliding with
	enum dir{ UP = 1, LEFT, DOWN, RIGHT };								
	
	for (size_t i = 0; i < players.size(); i++)
	{
		//moves player up if not at upwardbounds
	//Yes there needs to be a function call after each if to support directional travel
	//no, you cannot pass the key pressed event.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (players.at(i).getPlayerShape().getUpperBounds() > 0)
				players.at(i).moveLogic(UP, towerNum, towers.at(towerNum).getPosition(),
					towers.at(towerNum).getTowerRadius());
		}
		//move player left if not at left bounds
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			if (players.at(i).getPlayerShape().getLeftBounds() > 0)
				players.at(i).moveLogic(LEFT, towerNum, towers.at(towerNum).getPosition(),
					towers.at(towerNum).getTowerRadius());
		}
		//down
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			if (players.at(i).getPlayerShape().getLowerBounds() < window.getSize().y)
				players.at(i).moveLogic(DOWN, towerNum, towers.at(towerNum).getPosition(),
					towers.at(towerNum).getTowerRadius());
		}
		//and right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			if (players.at(i).getPlayerShape().getRightBounds() < window.getSize().x)
				players.at(i).moveLogic(RIGHT, towerNum, towers.at(towerNum).getPosition(),
					towers.at(towerNum).getTowerRadius());
		}

		/*Second parameter in function call accepts bool type, integer type is passed because any int > 0, (i.e. tower num 1,2,3 or 4)
		is interpreted as bool TRUE, if checkTowerColliion() fails to
		find colliding tower, it passes tower at elem 0 which is out of bounds*/


		//Grow follow area -- unrelated to movement but a good place to call
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) )
			players.at(i).growLargeFollowArea();
		else
			players.at(i).setLargeFollowerRadius(players.at(i).getMinLFR());
	}
	

}
//END PLAYER MOVEMENT LOGIC


//BEGIN SHOOTING MECHANICS AND RELEVANT FUNCTIONS

void shootingMechanics(sf::RenderWindow &window, sf::Mouse &mouseObject,
	std::vector<Player> &players)
{
	for (size_t i = 0; i < players.size(); i++)
	{
		players.at(i).shoot(mouseObject.getPosition(window));
		players.at(i).moveBullets();
		players.at(i).checkBulletInBounds(window);
	}
}


//*********************************************//
//BEGINS FOLLWER MECHANICS AND RELVANT FUNCTONS

void followerMechanics(sf::RenderWindow &window, sf::Mouse mouseObject,
	std::vector<Player> &players, std::vector<Follower> &activeFollowers,
	std::vector<Tower> &towers)
{
	float towerRadius = towers[0].getTowerRadius();
	spawnFollower(window, activeFollowers, towerRadius);
	moveFollowers(players, activeFollowers, towers);					

	shootFollowers(players, activeFollowers);
	attackPlayer(players, activeFollowers);

}


//SPAWNS FOLLOWERS THEN ADDS TO VECTOR
void spawnFollower(sf::RenderWindow &window, std::vector<Follower> &activeFollowers, float &towerRadius)				
//calls follower object to set followers position and velocity
{
	static int temperSpawnRate = 0; temperSpawnRate++;				//moderates spawn rate
	static int maxFollowers = 2;
	static int tmperRate = 50;

	if ((temperSpawnRate % tmperRate == 0) && (activeFollowers.size() < maxFollowers))
	{
		Follower follower(window, towerRadius);
		activeFollowers.push_back(follower) ;				//adds new follower to vector of active follower
		//std::cout << "Spawning fol, total num: " << activeFollowers.size() << std::endl;
	}

}


//MOVES FOLLOWERS BASED ON VELOCITY CALCULATION IN FOLLOWER OBJECT
void moveFollowers(std::vector<Player> &players, std::vector<Follower> &activeFollowers, std::vector<Tower> &towers)
{
	for (size_t i = 0; i < players.size(); i++) {
		for (size_t j = 0; j < activeFollowers.size(); j++)
		{
			activeFollowers[j].moveLogic(activeFollowers[j].followerCollision(activeFollowers, j),
				players.at(i), towers);
			//checks follower for follower collision then moves and adjust velocity as necesary
			//if follower is in collision with another follower, function "bounces" them off each other
			//otherwise just moves follwer at current velocity

		}
	}
	

}

//HANDLES FOLLOWER BULLET INTERACTIONS
void shootFollowers(std::vector<Player> &players, std::vector<Follower> &activeFollowers)
{
	std::vector<bool> erasefollower;
	for (size_t i = 0; i < players.size(); i++) {
		for (size_t j = 0; j < activeFollowers.size(); j++)
		{
			int dmg = players.at(i).shootFollower( 
				activeFollowers.at(j).getFollowerGlobalBounds() );

			//activeFollowers.takeDamage(dmg);

			if (dmg > 0) {
				activeFollowers.erase(activeFollowers.begin() + j);
				j--;
			}
		}

		//return array of followers shot by this player
		//aggregate all dead followers into 1 array by arr1 || arr2
		
	}
}

//HANDELS FOLLOWERS ATTACKING A PLAYER; REDUCES PLAYER'S HEALTH
void attackPlayer(std::vector<Player> &players, std::vector<Follower> &activeFollowers)
{
	for (size_t i = 0; i < players.size(); i++)
	{
		for (size_t j = 0; j < activeFollowers.size(); j++)
		{
			if (activeFollowers[j].getFollowerGlobalBounds().intersects(
				players.at(i).getHeartBounds()))	{	//if a follwer insects the player's global bounds

				int dmg = 1;					//later dmg = given followers damage
				players.at(i).takeDamage(dmg);	//reduce player's health
			}
		}
	}
	

}

//DRAWS FOLLOWERS IN WINDOW
void drawFollowers(sf::RenderWindow &window, std::vector<Follower> &activeFollowers)				//function to tell Follower objects to draw themselves
{
	for (size_t i = 0; i < activeFollowers.size(); i++) {
		activeFollowers[i].drawFollower(window);
	}
}

//END FUNCTIONS HANDLING FOLLOWERS
//***************************************//



//***************************************//
//BEGIN FUNCTIONS MANAGING TOWERS

void initializeTowers(sf::RenderWindow &window, std::vector<Tower> &towers, int numberOfTowers)		//sets up towers for game
{
	//adds an additional tower out of play that assists with mechanics
	for (size_t i = 0; i < numberOfTowers + 1; i++){
		towers.push_back(Tower(window, i));
	}
}


int checkTowerCollision(std::vector<Player> &players, std::vector<Tower> &towers)
{
	int collidingTower = 0;		//tower num (1-4) of colliding tower, or 0 for none
	//We can make this better, only check for collision if close to tower

	for (size_t i = 0; i < players.size(); i++)
	{
		for (size_t j = 0; j < towers.size(); j++)
		{
			if (towers[j].checkTowerCollision(players.at(i))) {
				collidingTower = j;
			}

		}
	}

	return collidingTower;
}


//HANDLING TOWER DRAWING
void drawTowers(sf::RenderWindow &window, std::vector<Tower> &towers)
{
	for (size_t i = 0; i < towers.size(); i++) {
		towers[i].drawTowers(window);
	}
}