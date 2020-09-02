#include "../../BaseCode/pch/stdafx.h"
#include "../../BaseCode/Globals/Globals.h"
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

	short gameState;
	//0 is main menu state

	//Title Vars
	sf::Text title1;

	//Subtitle Vars
	sf::Text subtitle1;

	//Option Vars
	std::vector<MenuObjects::MenuObject*> menuObjects;
	short numOptions;

	MenuObjects::Button hostGame;
	MenuObjects::Button joinGame;

	MenuObjects::Textbox enterCode;
	MenuObjects::Button submitCode;

	//Back Button
	MenuObjects::Button back;


	/*  Private Functions  */

	/*  Init Methods  */
	void initvars();
	void initGameTitle();
	void initMenuOptions();

	void addToVector();
	void initHostJoin(const float width, const float height);
	void initTextBox(const float width, const float height);
	void initPlayerList(const float width, const float height);
	void initBack(const float width, const float height);
	



	/*  Other Functions  */
	void updateOption(short selection);
	void animateTitle();
	void hoverOptions();


public:

	/*  Constructors  */

	LobbyState(sf::RenderWindow* w_ptr, std::vector<sf::Event>* events);


	/*  Modifiers  */

	/*  Accessors  */
	short getOptionSelected();

	/*  Other Public Funtions  */
	virtual short update(sf::Vector2i &mousePos, const float& dt);

	virtual void render(sf::RenderTarget* rt = nullptr);

	virtual void quitState();


	/*  Destructor  */
	virtual ~LobbyState();
};

