#pragma once
enum Component_Definition
{
	Transform_Component,
	Render_Component,
	Audio_Component,
	Physics_Component,
	Script_Component,
	Default
};
struct PathHolder
{
	std::string cubeTexture = "../Assets/texture.jpg";
	std::string cubeTexture2 = "../Assets/texture2.jpg";
	std::string pipe = "../Assets/pipe2.png";
	std::string pipeUp = "../Assets/pipe.png";
	std::string player = "../Assets/player.png";
	std::string Splash = "../Assets/SplashScreen.PNG";
	std::string background = "../Assets/background.jpg";
};