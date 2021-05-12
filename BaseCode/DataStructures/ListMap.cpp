#include "ListMap.h"

//Implementation file for ListMap.h

//Variables
template <class T>
const size_t ListMap<T>::DEF_MAP_CAP{ 10 };

/*	Constructors  */
//ListMap<T>();	-	template, inline
//ListMap<T>(size_t reserveCapacity); - template, inline


/*	Accessors  */

//T ListMap<T>::at(int id) - template, inline
//std::list<T>::iterator getFirst(); -template, inline
//std::list<T>::iterator getLast(); - template, inline

/*	Modifiers  */
template <class T>
boolean ListMap<T>::setMapCapacity(size_t newCapacity ) {
	
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


/*	Inserters  */
//std::list<T>::iterator push_back(T obj, int id) - template, inline
//std::list<T>::iterator push_front(T obj, int id) - template, inline
//std::list<T>::iterator push_back(T obj, int id); - template, inline


/*	Erasers */
//T erase(std::list<T>::iterator loc), template, inline
//T erase(int id) - template, inline

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
	while(elem != list.end()) {
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