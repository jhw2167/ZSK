#include "Globals.h"

/*
	Implementation file of global constants, colors for 
	the program to use
*/

namespace zsk {

	namespace art {

		/*  Art Vars declared extern as globals  */

		//Const font variables
		sf::Font arcade;
		sf::Font arial;

		void loadFonts()
		{
			/*
				load any fonts we will be using at the
				beginning of the program
			*/
			std::string arcFontFile = "Art/Fonts/ARCADE_N.ttf";
			std::string arlFontFile = "Art/Fonts/arial.ttf";

			//load arcade font
			if (!arcade.loadFromFile(arcFontFile)) {
				//loads font to use for text drawing
				std::cout << "Error loading arcade text, there may be some\n"
					<< "visual inconcistencies, ensure file: '"<< arcFontFile
					<< "' exists" << std::endl;

			}


			//load arcade font
			if (!arial.loadFromFile(arlFontFile)) {
				//loads font to use for text drawing
				std::cout << "Error loading arial text, there may be some\n"
					<< "visual inconcistencies, ensure file: '" << arlFontFile
					<< "' exists" << std::endl;

			}

		}

		//Const colors
		sf::Color primColor = sf::Color::White;
		sf::Color secColor = sf::Color::Black;

		sf::Color lightTertCol;
		sf::Color darkTertCol;

		sf::Color winClearColor = sf::Color::White;

		//non const variales
		std::vector<sf::Color> playerColors;

	}
}

