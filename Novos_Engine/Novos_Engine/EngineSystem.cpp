#include "stdafx.h"
#include "EngineSystem.h"
#include "InputInterface.h"
#include "CustomTypes.h"

 sf::Time EngineSystem::TimePerFrame = sf::seconds(1.f / 20.f);

EngineSystem::EngineSystem()
{	
	//Create Render System (Window)
	_mainWindow.create(sf::VideoMode(1024, 720, 32), "Novos Project");
	
	//Create Physics Engine
	PhysicsEngine = new PhysicSystem();

	//Create Game Object Manager
	GameObjectManager = new GameObject("ObjectManager");	

	//Set Object Manager in the center of the world (Window)	
	sf::Vector2f WindowCenter(_mainWindow.getSize().x * 0.5f, _mainWindow.getSize().y * 0.5f);
	GameObjectManager->GetComponent(Transform_Component)->setPosition(WindowCenter);

	InputInterface::GetInstance()->AddAction(Up, sf::Keyboard::Key::Up);
	InputInterface::GetInstance()->AddAction(Down, sf::Keyboard::Key::Down);
	InputInterface::GetInstance()->AddAction(Left, sf::Keyboard::Key::Left);
	InputInterface::GetInstance()->AddAction(Right, sf::Keyboard::Key::Right);
	InputInterface::GetInstance()->AddAction(Space, sf::Keyboard::Key::Space);

	EngineCustomSplash.loadFromFile("../Assets/SplashScreen.PNG");	
	EngineCustomSplashImage.setTexture(EngineCustomSplash);
	EngineCustomSplashImage.setTextureRect(sf::IntRect(0,0, _mainWindow.getSize().x, _mainWindow.getSize().y));
	
}

void EngineSystem::gameLoop()
{
	
	//time = clock.getElapsedTime();	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	while (_mainWindow.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;		
			
			if (SplashClock > 3.5f)
			{
				GameStatus();
				eventprocessor();
				PhysicsEngine->UpdatePhysics(TimePerFrame.asSeconds());
				GameObjectManager->Update(TimePerFrame);
			}				
		}

		Update(TimePerFrame.asSeconds());
		SplashClock += dt.asSeconds();
		score += dt.asSeconds();
		render();

	}
}

void EngineSystem::render()
{
	if (SplashClock <= 3.0f)
	{
		_mainWindow.clear();
		_mainWindow.draw(EngineCustomSplashImage);
		_mainWindow.display();
	}
	else
	{
				
		_mainWindow.clear();
		GameObjectManager->RenderGO(_mainWindow);			
		_mainWindow.display();
		
	}

}

void EngineSystem::eventprocessor()
{
	sf::Event event;
	while (_mainWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_mainWindow.close();
		
	}
}

void EngineSystem::InitWindow()
{	
	scoreObject = GameObjectManager->FindGameObject("Score");
	Gameover = GameObjectManager->FindGameObject("0gameOver");
	Player = GameObjectManager->FindGameObject("Player");

	gameLoop();
}

void EngineSystem::Update(float dt)
{	

	for (std::vector<GameObject*>::iterator it = script_objects.begin(); it != script_objects.end(); ++it)
	{
		float objPositionX = (*it)->GetComponent(Transform_Component)->getPosition().x;
		bool  outOfWindow = (*it)->GetComponent(Script_Component)->RunScript("OutOfView", objPositionX);
		if (outOfWindow)
		{			
			sf::Vector2f obPosition(_mainWindow.getSize().x * 0.5f,(*it)->GetComponent(Transform_Component)->getPosition().y);		
			(*it)->GetComponent(Physics_Component)->setPosition(obPosition);
		}				
	}
	scoreObject->GetComponent(Render_Component)->SetText("Score: "+to_string((int)score));

	auto input = InputInterface::GetInstance();
	

	if (input->IsActionTriggered(Input_ID::Up))
	{
		
	}
	if (input->IsActionTriggered(Input_ID::Down))
	{
		
	}
	if (input->IsActionTriggered(Input_ID::Left))
	{
		
	}
	if (input->IsActionTriggered(Input_ID::Right))
	{
		
	}
	if (input->IsActionTriggered(Input_ID::Space))
	{
		float jumpHeight = 0.5f;

		for (std::vector<GameObject*>::iterator it = script_objects.begin(); it != script_objects.end(); ++it)
		{
			float objMass = (*it)->GetComponent(Physics_Component)->GetObjectMass();
			float jumpImpulse = (*it)->GetComponent(Script_Component)->RunScript("jumpForce", objMass, jumpHeight);
			(*it)->GetComponent(Physics_Component)->AddForce(sf::Vector2f(0.0f, jumpImpulse));
		}		
	}
	
}

void EngineSystem::GameStatus()
{


	if (Player->GetComponent(Physics_Component)->GetTriggeredCollision())
	{
		Gameover->GetComponent(Render_Component)->SetText("GAME OVER!");
		
		TimePerFrame = sf::seconds(0);
		render();
	}
}

//Create Game Objects
void EngineSystem::CreateObject(std::string ObjectName, float x, float y)
{
	//Create new Object
	GameObject *ChildObj = new GameObject(ObjectName);

	//Get position coordinates and set object at position updating its transform (Default coords = 0,0)
	sf::Vector2f ObjectPosition(x, y);
	ChildObj->GetComponent(Transform_Component)->setPosition(ObjectPosition);

	//Add Child to GameManager graph
	GameObjectManager->AddChild(ChildObj);

	ChildObj->AddComponent(Render_Component);
	ChildObj->GetComponent(Render_Component)->setColor(sf::Color::Green);
}

//Find object with parent name in graph and assign it as parent to object  child name
void EngineSystem::SetObjectParent(std::string ObjParentName, std::string ObjChildName)
 {
	GameObject *ParentObject = GameObjectManager->FindGameObject(ObjParentName);
	//If we didnt find our desired parent object then no need to keep searching
	if (!ParentObject)
		return;

	GameObject *ChildObject = GameObjectManager->FindGameObject(ObjChildName);
	//If we didnt find child object then there is nothing to assign to parent
	if (!ChildObject)
		return;

	ParentObject->AddChild(ChildObject);
}

//Find object with name in graph and add specified component to it

void EngineSystem::AttachRenderComponent(std::string objName, sf::Vector2f size, sf::Color color, std::string text, std::string texturePath, int FontSize, std::string FontPath)
{
	GameObject *gameObject = GameObjectManager->FindGameObject(objName);
	if (!gameObject)
		return;

	gameObject->GetComponent(Render_Component)->SetTexture(texturePath);
	gameObject->GetComponent(Render_Component)->SetFont(FontPath);

	gameObject->AddComponent(Render_Component);
	gameObject->GetComponent(Render_Component)->setSize(size);
	gameObject->GetComponent(Render_Component)->SetText(text);
	gameObject->GetComponent(Render_Component)->SetTextSize(FontSize);
	gameObject->GetComponent(Render_Component)->setColor(color);
	gameObject->GetComponent(Render_Component)->SetTextColor(color);
}

void EngineSystem::AttachPhysicsComponent(std::string objName, float mass, bool hasGravity, sf::Vector2f Velocity)
{
	GameObject *gameObject = GameObjectManager->FindGameObject(objName);
	if (!gameObject)
		return;

	gameObject->AddComponent(Physics_Component);
	gameObject->GetComponent(Physics_Component)->AddRigidBodyToPhysicsSystem(*PhysicsEngine);
	gameObject->GetComponent(Physics_Component)->setPosition(gameObject->GetComponent(Transform_Component)->getPosition());
	gameObject->GetComponent(Physics_Component)->AddRenderComponentToRigidBody(gameObject->GetComponent(Render_Component));
	gameObject->GetComponent(Physics_Component)->SetObjectMass(mass);
	gameObject->GetComponent(Physics_Component)->SetHasGravity(hasGravity);
	gameObject->GetComponent(Physics_Component)->SetCurrentVelocity(Velocity);
}

void EngineSystem::AttachAudioComponent(std::string objName, std::string filePath, bool playOnAwake, bool Loop)
{
	GameObject *gameObject = GameObjectManager->FindGameObject(objName);
	if (!gameObject)
		return;

	gameObject->AddComponent(Audio_Component);
	gameObject->GetComponent(Audio_Component)->loadSound(filePath);
	gameObject->GetComponent(Audio_Component)->LoopSound(Loop);

	if (playOnAwake)
		gameObject->GetComponent(Audio_Component)->playSound();

}

void EngineSystem::AttachScriptComponent(std::string objName, std::string scriptName) 
 {
	GameObject *gameObject = GameObjectManager->FindGameObject(objName);
	if (!gameObject)
		return;

	gameObject->AddComponent(Script_Component);
	gameObject->GetComponent(Script_Component)->SetScriptName(scriptName);

	script_objects.push_back(gameObject);
}



