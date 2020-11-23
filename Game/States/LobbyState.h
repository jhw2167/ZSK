#include "../../BaseCode/pch/stdafx.h"
#include "State.h"

#include "../NetworkFiles/NetworkObjects.h"
#include "../Menus/MenuObjects.h"

/*
	lobbyState is a player interactive screen designed to 
	show a lobby for the players to organize their games
	(choose their colors, add new players and start their game.
*/

class LobbyState :
	public State
{
private:

	//Title Vars
	sf::Text title1;

	//Subtitle Vars
	sf::Text subtitle1;

	//Bounding rect
	sf::RectangleShape border;

	//Option Vars
	std::vector<MenuObjects::MenuObject*> menuObjects;
	short numOptions;

	//host side
	MenuObjects::Button hostGame;
	MenuObjects::Button codeText;
	MenuObjects::Button gameCode;

	//Join side
	MenuObjects::Button joinGame;
	MenuObjects::Textbox enterCode;
	MenuObjects::Button submitCode;

	//Back & Start Button
	MenuObjects::Button back;
	MenuObjects::Button start;

	//Player tuple boxes
	MenuObjects::Button hostList;
	MenuObjects::Button joinList;

	//Tuples for players joining
	std::vector<MenuObjects::Tuple> playerList;
	std::vector<NetworkObjects::ipBundle> playerIps;

	//networkObjects
	Contact serverContact;


	/*  Private Functions  */

	/*  Init Methods  */
	void initvars();
	void initGameTitle();
	void initMenuOptions();
	void initArt();
	void initIP();

	void addToVector();
	void initHostJoin(const float width, const float height);
	void initEnterCode(const float width, const float height);
	void initGenCode(const float width, const float height);

	void initPlayerList(const float width, const float height);
	void initBack(const float width, const float height);
	void initStartGame(const float width, const float height);
	

	/*  Configure Lobby methods  */
	void configLobby(STATE selection);
	void configHost();
	void configJoin();

	void addPlayerTuple(const NetworkObjects::ipBundle& newBundle);


	/*  Other Private Functions  */
	void updateOption(STATE selection);
	void animateTitle();
	void hoverOptions();

	void renderLobby();


public:

	/*  Constructors  */

	LobbyState(sf::RenderWindow* w_ptr, std::vector<sf::Event>* events);


	/*  Modifiers  */

	/*  Accessors  */
	STATE getOptionSelected();

	/*  Other Public Funtions  */
	void addNewPlayer(const NetworkObjects::ipBundle& bundle);

	virtual STATE update(sf::Vector2i &mousePos, const float& dt);

	virtual void render(sf::RenderTarget* rt = nullptr);

	virtual void quitState();


	/*  Destructor  */
	virtual ~LobbyState();
};

