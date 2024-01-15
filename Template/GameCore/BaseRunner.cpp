#include "BaseRunner.h"

#include "Managers/GameObjectManager.h"

using namespace gamecore;

BaseRunner::BaseRunner() : renderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
    "Banatin, Thomas | GDPARCM", sf::Style::Titlebar | sf::Style::Close)
{
	this->renderWindow.setFramerateLimit(FRAME_RATE_LIMIT);

    TextureManager::getInstance()->loadAll();

    auto object = new BGObject("Desert BG");
    GameObjectManager::getInstance()->addObject(object);

    auto display = new TextureDisplay("Texture Display");
    GameObjectManager::getInstance()->addObject(display);

    auto counter = new FPSCounter("FPS Counter");
    GameObjectManager::getInstance()->addObject(counter);

}

void BaseRunner::run()
{
    sf::Clock clock = sf::Clock();
    sf::Time lastUpdate = sf::Time::Zero;
    sf::Time timePerFrame = sf::seconds(1.0f / FRAME_RATE_LIMIT);

    while(this->renderWindow.isOpen()) 
    {
        this->processInput();
        lastUpdate += clock.restart();

        while(lastUpdate > timePerFrame) 
        {
            lastUpdate -= timePerFrame;
            this->update(timePerFrame);
        }

        this->render();
        this->fps = 1.0f / timePerFrame.asSeconds();
    }
}

void BaseRunner::processInput()
{
    sf::Event eEvent;

    while(this->renderWindow.pollEvent(eEvent)) 
    {
        switch(eEvent.type) 
        {
            case sf::Event::Closed:
                this->renderWindow.close();
                break;

        default:
                GameObjectManager::getInstance()->processInput(eEvent);
                break;
        }
    }
}

void BaseRunner::update(sf::Time deltaTime)
{
    GameObjectManager::getInstance()->update(deltaTime);
}

void BaseRunner::render()
{
    this->renderWindow.clear();

    GameObjectManager::getInstance()->draw(&renderWindow);

    this->renderWindow.display();
}

float BaseRunner::getFPS()
{
	return this->fps;
}

BaseRunner* BaseRunner::sharedInstance = nullptr;

BaseRunner* BaseRunner::getInstance()
{
    if(sharedInstance == nullptr)
    {
        sharedInstance = new BaseRunner();
    }

    return sharedInstance;
}
