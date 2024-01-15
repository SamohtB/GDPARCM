#include "BGObject.h"

using namespace entity;

void BGObject::initialize()
{
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getTexture(AssetType::BACKGROUND)[0];
	texture->setRepeated(true);
	this->sprite->setTexture(*texture);
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();

	this->sprite->setTextureRect(sf::IntRect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT * 8));
	this->setPosition(sf::Vector2f(0, -SCREEN_HEIGHT * 7));

	Renderer* renderer = new Renderer(this->name + " Renderer");
	renderer->AssignDrawable(this->sprite);
	this->attachComponent(renderer);
}

void BGObject::update(sf::Time deltaTime)
{
	sf::Vector2f position = this->getPosition();
	position.y += SCROLL_SPEED * deltaTime.asSeconds();
	this->setPosition(position);

	sf::Vector2f localPos = this->sprite->getPosition();
	if(localPos.y * deltaTime.asSeconds() >0)
	{
		this->setPosition(sf::Vector2f(0, -SCREEN_HEIGHT * 7));
	}
}

