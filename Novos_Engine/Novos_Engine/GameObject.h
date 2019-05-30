#pragma once
#include "stdafx.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "AudioComponent.h"
#include "BaseComponent.h"
#include "ScriptComponent.h"
#include "RigidBody.h"
#include "InputInterface.h"
#include "CustomTypes.h"
#include <unordered_map> 



class GameObject
{
public:
	GameObject(std::string GameObjectName);
	~GameObject();

	void AddChild(GameObject* Obj);
	GameObject* FindGameObject(std::string ObjectName);
	
	// Create Component
	void AddComponent(Component_Definition Component);

	// Get Component from list
	BaseComponent *GetComponent(Component_Definition ComponentName);
	
	void Update(sf::Time dt);		
	void RenderGO(sf::RenderWindow &win);


private:
	std::string GameObjectTag;
	std::unordered_map<Component_Definition, BaseComponent*> m_ComponentMap;
	std::unordered_map<std::string, GameObject*> ChildrenMap;
		
protected:
	GameObject* parent;
	std::vector<GameObject*> children;

private:
	void AddRenderComponent();
	void AddAudioComponent();
	void AddRigidBody();
	void AddScriptComponent();
};

