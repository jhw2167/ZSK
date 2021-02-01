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
void GameObj::addObj(int obj_id) {
	/*
		Create a new pair and insert it into the map
		also, update the collision map
	*/
	(*objs)[obj_id] = this;
}

void GameObj::remObj(int obj_id) {
	objs->erase(objID);
}


/*  PUBLIC METHODS  */

//Constructor
GameObj::GameObj(ObjType objType)
{
	static int called = 0;
	type = objType;
	id = ++objID;
	addObj(id);
	printf("1. {%d} objID: %d, objSz: %d, Constr Called: %d, " 
		"ObjType: %d\n\n", id, objID, objs->size(), ++called, type);
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


/* Utility Constructors */

//Copy constructor
GameObj::GameObj(const GameObj& rhs) 
{
	//printf("Calling copy constr: this id: %d, rhs id %d\n",id, rhs.id);
	this->pos = rhs.pos;
	this->type = rhs.type;
	this->id = rhs.id;

	(*objs)[rhs.id] = this;
	printf("2. {%d} New id for this: %p\n", rhs.id, this);
}

//Destructor
GameObj::~GameObj() 
{
	/*
		If we have not removed *this* object from the objs
		list, we will go ahead and do that.
		This check is important due to copy constr mecahnics
		where we put a new ptr in our objs array
	*/

	printf("About to delete {%d}, visualizing data... size %d\n",
		id, objs->size());

	try
	{
		for (auto data : *objs) {
			printf("{%d} {%p}\n\n", data.first, data.second);
		}

		GameObj* inObjs = objs->find(id)._Ptr->_Myval.second;
		printf("3. {%d} ---DESTRUCTOR--- This ptr: %p, in objs: %p\n",
			id, this, inObjs);

		if (inObjs == this) {
			cout << "Erasing obj at id: " << id << endl;
			objs->erase(id);
		}
	}
	catch (...) {
		//destructor continues as normal
	}

	
}
