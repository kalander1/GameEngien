#include "stdafx.h"
#include "EngineSystem.h"
#include "SystemInitializer.h"
#include "CustomTypes.h"
#include "JsonParser.h"
#include <string>

using namespace std;
void CreateGameObjects(EngineSystem &engine);
PathHolder pathHolder;
int main()
{
	//Initializing system check
	SystemInitializer* systemInit = nullptr;
	systemInit = new SystemInitializer();
	
	JsonParser jsonParser;
	
	if (systemInit->Run() == false)
	{
		MessageBox(NULL,_T("Multiple Instances Running!"),_T("Novos Engine"),NULL);
		return 0;
	}
	//delete systemInit;

	//Creating window
	EngineSystem GAME_ENGINE;

	CreateGameObjects(GAME_ENGINE);

	GAME_ENGINE.InitWindow();
	


	return 0;
}

void CreateGameObjects(EngineSystem &engine)
{


	engine.CreateObject("Score", -450, -350.0f);
	engine.AttachRenderComponent("Score", sf::Vector2f(0, 0), sf::Color::White, "Score: ");
	
	engine.CreateObject("background");
	engine.AttachRenderComponent("background", sf::Vector2f(1024, 720), sf::Color::White, "", pathHolder.background);
	engine.SetObjectParent("background","Score");
	engine.CreateObject("Player", -350.0f, -200.0f);
	engine.AttachRenderComponent("Player", sf::Vector2f(50.f, 50.0f), sf::Color::White, "", pathHolder.player);
	engine.AttachPhysicsComponent("Player", 2.0f, true, sf::Vector2f(0.0f, 0.0f));
	engine.AttachScriptComponent("Player", "Jump.lua");
	engine.AttachAudioComponent("Player", "../Assets/ClaimToFame.wav", true, true);

	engine.CreateObject("0gameOver", -250, 0);
	engine.AttachRenderComponent("0gameOver", sf::Vector2f(0, 0), sf::Color::Black, "", "", 100);


	float xPos = 0.0f;
	float pipeDist_x = 250.0f;
	float velocity = -80.f;

	// First pipe pair
	engine.CreateObject("3GreenPipe1", xPos, -180.0f);
	engine.AttachRenderComponent("3GreenPipe1", sf::Vector2f(90.f, 400.0f), sf::Color::White,"",pathHolder.pipe);
	engine.AttachPhysicsComponent("3GreenPipe1", 0.0f, false, sf::Vector2f(velocity, 0.0f));
	engine.AttachScriptComponent("3GreenPipe1", "OutsideView.lua");



	engine.CreateObject("3GreenPipe2", xPos, 350.0f);
	engine.AttachRenderComponent("3GreenPipe2", sf::Vector2f(90.f, 300.0f), sf::Color::White, "", pathHolder.pipeUp);
	engine.AttachPhysicsComponent("3GreenPipe2", 0.0f, false, sf::Vector2f(velocity, 0.0f));
	engine.AttachScriptComponent("3GreenPipe2", "OutsideView.lua");


	xPos += pipeDist_x;

	// Second pipe pair
	engine.CreateObject("3GreenPipe3", xPos, -300.0f);
	engine.AttachRenderComponent("3GreenPipe3", sf::Vector2f(90.f, 220.0f), sf::Color::White, "", pathHolder.pipe);
	engine.AttachPhysicsComponent("3GreenPipe3", 0.0f, false, sf::Vector2f(velocity, 0.0f));
	engine.AttachScriptComponent("3GreenPipe3", "OutsideView.lua");



	engine.CreateObject("3GreenPipe4", xPos, 200.0f);
	engine.AttachRenderComponent("3GreenPipe4", sf::Vector2f(90.f, 400.0f), sf::Color::White, "", pathHolder.pipeUp);
	engine.AttachPhysicsComponent("3GreenPipe4", 0.0f, false, sf::Vector2f(velocity, 0.0f));

	engine.AttachScriptComponent("3GreenPipe4", "OutsideView.lua");


	xPos += pipeDist_x;

	// Third pipe pair
	engine.CreateObject("3GreenPipe5", xPos, -230.0f);
	engine.AttachRenderComponent("3GreenPipe5", sf::Vector2f(90.f, 375.0f), sf::Color::White, "", pathHolder.pipe);
	engine.AttachPhysicsComponent("3GreenPipe5", 0.0f, false, sf::Vector2f(velocity, 0.0f));

	engine.AttachScriptComponent("3GreenPipe5", "OutsideView.lua");



	engine.CreateObject("3GreenPipe6", xPos, 300.0f);
	engine.AttachRenderComponent("3GreenPipe6", sf::Vector2f(90.f, 400.0f), sf::Color::White, "", pathHolder.pipeUp);
	engine.AttachPhysicsComponent("3GreenPipe6", 0.0f, false, sf::Vector2f(velocity, 0.0f));

	engine.AttachScriptComponent("3GreenPipe6", "OutsideView.lua");



	xPos += pipeDist_x;

	// Fourth pipe pair
	engine.CreateObject("GreenPipe7", xPos, -165.0f);
	engine.AttachRenderComponent("GreenPipe7", sf::Vector2f(90.f, 450.0f), sf::Color::White, "", pathHolder.pipe);
	engine.AttachPhysicsComponent("GreenPipe7", 0.0f, false, sf::Vector2f(velocity, 0.0f));

	engine.AttachScriptComponent("GreenPipe7", "OutsideView.lua");


	engine.CreateObject("3GreenPipe8", xPos, 390.0f);
	engine.AttachRenderComponent("3GreenPipe8", sf::Vector2f(90.f, 300.0f), sf::Color::White, "", pathHolder.pipeUp);
	engine.AttachPhysicsComponent("3GreenPipe8", 0.0f, false, sf::Vector2f(velocity, 0.0f));
	engine.AttachScriptComponent("3GreenPipe8", "OutsideView.lua");


	//xPos += pipeDist_x;

	//// Fifth pipe pair
	//engine.CreateObject("GreenPipe9", xPos, -280.0f);
	//engine.AttachRenderComponent("GreenPipe9", sf::Vector2f(70.f, 225.0f), sf::Color::Green);
	//engine.AttachPhysicsComponent("GreenPipe9", 0.0f, false, sf::Vector2f(-50.f, 0.0f));
	//engine.CreateObject("GreenPipe10", xPos, 300.0f);
	//engine.AttachRenderComponent("GreenPipe10", sf::Vector2f(70.f, 500.0f), sf::Color::Green);
	//engine.AttachPhysicsComponent("GreenPipe10", 0.0f, false, sf::Vector2f(-50.f, 0.0f));

}