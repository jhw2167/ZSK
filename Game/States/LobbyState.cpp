#include "LobbyState.h"

/*
	Implementation file for lobbyState Class
*/


/*  Constructors  */
LobbyState::LobbyState(sf::RenderWindow* w_ptr,
	std::vector<sf::Event>* evs)
	: State(w_ptr, evs)
{
	
	initvars();
	initArt();
	//initIP();
	initGameTitle();
	initMenuOptions();
}


/*  Init methods  */
void LobbyState::initvars()
{
	gameState = LOBBY;
	numOptions = 2;
	//default, user remains at startmenu
}

void LobbyState::initGameTitle()
{
	float wLength = window_ptr->getSize().x;
	float wHeight = window_ptr->getSize().y;

	float titleX = wLength / 2.f;
	float titleY = wHeight / 15.f;

	int textSize = (wLength / 100.f) * (wHeight / 100.f) * (1.f / 2.5f);

	//Title 1
	title1.setFont(zsk::art::arcade);
	title1.setString("Zombie Slayer Killer");
	title1.setFillColor(zsk::art::secColor);

	//set text size
	title1.setCharacterSize(textSize);
	sf::FloatRect size = title1.getLocalBounds();

	//Set position
	title1.setOrigin(sf::Vector2f(size.width / 2.f, size.height / 2.f));
	title1.setPosition(sf::Vector2f(titleX, titleY));
}

void LobbyState::initMenuOptions()
{
	//set Positions of options relative to window
	float wWidth = window_ptr->getSize().x;
	float wHeight = window_ptr->getSize().y;

	//init all our interactables
	initHostJoin(wWidth, wHeight);
	initEnterCode(wWidth, wHeight);
	initGenCode(wWidth, wHeight);

	initPlayerList(wWidth, wHeight);
	initBack(wWidth, wHeight);
	initStartGame(wWidth, wHeight);

	addToVector();
}

void LobbyState::initArt()
{
	const float width = window_ptr->getSize().x;
	const float height = window_ptr->getSize().y;

	float w = width * 0.98f;
	float h = height * 0.98f;

	sf::Vector2f adj(width - w, height - h);
	adj = (adj / 2.f);

	sf::Vector2f size(w, h);
	int thickness = 25;

	//Set border attributes
	border.setPosition(adj);
	border.setSize(size);
	border.setFillColor(zsk::art::primColor);

	border.setOutlineColor(zsk::art::secColor);
	border.setOutlineThickness(thickness);
}

void LobbyState::initIP()
{
	/*
		Initialize our serverContact object
		- for now initialized by default constructor
	*/
}

void LobbyState::initHostJoin(const float width, const float height)
{
	float posX = width / 6.f;
	float posY = height / 5.5f;

	//Determine button Positions
	sf::Vector2f posHost = sf::Vector2f(posX, posY);
	sf::Vector2f posJoin = sf::Vector2f(width - posX, posY);

	int textSize = (width / 100.f) * (height / 100.f) * (0.25f);
	float thickness = 8.f;

	//Set Text Aspects Strings
	std::string playText = "Host Game";
	std::string joinText = "Join Game";

	//create the buttons
	hostGame = MenuObjects::Button(LOBBY, posHost, playText, zsk::ARCDE,
		textSize, false, HOST_LOBBY);
	hostGame.bufferClickable();

	joinGame = MenuObjects::Button(LOBBY, posJoin, joinText, zsk::ARCDE,
		textSize, false, JOIN_LOBBY);
	joinGame.bufferClickable();

	//set Animate color to light gray and border thickness
	hostGame.setAnimateColor(zsk::art::lightTertCol);
	joinGame.setAnimateColor(zsk::art::lightTertCol);

	hostGame.setOutlineThickness(thickness);
	joinGame.setOutlineThickness(thickness);
}

void LobbyState::initEnterCode(const float width, const float height)
{
	/*
		Calculates all values and variables necesary to initialize
		the enter code TextBox and submitCode  button 
	*/

	sf::Vector2f pos = joinGame.getPosition();
	sf::Vector2f spacing = sf::Vector2f(0.f, height / 15.f);

	int textSize = joinGame.getTextSize();
	float thickness = 6.f;

	//Set Text Aspects Strings
	std::string defaultText = "Enter Code";
	sf::Vector2f tightness = sf::Vector2f(1.1f, 1.1);

	//create the textBox
	enterCode = MenuObjects::Textbox(LOBBY, pos + spacing, defaultText, zsk::ARIAL,
		textSize, false, LOBBY, tightness);

	enterCode.setEventsPtr(events);
	enterCode.setPrimColor(zsk::art::lightTertCol);
	enterCode.setTxtColor(zsk::art::secColor);

	//set animate color and thickness
	enterCode.setAnimateColor(sf::Color::Yellow);
	enterCode.setOutlineThickness(thickness);
	enterCode.setMaxMsgSize(5);
	enterCode.forceUpperCase(true);

	/*
		Create Accomplice button to submit the code
	*/
	pos = enterCode.getPosition();

	std::string msg = "->";
	tightness = sf::Vector2f(1.25f, 1.25f);

	//create button
	submitCode = MenuObjects::Button(LOBBY, pos, msg, zsk::ARIAL,
		textSize, false, LOBBY, tightness);
	//submitCode.bufferClickable();

	//reset position
	float x1 = joinGame.getPosition().x + joinGame.getBoxSize().x / 2.f;
	float x2 = joinGame.getPosition().x + enterCode.getBoxSize().x / 2.f;

	float dif = submitCode.getBoxSize().x / 2.f;
	pos = sf::Vector2f(x1 - dif, pos.y);
	submitCode.setPosition(pos);
	
	//set animation facets
	submitCode.setAnimateColor(zsk::art::lightTertCol);
	submitCode.setOutlineThickness(thickness + 2.f);

	submitCode.setPrimColor(zsk::art::lightTertCol);

	//setTextFacets
	submitCode.setTextSpacing(-1);
	submitCode.setTextStyle(sf::Text::Bold);
	submitCode.adjTextToBox(sf::Vector2f(0, -8.f));

}

void LobbyState::initGenCode(const float width, const float height)
{
	sf::Vector2f pos = hostGame.getPosition();

	sf::Vector2f spacing = sf::Vector2f(0.f, height / 16.f);
	sf::Vector2f pos1 = pos + spacing;

	int textSize = hostGame.getTextSize() + 2;
	float thickness = 0.f;
	sf::Vector2f tightness(0.9, 0.9);

	//Set Text Aspects Strings
	std::string defaultText = "Game Code:";
	std::string defaultCode = "#####";

	//create the buttons
	codeText = MenuObjects::Button(LOBBY, pos1, defaultText, zsk::ARIAL,
		textSize, false, LOBBY, tightness);
	codeText.setOutlineThickness(thickness);

	float align = (codeText.getBoxSize().x - hostGame.getBoxSize().x) / 2.f;
	pos1.x = codeText.getPosition().x + align;
	codeText.setPosition(pos1);
	codeText.setTextSpacing(0.80);
	codeText.setTxtColor(zsk::art::darkTertCol);


	//move position over slightlight for code
	float adj = 70.f;
	sf::Vector2f pos2 = codeText.getPosition();
	pos2.x += (codeText.getBoxSize().x / 2.f + adj);

	//set game code init
	gameCode = MenuObjects::Button(LOBBY, pos2, defaultCode, zsk::ARIAL,
		textSize, false, LOBBY, tightness);

	gameCode.setOutlineThickness(thickness);
	gameCode.setTextSpacing(0.5);
	gameCode.setTextStyle(sf::Text::Style::Bold);
	gameCode.setTxtColor(zsk::art::darkTertCol);

}

void LobbyState::initPlayerList(const float width, const float height)
{
	/*
		Init large boxes (unclicable buttons) on the left and right side 
		of the screen to hold the players in the lobby
	*/

	//Determine box size as 60% of window height
	sf::Vector2f size(width * 0.4f, height * 0.58f);
	float thickness = 8.f;

	sf::Vector2f spacing(0, height / 16.f);
	sf::Vector2f posLeft(hostGame.getPosition());

	//adjust left position of box
	posLeft.x -= hostGame.getBoxSize().x / 2.f;
	posLeft.x += size.x / 2.f;

	posLeft.y = enterCode.getPosition().y;
	posLeft.y += spacing.y + (size.y / 2.f);

	hostList = MenuObjects::Button(LOBBY, posLeft, size, false, LOBBY);

	hostList.setOutlineThickness(thickness);
	hostList.setSecColor(zsk::art::secColor);
	hostList.setPrimColor(zsk::art::lightTertCol);


	//And set JOIN list
	sf::Vector2f posRight(width - posLeft.x, posLeft.y);

	joinList = MenuObjects::Button(LOBBY, posRight, size, false, LOBBY);

	joinList.setOutlineThickness(thickness);
	joinList.setPrimColor(zsk::art::lightTertCol);
	joinList.setSecColor(zsk::art::secColor);

}

void LobbyState::initBack(const float width, const float height)
{
	sf::Vector2f pos(width * 0.05f, height * 0.94f);

	std::string msg = "<<";
	sf::Vector2f tightness(1.f, 1.f);
	int textSize = submitCode.getTextSize() + 5;
	float thickness = submitCode.getOutlineThickness();

	//create button
	back = MenuObjects::Button(LOBBY, pos, msg, zsk::ARCDE,
		textSize, false, MAIN_MENU, tightness);
	back.bufferClickable();

	//set animation facets
	back.setAnimateColor(zsk::art::lightTertCol);
	back.setOutlineThickness(thickness);
	back.setSecColor(zsk::art::secColor);

	//setTextFacets
	back.setTextSpacing(0);
	back.setTextStyle(sf::Text::Bold);
	back.adjTextToBox(sf::Vector2f(0, -6.f));
}

void LobbyState::initStartGame(const float width, const float height)
{
	sf::Vector2f pos = back.getPosition();
	pos.x += hostList.getBoxSize().x;

	std::string msg = "Start>>";
	sf::Vector2f tightness(1.1f, 1.05f);
	int textSize = enterCode.getTextSize() - 5.f;
	float thickness = submitCode.getOutlineThickness();

	//create button
	start = MenuObjects::Button(LOBBY, pos, msg, zsk::ARCDE,
		textSize, false, GAME, tightness);

	//reset pos
	pos.x -= start.getBoxSize().x / 2.f;
	start.setPosition(pos);

	//set animation facets
	start.setAnimateColor(zsk::art::lightTertCol);
	start.setOutlineThickness(thickness);

	start.setPrimColor(zsk::art::lightTertCol);
	start.setSecColor(zsk::art::secColor);
	start.setTxtColor(zsk::art::secColor);

	//setTextFacets
	start.setTextSpacing(1);
	//start.adjTextToBox(sf::Vector2f(0, -6.f));
}


//add all menuObjects to our vectors
void LobbyState::addToVector()
{
	//Push back our buttons
	menuObjects.push_back(&hostGame);
	menuObjects.push_back(&joinGame);
	menuObjects.push_back(&back);
	menuObjects.push_back(&start);
	menuObjects.push_back(&submitCode);

	//Push back raw text
	menuObjects.push_back(&codeText);
	menuObjects.push_back(&gameCode);

	//push back Text Boxes
	menuObjects.push_back(&enterCode);

	//Push back other vacant objects
	menuObjects.push_back(&hostList);
	menuObjects.push_back(&joinList);

	
}


//End Init Methods


/*  Modifiers  */

//End Modifiers

/*  Accessors  */
STATE LobbyState::getOptionSelected() {
	return gameState;
}

//End accessors


/*  Other Private Functions  */
void LobbyState::configLobby(STATE selection)
{
	/*
		Sets up the lobby for multiplayer play
		- must distinguish between a HOST and
		a lobby member by gamestate and send
		the packets to the main server
	*/

	switch (selection)
	{
	case LOBBY:
		//resets lobby
		initvars();
		initArt();
		//initIP();
		initGameTitle();
		initMenuOptions();
		break;

	case HOST_LOBBY:
		//configs host screen
		configHost();
		break;

	case JOIN_LOBBY:
		//configs join screen
		configJoin();
		break;

	default:
		break;
	}
}

void LobbyState::configHost()
{
	/*
		Sets up screen for host capabilities
		and view screen
	*/

	//send message to server to create game
	bool isHost = true;
	serverContact.sendBundle(isHost);

	//refactor certain buttons - host and join
	joinGame.setClickable(true);
	hostGame.setClickable(false);
	playerList.clear();

	//Back & start
	back.updateNextState(LOBBY);
	start.setClickable(true);
	start.setPrimColor(zsk::art::primColor);

	//create new visible player tuple
	addPlayerTuple(serverContact.getBundle());
}

void LobbyState::configJoin()
{
	/*
		Sets up screen for join lobby view
	*/

	//send message to server to join game
	bool isHost = false;
	serverContact.sendBundle(isHost);

	joinGame.setClickable(false);
	hostGame.setClickable(true);
	playerList.clear();

	//refactor certain buttons
	back.updateNextState(LOBBY);
}

void LobbyState::addPlayerTuple(const NetworkObjects::ipBundle & bndl)
{
	//Define objects in tuple
	std::vector<char> vals = { 'b', 't', 'b' };

	//Sizes
	float w = hostList.getBoxSize().x;
	float h = hostGame.getBoxSize().y * 1.5;
	sf::Vector2f size(w, h);
	std::vector<float> lengths = { 0.15, 0.7, 0.15 };

	// Position - push tuple position furth down the
	// list for each tuple added
	sf::Vector2f pos(0,0);

	if (gameState == HOST_LOBBY)
		pos = hostList.getPosition();
	else
		pos = joinList.getPosition();

	pos.y -= hostList.getBoxSize().y / 2.f;
	pos.y += size.y / 2.f;

	for (auto& tuple : playerList) {
		pos.y += tuple.getBoxSize().y;
	}

	//Create tuple members
	MenuObjects::Tuple member(gameState, pos, vals, lengths,
			size, false, gameState);

	//Modify individual entities
	std::vector<MenuObjects::MenuObject*>* objs = member.getObjs();

	float thickness = enterCode.getOutlineThickness() / 2.f;
	//playerList.back().setOutlineThickness(thickness);
	member.setOutlineThickness(thickness);
	for (auto& obj : *objs)
	{
		//Primary Colors
		obj->setPrimColor(zsk::art::primColor);
		obj->setSecColor(zsk::art::secColor);
		obj->setTxtColor(zsk::art::secColor);

		//Animation details
		obj->setAnimateColor(zsk::art::primColor);
		obj->setAnimateColor2(sf::Color::Yellow);
		obj->setAnimateScaler(sf::Vector2f(1, 1));
		
	}

	//set Special details for textbox - at pos(1)
	dynamic_cast<MenuObjects::Textbox*>(objs->at(1))->setEventsPtr(events);

	//Set Text box details
	dynamic_cast<MenuObjects::Textbox*>(objs->at(1))->setMaxMsgSize(12);
	dynamic_cast<MenuObjects::Textbox*>(objs->at(1))->setFont(zsk::ARIAL);
	dynamic_cast<MenuObjects::Textbox*>(objs->at(1))->setString(bndl.user);
	dynamic_cast<MenuObjects::Textbox*>(objs->at(1))
		->fitTextToBox(sf::Vector2f(1.2, 1.4), MenuObjects::LEFT);

	//add to list of players to be visible
	playerList.push_back(std::move(member));
	//playerList.push_back(member);

}


/*  Other Public Funtions  */

void LobbyState::addNewPlayer(const NetworkObjects::ipBundle & bundle)
{
	/*
		We will add a new player into the lobby by adding their ipbundle 
		to the lobby's list, and by adding their visual "tuple" onto
		the screen
	*/


}

STATE LobbyState::update(sf::Vector2i &mousePos, const float& dt)
{
	//Update and animate title screen
	animateTitle();
	hoverOptions();

	return gameState;
}

void LobbyState::animateTitle()
{
	//Make title move up and down a bit, maybe more later
	static sf::Vector2f truePos = title1.getPosition();

	static int counter = 1;
	static float dist = 0.2f;
	static int adj = 1;
	static int interval = 15;

	if (counter <= -interval)
		adj = 1;
	else if (counter >= interval)
		adj = -1;

	counter += adj;

	sf::Vector2f adjVect = sf::Vector2f(0.f, dist*counter);
	title1.setPosition(truePos + adjVect);
}

void LobbyState::hoverOptions()
{
	//detecs updates in all buttons onscreen and 
	//propogates updated state once selected

	for (auto& menObj : menuObjects) {

		STATE gs = menObj->update(*window_ptr);
		
		if (gs != gameState) {
			updateOption(gs);
			break;
		}
		
	}

	//update all tuples in playerlist
	for (auto& tuple : playerList) {
		STATE gs = tuple.update(*window_ptr);
		//tuples cannot change gamestate
	}
}

void LobbyState::updateOption(STATE selection) {

	gameState = selection;
	configLobby(selection);

	//Update option for all buttons
	for (auto& obj : menuObjects) {
		obj->updateCurrState(selection);
	}

}


void LobbyState::render(sf::RenderTarget* rt) {

	switch (gameState)
	{
	case MAIN_MENU:
		//title screen
		break;

	case HOST_LOBBY:
		//renders Lobby
		renderLobby();
		break;

	case JOIN_LOBBY:
		//renders Lobby
		renderLobby();
		break;

	case LOBBY:
		//renders Lobby
		renderLobby();
		break;

	case GAME:
		//options
		break;

	case QUIT:
		//quit to home screen
		break;
	}

}

void LobbyState::renderLobby() {
	//create Game Lobby;
	window_ptr->draw(border);
	window_ptr->draw(title1);

	//draw all our menu objects
	for (auto& menObj : menuObjects) {
		menObj->draw(*window_ptr);
	}


	for (auto& tuple : playerList) {
		tuple.draw(*window_ptr);
		//tuples cannot change gamestate
	}
	
}

void LobbyState::quitState()
{
}



	/*  Destructor  */
LobbyState::~LobbyState()
{
}
