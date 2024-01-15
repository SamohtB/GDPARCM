#include "FPSCounter.h"

using namespace entity;

void FPSCounter::initialize()
{
	sf::Font* font = new sf::Font();
	if(!font->loadFromFile("Media/Sansation.ttf"))
	{
		std::cerr << "FONT NOT FOUND" << std::endl;
	}

	this->statsText = new sf::Text();
	this->statsText->setFont(*font);
	this->statsText->setPosition(SCREEN_WIDTH - 150, SCREEN_HEIGHT - 100);
	this->statsText->setOutlineColor(sf::Color::White);
	this->statsText->setOutlineThickness(2.5f);
	this->statsText->setCharacterSize(35);

	Renderer* renderer = new Renderer(this->name + " Renderer");
	renderer->AssignDrawable(this->statsText);
	this->attachComponent(renderer);
}

void FPSCounter::update(sf::Time deltaTime)
{
	this->updateTime += deltaTime;
	if(this->updateTime >= sf::seconds(0.25f))
	{
		this->updateTime = sf::seconds(0.0f);
		float fps = 1.0f / deltaTime.asSeconds();
		this->statsText->setString("FPS: " + std::to_string((int)fps) + "\n");
	}
}

