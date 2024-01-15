#pragma once
#ifndef SINGLETON_GAMEOBJECT_MANAGER_H
#define SINGLETON_GAMEOBJECT_MANAGER_H

#include "SFML/Graphics.hpp"
#include "../../BaseClasses/GameObject.h"

namespace singleton
{
    using namespace baseclass;

    class GameObjectManager : private sf::NonCopyable
    {
    public:
        GameObjectManager() {}
		static GameObjectManager* getInstance();


        void processInput(sf::Event event);
        void update(sf::Time deltaTime);
        void physicsUpdate(sf::Time deltaTime);
        void draw(sf::RenderWindow* window);

        void addObject(GameObject* gameObject);

    private:
    	static GameObjectManager* sharedInstance;

        std::vector<GameObject*> gameObjectList;
    };
}
#endif // !SINGLETON_PHYSICS_GENERATOR_MANAGER_H


