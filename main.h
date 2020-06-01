/*Zombie Slayer Killer (ZSK) early alpha code, main.h file
ZSK is a third person, 2D simplistic shooter/follower arcade game
with a bit of a twist adding the tower dynamic to assist zombie slaying*/

// Visual Studious Visual C++ 2017 version 15.9.5
// SMFL for Visual C++ 15, version 2.5.1 for 32 bit OS
//Last updated *5/30/2020*

#pragma once

//Main file brings all objects together to create the game

//SFML includes
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

//Std lib includes
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
#include <cstdlib>

//Project includes
#include "FollowerObject.h"
#include "coutTests.h"

//FUNCTONS HANDLING PLAYER
void movePlayerLogic(Player &player1, std::vector<Tower> &towers, float windowLength, float windowHeight);


//ALL FUNCTIONS HANDLING BULLETS
void shootingMechanics(sf::RenderWindow &window, sf::Mouse mouseObject, Player player1, std::vector<Bullet> &activeBullets);

Bullet addBullet(sf::Vector2i cursorVect, Player &player1);

void moveBullets(std::vector<Bullet> &activeBullets);

void deleteBullets(sf::RenderWindow &window, std::vector<Bullet> &activeBullets);

void drawBullets(sf::RenderWindow &window, std::vector<Bullet> &activeBullets);


//ALL FUNCTIONS HANDLING FOLLOWERS
void followerMechanics(sf::RenderWindow &window, sf::Mouse mouseObject,
	Player &player1, std::vector<Follower> &activeFollowers, std::vector<Bullet> &activeBullets,
	std::vector<Tower> &towers);

//SPAWNS FOLLOWERS THEN ADDS TO VECTOR
Follower spawnFollower(sf::RenderWindow &window, Player &player1);

//MOVES FOLLOWERS BASED ON VELOCITY CALCULATION IN FOLLOWER OBJECT
void moveFollowers(Player &player1, std::vector<Follower> &activeFollowers, std::vector<Tower> &towers);

//ASSESS IF FOLLOWERS HAVE BEEN SHOT BY A PLAYER AND DELETES OBJECTS ACCORDING
void shootFollowers(std::vector<Follower> &activeFollowers, std::vector<Bullet> &activeBullets);

//HANDLES ZOMBIES ATTACKING A PLAYER
void attackPlayer(Player &player1, std::vector<Follower> &activeFollowers);

//DRAWS FOLLOWERS IN WINDOW
void drawFollowers(sf::RenderWindow &window, std::vector<Follower> &activeFollowers);


//ALL FUNCTIONS HANDLING TOWERS
void initializeTowers(sf::RenderWindow &window, std::vector<Tower> &towers, int numberOfTowers);

//HANDLES POTENTIAL PLAYER-TOWER COLLISIONS
int checkTowerCollision(Player &player1, std::vector<Tower> &towers);

//DRAWS TOWERS ON MAP
void drawTowers(sf::RenderWindow &window, std::vector<Tower> &towers);


