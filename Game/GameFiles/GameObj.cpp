#include "GameObj.h"

/*
	Implementation file for GameObj.h implementing
	our abstract game object class
*/

//static initilization
std::unordered_map<int, GameObj*>* 
	GameObj::objs = nullptr;

int GameObj::objID = 0;


/* PRIVATE METHODS  */

//ADD object when created
void GameObj::addObj() {
	/*
		Create a new pair and insert it into the map
		also, update the collision map
	*/
	id = objID++;
	(*objs)[id] = this;
}


/*  PUBLIC METHODS  */

//Constructor
GameObj::GameObj(ObjType objType)
{
	static int called = 0;
	type = objType;
	id = -1;
	addObj();
	printf("id: %d, objID: %d, objSz: %d, Constr Called: %d\n\n",
		id, objID, objs->size(), ++called);
}

//Returns objects id
unsigned int GameObj::getID() const  {
	return id;
}

//Returns obj type
ObjType GameObj::getType() const  {
	return type;
}

//Returns object position as a vector
sf::Vector2f GameObj::getPos() const  {
	return pos;
}

//One time per game SET Objs game vector pointer
void GameObj::setObjs(std::unordered_map<int, GameObj*>* vect) {
	objs = vect;
}

//Copy constructor
GameObj::GameObj(const GameObj& rhs) {
	cout << "Calling copy constr " << id  << endl;
}

//Destructor
GameObj::~GameObj() 
{
	cout << "Calling destr const " << id << endl;
	objs->erase(id);
}
