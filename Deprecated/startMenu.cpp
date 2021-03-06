//Implementation file for startMenu

#include "startMenu.h"

	/*  StartMenu  */
//Default constructor, does nothing
StartMenu::StartMenu()
{
}

//Start Menu Constructor
StartMenu::StartMenu(sf::RenderWindow &window)
{
	win_ptr = &window;
	initvars();

	initGameTitle();
	initMenuOptions();
}

//One Line title, One option


	/*  Init methods  */
void StartMenu::initvars()
{
	optionSelected = 0;
	numOptions = 2;
	//default, user remains at startmenu
}

void StartMenu::initGameTitle()
{
	float wLength = win_ptr->getSize().x;
	float wHeight = win_ptr->getSize().y;

	float titleX = wLength / 2.f;
	float titleY = wHeight / 6.f;

	int textSize = (wLength / 100.f) * (wHeight / 100.f) * (1.f / 2.f);

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

void StartMenu::initMenuOptions()
{
	//set Positions of options relative to window
	float wLength = win_ptr->getSize().x;
	float wHeight = win_ptr->getSize().y;

	float posX = wLength / 2.f;
	float posY = wHeight / 2.f;

	sf::Vector2f posPlay = sf::Vector2f(posX, posY);
	sf::Vector2f spacing = sf::Vector2f(0.f, wHeight / 12.f);

	int textSize = (wLength / 100.f) * (wHeight / 100.f) * (0.25f);
	float thickness = 8.f;

	//Set Text Aspects Strings
	std::string playText = "Play Game";
	std::string quitText = "Quit";

	sf::Vector2f playTightness = sf::Vector2f(1.31f, 1.1);
	sf::Vector2f quitTightness = sf::Vector2f(3.f, 1.1);
	
	//create the buttons
	play = MenuObjects::Button(posPlay, playText, zsk::ARCDE,
		textSize, true, playTightness);

	quit = MenuObjects::Button(posPlay + spacing, quitText, zsk::ARCDE,
		textSize, true, quitTightness);

	//set Animate color to light gray and border thickness
	play.setAnimateColor(zsk::art::lightTertCol);
	quit.setAnimateColor(zsk::art::lightTertCol);

	play.setOutlineThickness(thickness);
	quit.setOutlineThickness(thickness);
}

//End Init Methods


	/*  Setter Methods  */
void StartMenu::setTitlePos(sf::Vector2f const &newPos)
{
	float wLength = win_ptr->getSize().x;
	float wHeight = win_ptr->getSize().y;

	t1Pos = newPos;
	t2Pos = newPos + sf::Vector2f(0, wLength/ 12.f);

	sf::FloatRect title1Size = title1.getLocalBounds();
	sf::FloatRect title2Size = title2.getLocalBounds();

	title1.setOrigin(title1Size.width / 2.f, title1Size.height / 2.f);
	title1.setPosition(t1Pos);

	title2.setOrigin(title2Size.width / 2.f, title2Size.height / 2.f);
	title2.setPosition(t2Pos);
}

void StartMenu::setTitleSize(int newSize) {
	title1.setCharacterSize(newSize);
	title2.setCharacterSize(newSize);
}


//End Setter Methods


	/*  Accesor Methods  */
short StartMenu::getOptionSelected() {
	return optionSelected;
}


	/*  Other Functions  */
void StartMenu::update(sf::Vector2i const & mousePos)
{
	/* 
		update function: @void
		-animate title animation
		-add effects for hovering over Play or Quit
		-eventually add clip to background
	*/

	animateTitle();
	hoverOptions();
}

void StartMenu::animateTitle()
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

void StartMenu::hoverOptions()
{
	
	play.update(*win_ptr);
	quit.update(*win_ptr);

	if (play.isClicked()){
		updateOption(1);
	}
	else if (quit.isClicked()) {
		updateOption(3);
	}
}

void StartMenu::updateOption(short selection) {
	optionSelected = selection;
}

void StartMenu::drawMenu(sf::RenderWindow & window) {
	

	switch (optionSelected)
	{
	case 0:
		//title screen
		window.draw(title1);
		window.draw(title2);

		play.draw(*win_ptr);
		quit.draw(*win_ptr);
		
		break;
	case 1:
		//play Game;
		break;
	case 2:
		//options
		break;
	case 3:
		//quit game
		break;
	}
}


	/*  Destructors  */
StartMenu::~StartMenu()
{
	
}
