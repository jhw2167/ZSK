#include "MenuObjects.h"

/*
	Implementation file for menuobjects.h
*/


namespace MenuObjects {

	//init static members
	sf::Vector2f Button::defSize = sf::Vector2f(0,0);

	/*  Button Class  */

	//Button default Constructor
	Button::Button(const sf::RenderWindow &window, 
		const sf::Vector2f& pos)
	{
		win_ptr = &window;

		calcDefaultSizes();
		initColors();
		initSizes();
		initText();
		initPositions(pos);
	}

	/*  Accessors  */
	std::string Button::getString() const {
		return text.getString();
	}

	bool Button::isHovered() const
	{
		return false;
	}

	bool Button::isClicked() const
	{
		return false;
	}

	sf::Color Button::getPrimColor() const{
		return shape.getFillColor();
	}

	sf::Color Button::getSecColor() const {
		return shape.getOutlineColor();
	}

	sf::Color Button::getTxtColor() const {
		return text.getColor();
	}


	/*  Modifiers  */
	void Button::setString(const std::string & newString)
	{
	}

	void Button::setSize(const float multiplier)
	{
	}

	void Button::getPrimColor(const sf::Color & newPrim)
	{
	}

	void Button::setSecColor(const sf::Color & newSec)
	{
	}

	void Button::setTxtColor(const sf::Color & newTxtcolor)
	{
	}

	void Button::update()
	{
	}


	/*  Other Private Functions  */
	void Button::calcDefaultSizes()
	{
		/*
			Calculate default and standard sizes based on the
			window for the box and text.
			The button size can thereafter be scaled or reset
			entirely.
		*/

	}

	void Button::initText(const std::string& newString,
		const short font)
	{
		/*
			Initialize our button text with a font, textSize
			and color
		*/
		
		switch (font)
		{
		case ARIAL:
			text.setFont(zsk::art::arial);
			break;

		case ARCDE:
			text.setFont(zsk::art::arcade);
			break;

		default:

			text.setFont(zsk::art::arial);
			break;
		}

		text.setCharacterSize(textSize);
		text.setColor(zsk::art::secColor);
	}

	void Button::initSizes()
	{
	}

	void Button::initPositions(const sf::Vector2f& pos)
	{
		/*
			Init positions for the bounding rectangle
			and the contained text within it.
			Origins will need to be set and formatted
			similiarly
		*/

	}

	void Button::initColors(const sf::Color& prim = zsk::art::primColor,
		const sf::Color& sec = zsk::art::secColor,
		const sf::Color& txt = zsk::art::secColor)
	{
	}


	//Button Functionality
	bool Button::checkHovering()
	{
		return false;
	}

	void Button::animateOnHover()
	{
	}

	


	/*  Other Public Functions  */



	/*  Destructors  */
	Button::~Button()
	{
	}
	//END Button Class







	/*  Textbox Class  */

//Textbox default Constructor
	Textbox::Textbox()
	{
	}

	/*  Accessors  */


	/*  Modifiers  */


	/*  Other Private Functions  */

	/*  Other Public Functions  */



	/*  Destructors  */
	Textbox::~Textbox()
	{
	}
	//END Textbox Class


}


	