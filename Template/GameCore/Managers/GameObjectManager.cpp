#include "GameObjectManager.h"

using namespace singleton;

void GameObjectManager::processInput(sf::Event event)
{
    for(GameObject* gameObject : this->gameObjectList)
    {
        gameObject->processInput(event);
    }
}

void GameObjectManager::update(sf::Time deltaTime)
{
    int max = this->gameObjectList.size();
    for(int i = 0; i < max; i++)
    {
        this->gameObjectList[i]->update(deltaTime);
    }
}

void GameObjectManager::physicsUpdate(sf::Time deltaTime)
{
    for(GameObject* gameObject : this->gameObjectList)
    {
        gameObject->physicsUpdate(deltaTime);
    }
}

void GameObjectManager::draw(sf::RenderWindow* window)
{
    for(GameObject* gameObject : this->gameObjectList)
    {
        gameObject->draw(window, sf::RenderStates::Default);
    }
}

void GameObjectManager::addObject(GameObject* gameObject)
{
    this->gameObjectList.push_back(gameObject);
    gameObject->initialize();
}

GameObjectManager* GameObjectManager::sharedInstance = nullptr;

GameObjectManager* GameObjectManager::getInstance()
{
    if(sharedInstance == nullptr)
        sharedInstance = new GameObjectManager();

    return sharedInstance;
}