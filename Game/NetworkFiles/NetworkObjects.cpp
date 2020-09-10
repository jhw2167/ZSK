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

//Overloads for PKT_TYPE must come before Class "Contact"
sf::Packet& operator>>(sf::Packet& pkt, PKT_TYPE& type) {

	unsigned int temp = 0;
	pkt >> temp;
	type = static_cast<PKT_TYPE>(temp);

	return pkt;
}

sf::Packet& operator<<(sf::Packet& pkt, const PKT_TYPE& type) {

	unsigned int temp = 0;
	temp = type;
	pkt << temp;

	return pkt;
}


/*  Class Contact Definition  */

//Static Variable initialization
sf::IpAddress Contact::serverIP("192.168.1.12");
unsigned short Contact::serverPort = 5500;
unsigned short Contact::recPort = 3001;

Contact::Contact()
{
	//Only rec Socket needs to be bound
	recSocket.bind(recPort);
	recSocket.setBlocking(false);

	sendSocket.setBlocking(false);
	initBundle();
}

	/*  Private Methods  */
void Contact::initBundle() {
	core.ip = sf::IpAddress::getLocalAddress().toString();
}


	/*  Modifiers  */
void Contact::setIP(const NetworkObjects::ipBundle & myIP) {
	core = myIP;
}

//End Modifiers


/*  Accessors  */
NetworkObjects::ipBundle Contact::getBundle() const {
	return core;
}

void Contact::send(sf::Packet & toSend) {
	sendSocket.send(toSend, serverIP, serverPort);
}

void Contact::sendBundle(bool isHost)
{
	sf::Packet toSend;
	toSend << BNDL << core;
	core.isHost = isHost;

	if (isHost) {
		core.ping = 0;
		core.user = "Player 1";
		core.playerNum = 1;
		send(toSend);
	}
	else {
		core.user = "Player 0";
		send(toSend);
	}
}

PKT_TYPE Contact::receive(sf::Packet& toRec)
{
	PKT_TYPE type = NO_DATA_REC;

	if (recSocket.receive(toRec, serverIP, recPort) !=
		sf::Socket::Done)
	{
		cout << "No data receive from server\n";
		return type;
	}

	toRec >> type;
	return type;
}

//End Accessors


/*  Other Methods  */



//End Class Contact

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


	/*  IP Bundle  */
sf::Packet & operator>>(sf::Packet & pkt, ipBundle & obj) 
{
	/*	Extraction operator for ipbundle  */

	pkt >> obj.ip;
	pkt >> obj.playerNum;
	pkt >> obj.user;
	pkt >> obj.ping;

	return pkt;
}

sf::Packet & operator<<(sf::Packet & pkt, const ipBundle obj)
{
	/*	Insertion operator for ipbundle  */

	pkt << obj.ip;
	pkt << obj.playerNum;
	pkt << obj.user;
	pkt << obj.ping;

	return pkt;
}

//End Vector overloads
