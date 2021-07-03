#pragma once

/*
	Datastructure ListMap for constant time insertion, 
	deletion and random access.

	Author: Jack H. Welsh, 5/5/21
*/

//includes
#include "../pch/stdafx.h"
#include "../Exceptions/Exceptions.h"

template <typename T>
class ListMap {

private:

	//Variables
	std::list<T> list;
	std::unordered_map<int, typename std::list<T>::iterator > map;
	const static size_t DEF_MAP_CAP;

	//Pointer to ID function
	int (*getID)(T);

public:

	/*	Constructors  */
	ListMap();
	ListMap(size_t reserveCapacity);
	ListMap(int idFunction(T), size_t reserveCapacity);


	/*	Accessors  */
	size_t listSize();
	size_t mapSize();
	size_t mapCapacity();
	int getIDFromFunction(T obj);
	T& at(int id);
	typename std::list<T>::iterator atIterator(int id);
	typename std::list<T>::iterator begin();
	typename std::list<T>::iterator end();
	typename std::list<T>* getList();

	/*	Modifiers  */
	boolean setMapCapacity(size_t newCapacity = DEF_MAP_CAP);
	void setIDFunction(int idFunction(T));

	/*	Inserters  */
	typename std::list<T>::iterator insert(T obj, const typename std::list<T>::iterator& before);
	typename std::list<T>::iterator push_front(T obj);
	typename std::list<T>::iterator push_back(T obj);


	/*	Erasers */
	T& erase(int id);

	/*  Clear Methods  */
	size_t clear() noexcept;
	void clearAll() noexcept;
};

/*
	Template function must exist in the header file because
	they provide the compiler patterns from which to generate
	the source code needed for compilation of a specific
	instance of the template.
*/


/*	Constructors  */
template<class T>
ListMap<T>::ListMap()
{
	/*
		T MUST be a pointer to an object that holds
		a UNIQUE ID value, stored internally by the object, that
		the value will be hashed by - else use mem address.
	*/

	//assert that T is of type pointer
	static_assert(std::is_pointer<T>::value, "Type T must be pointer : ListMap.h");
	setIDFunction([](T obj) { return reinterpret_cast<int>(obj); });
}

template<class T>
ListMap<T>::ListMap(size_t reserveCapacity)
{
	//Assert that type T must be a ptr
	//Allocate capacity to map
	ListMap();
	setMapCapacity(reserveCapacity);
}


template<class T>
ListMap<T>::ListMap(int idFunction(T), size_t reserveCapacity)
{
	//Assert that type T must be a ptr
	//Allocate capacity to map
	ListMap();
	setIDFunction(idFunction);
	setMapCapacity(reserveCapacity);
}


/*  Accessors  */

template <class T>
size_t ListMap<T>::listSize() {
	return list.size();
}

template <class T>
size_t ListMap<T>::mapSize() {
	return map.size();
}

template <class T>
size_t ListMap<T>::mapCapacity() {
	return map.max_size();
}

template <class T>
int ListMap<T>::getIDFromFunction(T obj) {
	return getID(obj);
}

template<class T>
T& ListMap<T>::at(int id)
{
	/*
		Returns T* at provided map index
		-	Throws out_of_range if index DNE
		-	T=GameObj* will be nullptr if
			removed from the list
	*/

	//may throw out_of_range, to be caught by caller of at()
	typename std::list<T>::iterator val = atIterator(id);
	if (val == list.end())
		throw no_such_object("GameObj Expired at id" + id);

	return val._Ptr->_Myval;
}


template<class T>
typename std::list<T>::iterator ListMap<T>::atIterator(int id)
{
	/*
		Returns iterator at provided map index
		-	Throws out_of_range if index DNE
		-	T=GameObj* will be nullptr if
			removed from the list
	*/

	return map.at(id);
}

//Get first entry in the list
template<class T>
typename std::list<T>::iterator ListMap<T>::begin() {
	return list.begin();
}

//Get last entry in the list
template<class T>
typename std::list<T>::iterator ListMap<T>::end() {
	return list.end();
}


//Returns a ptr to the list that exist internally in this object
template<class T>
typename std::list<T>* ListMap<T>::getList() {
	return &list;
}


/*	Modifiers  */
template <class T>
boolean ListMap<T>::setMapCapacity(size_t newCapacity) {

	/*
		Checks if requested capacity has already been
		returned and returns false if so -
		ELSE - newCapacity is reserved, a rehash is
		triggered and the method is O(n)
	*/

	if (map.max_size() < newCapacity) {
		map.reserve(newCapacity);
		return true;
	}

	return false;
}

template <class T>
void ListMap<T>::setIDFunction(int id(T)) {
	/*  MAKES IMPLICIT CALL TO CLEAR ALL,
	sets new id function else we may lose
	lots of data  */

	clearAll();
	getID = id;
}



/*  Insertion Function  */
template<class T>
typename std::list<T>::iterator ListMap<T>::insert(T obj, const typename std::list<T>::iterator& before) {

	/*
		- Checks if object item is novel to ListMap
			- Throws invalid argument if id is not novel
		- Inserts object into list
		- sets iterator equal to map[id]
		- returns iterator
	*/

	//get object unique ID
	int id = getID(obj);

	try {
		at(id);
	}
	catch (no_such_object& nso) {
		std::string what = nso.what();
		what += "\nncannot insert new object at this id\n";
		throw no_such_object(what);
	}
	catch (const std::out_of_range& oor) {
		fprintf(stderr, "ID: %d unused, we listMap may insert this object\n\n", id);
	}
	catch (const std::exception& e) {
		fprintf(stderr, "\nUnknown exception caught in ListMap<T>::insert when attempting to check use of id: %d\n", id);
		std::cerr << e.what() << endl;
	}

	//Insert obj into list
	typename std::list<T>::iterator loc = list.insert(before, obj);

	//Map to id value
	map[id] = loc;
	return loc;
}

template<class T>
typename std::list<T>::iterator ListMap<T>::push_front(T obj) {
	/*
		To push object onto front of list we insert before
		the "first" element of the list.
		- insert performs all necessary errro checking
	*/

	insert(obj, list.begin());
}

template<class T>
typename std::list<T>::iterator ListMap<T>::push_back(T obj) {

	/*
		To push object onto back of list we insert before
		the "after last" element of the list.
		- insert performs all necessary errro checking
	*/

	insert(obj, list.end());
}


/*  Erasers  */

template <class T>
T& ListMap<T>::erase(int id)
{
	/* Removes element at id,
		- sets map iterator to list<T>::end() at id
		- returns T, pointer to GameObj
		- throws out_of_range if ID doesnt exist
	*/

	//throws out of range
	typename std::list<T>::iterator iter = map.at(id);

	//set to end() in map, remove from list
	map[id] = list.end();
	T& val{ iter._Ptr->_Myval };
	list.erase(iter);

	return val;
}


/*  Clear Methods  */
template <class T>
size_t ListMap<T>::clear() noexcept
{
	/* Clears the entire map, reloads all
	values in the list back into the map with
	their internally stored ID's
	- function to generate ID's must be passed
	*/

	//clear map
	size_t cap = map.max_size();
	map.clear();
	map.reserve(cap);

	//iterate over LL
	auto elem = list.begin();
	while (elem != list.end()) {
		map[getID(elem._Ptr->_Myval)] = elem;
		++elem;
	}

	//return size
	return map.size();
}


template <class T>
void ListMap<T>::clearAll() noexcept {
	map.clear();
	setMapCapacity();
	list.clear();
}
