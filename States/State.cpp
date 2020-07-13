#include "State.h"



State::State(sf::RenderWindow* w_ptr) 
{
	window_ptr = w_ptr;

	std::cout << "Window_ptr address in state constructor: " 
		<< window_ptr << std::endl;
}


State::~State()
{
}
