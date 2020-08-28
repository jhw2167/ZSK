#include "LobbyState.h"

/*
	Implementation file for lobbyState Class
*/


/*  Constructors  */
LobbyState::LobbyState(sf::RenderWindow* w_ptr)
	: State(w_ptr)
{
	initvars();
	initGameTitle();
	initMenuOptions();
}


/*  Init methods  */
void LobbyState::initvars()
{
	gameState = LOBBY;
	numOptions = 2;
	//default, user remains at startmenu

	sf::Packet pkt;
	const sf::Vector2f start(1, 2);
	sf::Vector2f end;

	pkt << start;
	pkt >> end;
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
	float wLength = window_ptr->getSize().x;
	float wHeight = window_ptr->getSize().y;

	//init all our interactables
	initHostJoin(wLength, wHeight);
	initTextBox(wLength, wHeight);
	initPlayerList(wLength, wHeight);
	initBack(wLength, wHeight);
}

void LobbyState::initHostJoin(const float width, const float height)
{
	float posX = width / 2.f;
	float posY = height / 2.f;

	sf::Vector2f posPlay = sf::Vector2f(posX, posY);
	sf::Vector2f spacing = sf::Vector2f(0.f, height / 12.f);

	int textSize = (width / 100.f) * (height / 100.f) * (0.25f);
	float thickness = 8.f;

	//Set Text Aspects Strings
	std::string playText = "Host Game";
	std::string quitText = "Quit";

	sf::Vector2f playTightness = sf::Vector2f(1.1f, 1.1);
	sf::Vector2f quitTightness = sf::Vector2f(3.1f, 1.1);

	//create the buttons
	hostGame = MenuObjects::Button(posPlay, playText, zsk::ARCDE,
		textSize, false, playTightness);
	hostGame.bufferClickable();

	quit = MenuObjects::Button(posPlay + spacing, quitText, zsk::ARCDE,
		textSize, false, quitTightness);
	quit.bufferClickable();

	//set Animate color to light gray and border thickness
	hostGame.setAnimateColor(zsk::art::lightTertCol);
	quit.setAnimateColor(zsk::art::lightTertCol);

	hostGame.setOutlineThickness(thickness);
	quit.setOutlineThickness(thickness);

}


void LobbyState::initTextBox(const float width, const float height)
{
	float posX = width / 1.5f;
	float posY = height / 4.f;

	sf::Vector2f pos = sf::Vector2f(posX, posY);
	sf::Vector2f spacing = sf::Vector2f(0.f, height / 12.f);

	int textSize = (width / 100.f) * (height / 100.f) * (0.25f);
	float thickness = 8.f;

	//Set Text Aspects Strings
	std::string defaultText = "Enter Code";

	sf::Vector2f tightness = sf::Vector2f(1.1f, 1.1);

	//create the buttons
	enterCode = MenuObjects::Textbox(pos, defaultText, zsk::ARIAL,
		textSize, false, tightness);
	enterCode.bufferClickable();

	//set animate color and thickness
	enterCode.setAnimateColor(sf::Color::Yellow);
	enterCode.setOutlineThickness(thickness);
}

void LobbyState::initPlayerList(const float width, const float height)
{
}

void LobbyState::initBack(const float width, const float height)
{
}

//End Init Methods


/*  Modifiers  */

//End Modifiers

/*  Accessors  */
short LobbyState::getOptionSelected() {
	return gameState;
}


/*  Other Public Funtions  */

short LobbyState::update(sf::Vector2i &mousePos, const float& dt)
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

	hostGame.update(*window_ptr);
	quit.update(*window_ptr);
	enterCode.update(*window_ptr);

	if (hostGame.isClicked()) {
		updateOption(GAME);
	}
	else if (quit.isClicked()) {
		updateOption(MAIN_MENU);
	}
}

void LobbyState::updateOption(short selection) {
	gameState = selection;
}


void LobbyState::render(sf::RenderTarget* rt) {

	switch (gameState)
	{
	case MAIN_MENU:
		//title screen
		break;
	case LOBBY:
		//create Game Lobby;
		window_ptr->draw(title1);

		hostGame.draw(*window_ptr);
		quit.draw(*window_ptr);
		enterCode.draw(*window_ptr);

		break;
	case GAME:
		//options
		break;
	case QUIT:
		//quit game
		break;
	}
}

void LobbyState::quitState()
{
}


/*  Other Private Functions  */


	/*  Destructor  */
LobbyState::~LobbyState()
{
}
