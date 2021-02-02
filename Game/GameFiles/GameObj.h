#pragma once

/*
	Game object header file, all objects in the game will be 
	a subclass (inherited) of "GameObj" which has public:
		- position
		- obj type (enum)
		- ptr to gameState's objs vector holding all game objs
		- addObj(obj *) method 
		- constuctor

*/

/* Includes */
#include "../../BaseCode/Globals/Globals.h"

//Global enum
enum class ObjType {PLR = 0, BUL, FOL, TOW, LSR, DROP};

//Forward delcaration of all coming classes:
class Tower;
class Bullet;
class PlayerShape;
class Player;
class FollowerShape;
class Follower;



class GameObj
{
private:
	static int objID;
	int id;

	//maps
	static std::unordered_map<int, GameObj*>* objs;

	//functions
	void addObj(int obj_id);
	void remObj(int obj_id);

protected:
	//static properties
	static sf::RenderWindow *window;
	static sf::Vector2i mousePos;

	//Obj properties
	sf::Vector2f pos;
	ObjType type;

public:

	//list of collisions with other objects
	std::vector<GameObj*> collisions;

	/* Public Functions */
	GameObj(ObjType objType);

	//Accessors
	unsigned int getID() const;
	ObjType getType() const;
	sf::Vector2f getPos() const;
	virtual const sf::FloatRect& getGlobalBounds() const = 0;
	virtual STATE update() = 0;

	//Modifiers
	static void setWindow(sf::RenderWindow *win_ptr);
	static void setMousePos(sf::Vector2i& mousePos);

	static void setObjs(std::unordered_map<int,
		GameObj*>* vect);
	
	//copy constructor
	GameObj(const GameObj& rhs);

	//destructor
	~GameObj();
};

