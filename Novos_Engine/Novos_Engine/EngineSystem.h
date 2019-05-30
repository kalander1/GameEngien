#pragma once
#include "stdafx.h"
//#include <Windows.h>
#include "GameObject.h"
#include "PhysicSystem.h"


class EngineSystem
{
public:
	EngineSystem();

	sf::Clock clock;
	sf::Time time;
	

	static sf::Time TimePerFrame;
	void gameLoop();

	bool multiWindow = false;
	void render();
	void eventprocessor();
	void InitWindow();
	void GameStatus();

	//Functions to create game objects, and add components
	void CreateObject(std::string ObjectName, float x = 0.0f, float y = 0.0f);

	void SetObjectParent(std::string ObjParentName, std::string ObjChildName);
	   	 
	//Add component functions
	void AttachRenderComponent(std::string objName, sf::Vector2f size = sf::Vector2f(0.0f, 0.0f), sf::Color color = sf::Color::Red, std::string text = "", std::string texturePath = "",int FontSize = 24, std::string FontPath = "");

	void AttachPhysicsComponent(std::string objName, float mass = 1.0f, bool hasGravity = true,  sf::Vector2f Velocity = sf::Vector2f(0.0f, 0.0f));

	void AttachAudioComponent(std::string objName, std::string filePath, bool playOnAwake = false, bool Loop = false);

	void AttachScriptComponent(std::string objName, std::string scriptName);


	GameObject* GameObjectManager;
	PhysicSystem* PhysicsEngine;
	//GameObject &Player;

protected:
	sf::RenderWindow _mainWindow;

private:
	void Update(float deltaTime);	
	std::vector<GameObject*> script_objects;
	GameObject* scoreObject;
	sf::Texture EngineCustomSplash;
	sf::Sprite  EngineCustomSplashImage;
	float score = 0.0f;
	float SplashClock = 0.0f;
	GameObject *Player;
	GameObject *Gameover;
};





