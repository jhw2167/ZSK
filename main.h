//main.h file
#pragma once

//Main file brings all objects together to create the game
#include "Game.h"
#include "coutTests.h"

//FUNCTONS HANDLING PLAYER
void movePlayerLogic(sf::RenderWindow &window, std::vector<Player> &players, std::vector<Tower> &towers);

//ALL FUNCTIONS HANDLING BULLETS
void shootingMechanics(sf::RenderWindow &window, sf::Mouse &mouseObject,
	std::vector<Player> &players);


//ALL FUNCTIONS HANDLING FOLLOWERS
void followerMechanics(sf::RenderWindow &window, sf::Mouse mouseObject,
	std::vector<Player> &players, std::vector<Follower> &activeFollowers,
	std::vector<Tower> &towers);

//SPAWNS FOLLOWERS THEN ADDS TO VECTOR
void spawnFollower(sf::RenderWindow &window, std::vector<Follower> &activeFollowers, float &towerRadius);

//MOVES FOLLOWERS BASED ON VELOCITY CALCULATION IN FOLLOWER OBJECT
void moveFollowers(std::vector<Player> &players, std::vector<Follower> &activeFollowers, std::vector<Tower> &towers);

//ASSESS IF FOLLOWERS HAVE BEEN SHOT BY A PLAYER AND DELETES OBJECTS ACCORDING
void shootFollowers(std::vector<Player> &players, std::vector<Follower> &activeFollowers);

//HANDLES ZOMBIES ATTACKING A PLAYER
void attackPlayer(std::vector<Player> &players, std::vector<Follower> &activeFollowers);

//DRAWS FOLLOWERS IN WINDOW
void drawFollowers(sf::RenderWindow &window, std::vector<Follower> &activeFollowers);


//ALL FUNCTIONS HANDLING TOWERS
void initializeTowers(sf::RenderWindow &window, std::vector<Tower> &towers, int numberOfTowers);

//HANDLES POTENTIAL PLAYER-TOWER COLLISIONS
int checkTowerCollision(std::vector<Player> &players, std::vector<Tower> &towers);

//DRAWS TOWERS ON MAP
void drawTowers(sf::RenderWindow &window, std::vector<Tower> &towers);


//Define Global STRUCT datatype -- StartMenu



//INITIALIZE STATIC MEMBERS OF OBJECTS

//Player object
float Player::healthBarHeight = 30.f;
float Player::areaOutline = 4.f;
sf::Color Player::pColors[] = {sf::Color::Red, sf::Color::Blue,
	sf::Color::Green, sf::Color::Yellow};

FollowerShape Player::scoreFigure = FollowerShape(sf::Color::Black, 3.f);
PlayerShape Player::lifeFigure = PlayerShape(2.5f);

sf::Font Player::arial;

//follower objects
int Follower::f_id = 0;
sf::Font Follower::arial;

//TESTS

void vectorTests()
{
	std::cout << " Our new test " << std::endl << std::endl;
	std::vector<int> nums{ 2, 5, 7 };

	for (size_t i = 0; i < nums.size(); i++)
	{
		std::cout << "Nums at i = " << i << " is " << nums[i] << std::endl;
		std::cout << "Nums size is: " << nums.size() << std::endl;
		nums.erase(nums.begin());
		i--;
	}

	getchar();

}