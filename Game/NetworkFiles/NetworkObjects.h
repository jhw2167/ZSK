#include "../../BaseCode/pch/stdafx.h"

/*
	We need to create a few network objects
	that will simplify the sending and receiving
	of packages during the game and in
	the lobby state
*/

namespace NetworkObjects {

	/*  Fundamental Networking items  */

	/*
		IPBundle pairs an ip address with
		a playerNumber, username and ping from host
	*/

	struct ipBundle {
		std::string ip;
		short playerNum;
		std::string user;

		int ping;

		ipBundle(std::string ip1 = "192.168.1.1", short pNum = 0,
			std::string user1 = "Player",
			int ping1 = -1) :
			ip(ip1), playerNum(pNum), user(user1),
			ping(ping1) {};

	};

	/*
		lobby info is managed by the host and updated whenever
		a new player connects to the server and sent to all players
	*/

	struct  lobbyInfo
	{
		std::string gameID;
		std::vector<ipBundle> allPlayers;
		short numPlayers;

		lobbyInfo(std::string id = "AAAAA",
			const std::vector<ipBundle>& players = std::vector<ipBundle>(),
			short totalPlayers = 1) : gameID(id), allPlayers(players),
			numPlayers(totalPlayers) {};
	};


	/*  Standardized packages  */

	//reqPkt - 1
	/*
		reqPkt - a request to join game lobby 
		packet sent from client to host:
			- enum = 1

		Implemented with packet >> 1 >> ipBundle(senderIP, playNum)
	*/

	//lobInfoPkt - 2
	/*
		lobbyInfoPkt - lobby info package sent from host
		to all clients to update names, ping, ips etc.
			- enum = 2

		Implemented with packet >> 2 >> lobbyInfo;
	*/
		

	//updatePkt - 3
	/*
		updatePkt - an update on player info sent from 
		a client to a host:
			- enum = 3

			Implemented with packet >> 3 >> ipBundle(senderIP, playNum,
			user = newUser, ping = newPing)
	*/


	//clientDataPkt - 10
	/*
		clientDataPkt - A packet sent from the client to the host
		in game, to update the lobby with the clients data 
			- enum = 10

		Implement with: packet >> 10 >> clientDataPkt;
	*/

	struct clientDataPkt 
	{
		//Player move mechanics - can move up
		//to two directios simultaneously
		short dir1;
		short dir2;

		//did they click to shoot
		bool leftClick;

		//Players mouse pos
		sf::Vector2f mousePos;

		//did they click to grow folRadius
		//did they release to shrink it
		bool rightClick;
		bool realeaseRightClick;
		
		//did player quit
		bool playerQuit;
	};

	//gameInfoPkt - 11
	/*
		gameInfoPkt - screenshot of gameState at a timepoint
		distributed to all players in a game
			- enum = 11
	*/

	//preRequisite packets
	struct bulletData
	{
		/*
			Holds key bullet data:
			(create bullet and add to vector for client)
			- id (for matching purposes)
			- Position
			- hit(for audio and visuals)
			- isDeleted
			- isNew
			- orientNew bullets
		*/

		sf::Vector2f pos;

		bool hit;
		bool isDeleted;
	};

	struct playerData {
		/*
			Holds a player's vars:
			- Position
			- Health
			- Shield
			- Score/kills
			- is Stunned
			- drops/powerUps
			- bullet data
		*/

		sf::Vector2f pos;

		int health;
		int shield;

		int score;
		bool isStunned;

		//powerUps
		std::vector<bulletData> bullets;

	};


	struct followerData {
		/*
			Holds a Followers's vars:
			- id
			- Position
			- Health
			- Score/kills
		*/
		int id;
		sf::Vector2f pos;
		int health;
	};

	struct towerData {
		/*
			Holds a Towers's vars:
			- towerNum
			- ownedBy
			- isFiring
			- nextBuyAt
			- TimerInfo
		*/

		int towerNum;
		int ownedBy;

		bool isFiring;

		int nextBuyAt;
		float timer;
		float maxTimer;
	};

	//gameInfoPkt - 11 implementation
	struct gameInfoPkt {
		std::vector<playerData> players;
		std::vector<followerData> followers;
		std::vector<towerData> towers;
	};

}

/*  Operator Overloads for Packet loading/unloading */

	/*  Vectors  */

sf::Packet& operator>>(sf::Packet& pkt, sf::Vector2f& obj);

sf::Packet& operator<<(sf::Packet& pkt, const sf::Vector2f& obj);


	/*  IP Bundle  */
using NetworkObjects::ipBundle;
sf::Packet& operator>>(sf::Packet& pkt, ipBundle& obj);

sf::Packet& operator<<(sf::Packet& pkt, const ipBundle obj);


//End Vector Overloads