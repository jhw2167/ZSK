
//Main cpp file for running ZSK, include main.h for all includes
//and forward declared functions

#include "main.h"

int main(int argc, char *argv[])
{
	//coutTests();				
	//calls cout tests for creating cout variable statements

	//vectorTests();

	Game game;

	while (game.windowIsOpen())
	{
		//Update Game
		game.update();

		//Render Game
		game.render();
	}

	//getchar();

	return 0;
}
//END MAIN METHOD


//Run StartMenu
/******* TEMPORARILY BLOCKED *******

bool runStartMenu(sf::RenderWindow &window)
{
	static float wLength = window.getSize().x;
	static float wHeight = window.getSize().y;

	static bool init = false;

	static sf::Font arcade;
	static sf::Text title1;
	static sf::Text title2;

	static sf::Text subtitle1;

	static sf::Text startText;
	static sf::Text quitText;

	static sf::RectangleShape startRect;
	static sf::RectangleShape quitRect;
	static sf::RectangleShape settingsRect;

	init = (wLength == window.getSize().x) && (wHeight == window.getSize().y);

	if (!init)
	{
		float titleX = wLength / 2.f;
		float titleY = 40.f;

		sf::Vector2f titlePos = sf::Vector2f(titleX, titleY);
		sf::Vector2f rectOrigin = sf::Vector2f(0, 0);
		sf::Vector2f rectSize = sf::Vector2f(wLength / 2.f, 50.f);

		startRect.setOrigin(rectOrigin);

	}



}

*/



void movePlayerLogic(sf::RenderWindow &window, std::vector<Player> &players, std::vector<Tower> &towers)
{
	int towerNum = checkTowerCollision(players, towers);		//towerNum is initialized to element number  of tower player is colliding with
	enum dir { UP = 1, LEFT, DOWN, RIGHT };

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
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
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

}


//MOVES FOLLOWERS BASED ON VELOCITY CALCULATION IN FOLLOWER OBJECT
void moveFollowers(std::vector<Player> &players, std::vector<Follower> &activeFollowers, std::vector<Tower> &towers)
{
	
	

}

//HANDLES FOLLOWER BULLET INTERACTIONS
void shootFollowers(std::vector<Player> &players, std::vector<Follower> &activeFollowers)
{
	
}

//HANDELS FOLLOWERS ATTACKING A PLAYER; REDUCES PLAYER'S HEALTH
void attackPlayer(std::vector<Player> &players, std::vector<Follower> &activeFollowers)
{
	
}

//DRAWS FOLLOWERS IN WINDOW
void drawFollowers(sf::RenderWindow &window, std::vector<Follower> &activeFollowers)				//function to tell Follower objects to draw themselves
{
}

//END FUNCTIONS HANDLING FOLLOWERS
//***************************************//



//***************************************//
//BEGIN FUNCTIONS MANAGING TOWERS

void initializeTowers(sf::RenderWindow &window, std::vector<Tower> &towers, int numberOfTowers)		//sets up towers for game
{
}


int checkTowerCollision(std::vector<Player> &players, std::vector<Tower> &towers)
{
	return 0;
}


//HANDLING TOWER DRAWING
void drawTowers(sf::RenderWindow &window, std::vector<Tower> &towers)
{
	
}