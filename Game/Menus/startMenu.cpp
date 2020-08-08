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
	setWindowSize(window);
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
	float titleX = wLength / 2.f;
	float titleY = wHeight / 6.f;

	int textSize = (wLength / 100.f) * (wHeight / 100.f) * (1.f / 2.f);

	if (!arcade.loadFromFile("Fonts/ARCADE_N.ttf")) 	{
		//loads font to use for text drawing
		std::cout << "Error loading arcade text in \n startMenu.cpp" << std::endl;
	}

	//Title 1
	title1.setFont(arcade);
	title1.setString("Zombie Slayer");
	title1.setFillColor(sf::Color::Black);

	//Title 2
	title2.setFont(arcade);
	title2.setString("Killer");
	title2.setFillColor(sf::Color::Black);
	
	//set text size for t1 and t2
	setTitleSize(textSize);

	//Set positions for t1 and t2
	setTitlePos(sf::Vector2f(titleX, titleY));
}

void StartMenu::initMenuOptions()
{
	float posX = wLength / 2.f;
	float posY = wHeight / 2.f;

	int textSize = (wLength / 100.f) * (wHeight / 100.f) * (1.f / 4.f);
	float thickness = 10.f;

	//Set Text Aspects Strings
	playText.setString("Play Game");
	quitText.setString("Quit");

	playText.setFillColor(sf::Color::Black);
	quitText.setFillColor(sf::Color::Black);

	playText.setFont(arcade);
	quitText.setFont(arcade);

	setOptionsSize(textSize);

	//Set Other Aspects - Rects
	playRect.setFillColor(sf::Color::White);
	quitRect.setFillColor(sf::Color::White);

	playRect.setOutlineColor(sf::Color::Black);
	playRect.setOutlineThickness(thickness);

	quitRect.setOutlineColor(sf::Color::Black);
	quitRect.setOutlineThickness(thickness);

	//Set size and Position
	setOptionsPos(sf::Vector2f(posX, posY));
}

//End Init Methods


	/*  Setter Methods  */
void StartMenu::setWindowSize(sf::RenderWindow & window) {
	wLength = window.getSize().x;
	wHeight = window.getSize().y;
}

void StartMenu::setTitlePos(sf::Vector2f const &newPos)
{
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

void StartMenu::setOptionsSize(int txtSize)
{
	//set text sizes
	playText.setCharacterSize(txtSize);
	quitText.setCharacterSize(txtSize);

	float length = playText.getLocalBounds().width;
	float length2 = quitText.getLocalBounds().width;
	float height = playText.getLocalBounds().height;

	sf::Vector2f origin = sf::Vector2f(length / 2.f, height / 2.f);
	sf::Vector2f origin2 = sf::Vector2f(length2 / 2.f, height / 2.f);

	playText.setOrigin(origin);
	quitText.setOrigin(origin2);

	//rectangle size is just taller than text
	//and just was wide as main title font
	float adj = 10.f;
	float rectLength = title2.getLocalBounds().width;
	float rectHeight = playText.getLocalBounds().height + adj;

	sf::Vector2f size = sf::Vector2f(rectLength, rectHeight);

	playRect.setSize(size);
	quitRect.setSize(size);

	sf::Vector2f rectOrigin = sf::Vector2f(rectLength / 2.f,
		(rectHeight - adj) / 2.f);

	playRect.setOrigin(rectOrigin);
	quitRect.setOrigin(rectOrigin);

	//Set Scales to 1.f
	static sf::Vector2f scale = sf::Vector2f(1, 1);
	playRect.setScale(scale);
	quitRect.setScale(scale);

	playText.setScale(scale);
	quitText.setScale(scale);
}

void StartMenu::setOptionsPos(sf::Vector2f const & newPos)
{
	sf::Vector2f spacing = sf::Vector2f(0.f, wHeight / 12.f);

	//Set Rect positions
	playRect.setPosition(newPos);
	quitRect.setPosition(newPos + spacing);

	//Set text Positions
	playText.setPosition(newPos);
	quitText.setPosition(newPos + spacing);
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
	hoverOptions(mousePos);
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

void StartMenu::hoverOptions(sf::Vector2i const &mousePos)
{
	short selection = 0;
	static bool unSelected = true;
	//default option 0 selected
	sf::Vector2f pos_2f = sf::Vector2f(mousePos.x, mousePos.y);

	if (playRect.getGlobalBounds().contains(pos_2f)) {
		selection = 1;
		//"Play Game" Button
	}
	else if (false) {
		selection = 2;
		//"Options" Menu
	}
	else if (quitRect.getGlobalBounds().contains(pos_2f)) {
		selection = 3;
		//"Quit" Button
	}
	else if (selection == 0 && !(unSelected)) {
		selection = 4;
		unSelected = true;
	}

	switch (selection * unSelected)
	{
	case 0:
		//no action
		break;

	case 1:
		selectRect(playRect, playText);
		unSelected = false;
		break;
		// "Play Game" Button

	case 2:
		unSelected = false;
		break;
		//"Options" Button

	case 3:
		selectRect(quitRect, quitText);
		unSelected = false;
		break;
		//"Quit" Button

	case 4:
		initMenuOptions();
		break;
		//reInitialize options
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		optionSelected = selection;

}

void StartMenu::selectRect(sf::RectangleShape & rect, sf::Text & text )
{
	static sf::Color gray = sf::Color(168, 168, 168, 255);
	static sf::Vector2f scaling = sf::Vector2f(1.1f, 1.1f);

	rect.setFillColor(gray);
	rect.scale(scaling);
	text.scale(scaling);
}

void StartMenu::updateOption(short selection) {
	optionSelected = selection;
}

void StartMenu::drawMenu(sf::RenderWindow & window) {
	

	switch (optionSelected)
	{
	case 0:
		window.draw(title1);
		window.draw(title2);

		window.draw(playRect);
		window.draw(quitRect);

		window.draw(playText);
		window.draw(quitText);
		//title screen

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
