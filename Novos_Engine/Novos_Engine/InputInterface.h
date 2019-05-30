#pragma once
#include "stdafx.h"

enum Input_ID
{
	Up,
	Down,
	Left,
	Right,
	Space
};

class InputInterface 
{
public:
	InputInterface();

	static InputInterface* GetInstance()
	{
		static InputInterface instance;
		return &instance;
	}

	~InputInterface() {}

	void AddAction(int id, sf::Keyboard::Key key);
	bool IsActionTriggered(int id);
	
	sf::Vector2i GetMousePosition(sf::RenderWindow &window);

private:
	
	std::map<int, sf::Keyboard::Key> m_Actions;

	/*virtual string VOnKeyDown(char kcode) = 0; 
	virtual void VOnKeyUp(char kcode) = 0;
	virtual string mouseEvents() = 0;*/
};
