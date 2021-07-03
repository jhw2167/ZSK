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
#include "Other/functions.h"

//using statements
using std::list;
using std::shared_ptr;


//Global enum
enum class ObjType {PLR = 0, TOW, LSR, FOL, BUL, DRP, END};

//Forward delcaration of all coming classes:
class Tower;
class Bullet;
class PlayerShape;
class Player;
class FollowerShape;
class Follower;

/*
	Holds iterators to first and last of a specific
	object "set" such as players, followers etc.
*/

//Forward declare GameObj definition needed for struct Sublist
class GameObj;

struct SubList {
	std::list<GameObj*>::const_iterator start;
	std::list<GameObj*>::const_iterator end;

	SubList(std::list<GameObj*>::const_iterator s,
		list<GameObj*>::const_iterator t) :
		start(s), end(t) {};
};


class GameObj
{
private:
	static int objID;
	int id;
	std::list<GameObj*>::const_iterator self;

	//lists
	static std::shared_ptr<ListMap<GameObj*>> objs;
	static std::vector<SubList> subLists;
		

protected:
	
	//static properties - this objects should never be changed other
	//than via their static method thus they are private instances
	static std::shared_ptr<sf::RenderWindow> window_ptr;
	static std::shared_ptr<sf::Mouse> mouse_ptr;
	
	//Obj properties
	sf::Vector2f pos;
	ObjType type;


	/** FUNCTIONS **/
	virtual void addObj();
	virtual void remObj();
	//END FUNCTIONS

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

	
	static std::shared_ptr<Player> getNewPlayer();
	static std::shared_ptr<Tower> getNewTower();
	static std::shared_ptr<Follower> getNewFollower();
	static std::shared_ptr<Bullet> getNewBullet();
	//static std::shared_ptr<Drop> getNewBullet();

	//Modifiers
	static void setWindow(const std::shared_ptr<sf::RenderWindow>& window_pointer);
	static void setMouse(const std::shared_ptr <sf::Mouse>& mouse_pointer);

	static void setObjs(std::shared_ptr<ListMap<GameObj*>> list);
	static void initSublist();
	void setSublist(const SubList& sub, ObjType indx);
		

	//General, virtual functions
	virtual STATE update() = 0;


	
	//Static add/delete GameObj from the list
	template<class objType>
	static std::shared_ptr<GameObj> getNewGameObj();

	template<class objType>
	static std::shared_ptr<GameObj> removeGameObj(int objID);

	
	//copy constructor
	GameObj(const GameObj& rhs);

	//move constructor
	GameObj(GameObj&& rhs);

	//destructor
	~GameObj();
};

template<class objType>
inline std::shared_ptr<GameObj> GameObj::getNewGameObj()
{
	//Create new GameObj of child type: player, tower, follower etc.
	//and append it to the back of the lists subsection

	static_assert(std::is_base_of<GameObj, ObjType>::value, "ObjType must inherit from GameObj");
	std::shared_ptr<GameObj> obj(new objType());
	objs->insert(subLists.at(static_cast<size_t>(obj->getID())).end);
	return ;
}

template<class objType>
inline std::shared_ptr<GameObj> GameObj::removeGameObj(int objID)
{
	return std::shared_ptr<GameObj>();
}
