#include "stdafx.h"
#include "InputInterface.h"


InputInterface::InputInterface()
{
}
//
//InputInterface::~InputInterface()
//{
//}

void InputInterface::AddAction(int id, sf::Keyboard::Key key)
{
	m_Actions[id] = key;
}

bool InputInterface::IsActionTriggered(int id)
{
	return sf::Keyboard::isKeyPressed(m_Actions[id]);
}


sf::Vector2i InputInterface::GetMousePosition(sf::RenderWindow &window)
{
	return sf::Mouse::getPosition(window);
}