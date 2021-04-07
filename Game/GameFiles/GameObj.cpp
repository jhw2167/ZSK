#include "GameObj.h"

/*
	Implementation file for GameObj.h implementing
	our abstract game object class
*/

//static initilization
std::list<GameObj*>* 
	GameObj::objs = nullptr;

int GameObj::objID = 0;


/* PRIVATE METHODS  */

//ADD object when created
void GameObj::addObj(int obj_id) {
	/*
		GameObject puts itself onto the linked list
	*/
	id = obj_id;
	objs->push_back(this);
	self = objs->end();
}

void GameObj::remObj() {
	objs->erase(self);
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

void GameObj::setWindow(sf::RenderWindow * win_ptr) {
	window = win_ptr;
}

void GameObj::setMousePos(sf::Vector2i & mousePosition) {
	mousePos = mousePosition;
}

//One time per game SET Objs game vector pointer
void GameObj::setObjs(std::list<GameObj*>* list) {
	objs = list;
}


/* Utility Constructors */

//Copy constructor
GameObj::GameObj(const GameObj& rhs) 
{
	//printf("Calling copy constr: this id: %d, rhs id %d\n",id, rhs.id);
	this->pos = rhs.pos;
	this->type = rhs.type;
	this->id = rhs.id;

	remObj();
	addObj(this->id);
	printf("2. {%d} New id for this: %p\n", rhs.id, this);
}

//move constructor
GameObj::GameObj(GameObj&& rhs)
{
	//printf("Calling copy constr: this id: %d, rhs id %d\n",id, rhs.id);
	this->pos = rhs.pos;
	this->type = rhs.type;
	this->id = rhs.id;

	remObj();
	addObj(this->id);
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
	bool shouldRemove = 0;

	try
	{
		//Print all items remaining in list for reference
		for (auto data : *objs) {
			printf("{%d} {%p}\n\n", data->id, data);

			//check for *this* item
			if (data->id == this->id)
				shouldRemove = 1;

		}

		if (shouldRemove)
			printf("3. {%d} ---DESTRUCTOR--- This ptr: %p, in objs\n",
				id, this);
		else
			printf("Object did not exist, no deletio\n\n");

		
		//Remember to actually remove the object here!!
		//REMOVE_OBJ
	}
	catch (...) {
		//destructor continues as normal
	}

	
}
