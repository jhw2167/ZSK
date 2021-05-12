#include "GameObj.h"

/*
	Implementation file for GameObj.h implementing
	our abstract game object class
*/

//static initilization
std::shared_ptr<std::list<GameObj*>> GameObj::objs = nullptr;

int GameObj::objID = 0;


/* PRIVATE METHODS  */

//ADD object when created
void GameObj::addObj() {
	
	//GameObject puts itself onto the linked list

	objs->push_back(this);
	self = objs->end();
}

void GameObj::remObj() {
	/*
		Remove object from the LL and assign const
		iterator to the correct next obj
	*/
	objs->erase(self);
}


/*  PUBLIC METHODS  */

//Constructor
GameObj::GameObj(ObjType objType)
{
	static int called = 0;
	type = objType;
	id = ++objID;
	addObj();
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


/* STATIC Setters */

void GameObj::setWindow(const std::shared_ptr<sf::RenderWindow>& window_pointer) {
	window_ptr = window_pointer;
}

void GameObj::setMouse(const std::shared_ptr<sf::Mouse>& mouse_pointer) {
	mouse_ptr = mouse_pointer;
}

//One time per game SET Objs game vector pointer
void GameObj::setObjs(std::shared_ptr<std::list<GameObj*>> list) {
	objs = list;
}

//init our subLists from static function call
void GameObj::initSublist() {

	/*
		Initiate sublist pointers to null values (before obj
		vector is added to) using objs->begin
		- Use std::move to avoid unecessary copying
	*/

	int i = static_cast<int>(ObjType::PLR);
	int end = static_cast<int>(ObjType::END);

	while(i++ != end) {
		subLists.push_back(std::move(SubList(objs->begin(), objs->begin())));
	}
}

//Set specific subList
void GameObj::setSublist(const SubList& sub, ObjType indx) {
	subLists.at(static_cast<int>(indx)) = sub;
}

//END STATIC METHODS

/* Utility Constructors */



//Copy constructor
GameObj::GameObj(const GameObj& rhs) 
{
	//printf("Calling copy constr: this id: %d, rhs id %d\n",id, rhs.id);
	this->pos = rhs.pos;
	this->type = rhs.type;
	this->id = rhs.id;

	remObj();
	addObj();
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
	addObj();
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
