#include "NetworkObjects.h"

/*
	Implementation file for network objects.h file
*/

namespace NetworkObjects {

	/*  Struct IPBundle Implementation  in .h */

	/*  Struct lobbyInfo Implementation  in .h */

	/*  Struct clientDataPkt Implementation  in .h */

	/*  Struct gameInfoPkt Implementation  in .h */
}


/*  Operator Overloads for Packet loading/unloading */

	/*  Vectors  */

sf::Packet& operator>>(sf::Packet& pkt, sf::Vector2f& obj) {
	pkt >> obj.x >> obj.y;
	return pkt;
}

sf::Packet& operator<<(sf::Packet& pkt, const sf::Vector2f& obj) {
	pkt << obj.x << obj.y;
	return pkt;
}