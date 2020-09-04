#include "MenuState.h"

/*
	Implementation File for MenuState Class
*/



/*  Constructors  */
MenuState::MenuState(sf::RenderWindow* w_ptr, std::vector<sf::Event>* evs)
	: State(w_ptr, evs)
{
	initvars();
	initGameTitle();
	initMenuOptions();
}


/*  Init methods  */
void MenuState::initvars()
{
	gameState = MAIN_MENU;
	numOptions = 2;
	//default, user remains at startmenu
}

void MenuState::initGameTitle()
{
	float wLength = window_ptr->getSize().x;
	float wHeight = window_ptr->getSize().y;

	float titleX = wLength / 2.f;
	float titleY = wHeight / 7.f;

	int textSize = (wLength / 100.f) * (wHeight / 100.f) * (1.f / 1.5f);

	//Title 1
	title1.setFont(zsk::art::arcade);
	title1.setString("Zombie Slayer");
	title1.setFillColor(zsk::art::secColor);

	//Title 2
	title2.setFont(zsk::art::arcade);
	title2.setString("Killer");
	title2.setFillColor(zsk::art::secColor);

	//set text size for t1 and t2
	setTitleSize(textSize);

	//Set positions for t1 and t2
	setTitlePos(sf::Vector2f(titleX, titleY));
}

void MenuState::initMenuOptions()
{
	//set Positions of options relative to window
	float wLength = window_ptr->getSize().x;
	float wHeight = window_ptr->getSize().y;

	float posX = wLength / 2.f;
	float posY = wHeight / 2.f;

	sf::Vector2f posPlay = sf::Vector2f(posX, posY);
	sf::Vector2f spacing = sf::Vector2f(0.f, wHeight / 12.f);

	int textSize = (wLength / 100.f) * (wHeight / 100.f) * (0.25f);
	float thickness = 8.f;

	//Set Text Aspects Strings
	std::string playText = "Create Game";
	std::string quitText = "Quit";

	sf::Vector2f playTightness = sf::Vector2f(1.1f, 1.1);
	sf::Vector2f quitTightness = sf::Vector2f(3.1f, 1.1);

	//create the buttons
	play = MenuObjects::Button(MAIN_MENU, posPlay, playText, zsk::ARCDE,
		textSize, true, LOBBY, playTightness);

	quit = MenuObjects::Button(MAIN_MENU, posPlay + spacing, quitText, zsk::ARCDE,
		textSize, true, QUIT, quitTightness);

	//set Animate color to light gray and border thickness
	play.setAnimateColor(zsk::art::lightTertCol);
	quit.setAnimateColor(zsk::art::lightTertCol);

	play.setOutlineThickness(thickness);
	quit.setOutlineThickness(thickness);
}

//End Init Methods


/*  Modifiers  */
void MenuState::setTitlePos(sf::Vector2f const &newPos)
{
	float wLength = window_ptr->getSize().x;
	float wHeight = window_ptr->getSize().y;

	t1Pos = newPos;
	t2Pos = newPos + sf::Vector2f(0, wLength / 12.f);

	sf::FloatRect title1Size = title1.getLocalBounds();
	sf::FloatRect title2Size = title2.getLocalBounds();

	title1.setOrigin(title1Size.width / 2.f, title1Size.height / 2.f);
	title1.setPosition(t1Pos);

	title2.setOrigin(title2Size.width / 2.f, title2Size.height / 2.f);
	title2.setPosition(t2Pos);
}

void MenuState::setTitleSize(int newSize) {
	title1.setCharacterSize(newSize);
	title2.setCharacterSize(newSize);
}

//End Modifiers

/*  Accessors  */
short MenuState::getOptionSelected() {
	return gameState;
}


/*  Other Public Funtions  */

STATE MenuState::update(sf::Vector2i &mousePos, const float& dt)
{
	//Update and animate title screen
	animateTitle();
	hoverOptions();

	return gameState;
}

void MenuState::animateTitle()
{
	//Make title move up and down a bit, maybe more later
	static sf::Vector2f truePos = t1Pos;

	static int counter = 1;
	static float dist = 0.3f;
	static int adj = 1;
	static int interval = 25;

	if (counter <= -interval)
		adj = 1;
	else if (counter >= interval)
		adj = -1;

	counter += adj;

	sf::Vector2f adjVect = sf::Vector2f(0.f, dist*counter);
	setTitlePos(truePos + adjVect);
}

void MenuState::hoverOptions()
{

	play.update(*window_ptr);
	quit.update(*window_ptr);

	if (play.isClicked()) {
		updateOption(LOBBY);
	}
	else if (quit.isClicked()) {
		updateOption(QUIT);
	}
}

void MenuState::updateOption(STATE selection) {
	gameState = selection;
}


void MenuState::render(sf::RenderTarget* rt) {

	switch (gameState)
	{
	case MAIN_MENU:
		//title screen
		window_ptr->draw(title1);
		window_ptr->draw(title2);

		play.draw(*window_ptr);
		quit.draw(*window_ptr);

		break;
	case LOBBY:
		//create Game Lobby;
		break;
	case GAME:
		//options
		break;
	case QUIT:
		//quit game
		break;
	}
}

void MenuState::quitState()
{
}


/*  Other Private Functions  */


	/*  Destructor  */
MenuState::~MenuState()
{
}
