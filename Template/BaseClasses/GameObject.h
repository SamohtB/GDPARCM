#pragma once
#ifndef BASECLASS_GAMEOBJECT_H
#define BASECLASS_GAMEOBJECT_H

#include <iostream>

#include "SFML/Graphics.hpp"

#include "Enums/ComponentType.h"
#include "Component.h"

#include "../Entities/Components/Input/GeneralInput.h"
#include "../Entities/Components/Renderer/Renderer.h"

namespace baseclass
{
	using namespace component;

	class GameObject
	{
	public:
		GameObject(std::string name);
		virtual ~GameObject() = default;

		virtual void initialize() = 0;
        virtual void processInput(sf::Event event);
        virtual void update(sf::Time deltaTime);
		virtual void physicsUpdate(sf::Time deltaTime);
        virtual void draw(sf::RenderWindow* window, sf::RenderStates renderStates);

		virtual sf::Vector2f getPosition();
		virtual void setPosition(sf::Vector2f position);
		virtual void setPosition(float x, float y);
		virtual void move(sf::Vector2f displacement);

		void attachComponent(Component* component);
        void detachComponent(Component* component);
        Component* findComponentByName(std::string name);
        std::vector<Component*> getComponents(ComponentType componentType);

		std::string getName();
		sf::Sprite* getSprite();

		bool getEnabledStatus();
		virtual void setEnabledStatus(bool status);
		
	protected:
		bool isEnabled;
		std::string name;
		sf::Sprite* sprite;

		std::vector<Component*> componentList;
	};
}

#endif // !GAMECORE_GAMEOBJECT_H
