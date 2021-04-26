#include "State.h"


//Constructor
State::State() {
	//This class is mostly virtual, not much to do here
}

void State::setWindow(const std::shared_ptr<sf::RenderWindow>& w_ptr)	{
	window_ptr = w_ptr;
}

void State::setMouse(const std::shared_ptr<sf::Mouse>& m_ptr) {
	mouse_ptr = m_ptr;
}

void State::setEvents(const std::shared_ptr<std::vector<sf::Event>>& evs_ptr) {
	events_ptr = evs_ptr;
}


//Destructor
State::~State()
{
}
