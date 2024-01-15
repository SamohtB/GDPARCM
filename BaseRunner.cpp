#include "BaseRunner.h"

using namespace gamecore;

BaseRunner::BaseRunner() : renderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Banatin, Thomas | GDPARCM", sf::Style::Titlebar | sf::Style::Close)
{
	this->renderWindow.setFramerateLimit(FRAME_RATE_LIMIT);
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
                break;
        }
    }
}

void BaseRunner::update(sf::Time deltaTime)
{
}

void BaseRunner::render()
{
    this->renderWindow.clear();
    this->renderWindow.display();
}
