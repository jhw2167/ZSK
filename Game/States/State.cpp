#include "State.h"



State::State(sf::RenderWindow* w_ptr, std::vector<sf::Event>* evs)
{
	window_ptr = w_ptr;
	events = evs;
}


State::~State()
{
}
