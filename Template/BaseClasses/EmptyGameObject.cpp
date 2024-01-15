#include "EmptyGameObject.h"

using namespace baseclass;

EmptyGameObject::EmptyGameObject(std::string strName) : GameObject(strName) {}

EmptyGameObject::~EmptyGameObject() {}

void EmptyGameObject::initialize() {}

void EmptyGameObject::setTexture(sf::Texture* texture)
{
	this->sprite = new sf::Sprite();
	this->texture = texture;
	this->sprite->setTexture(*texture);

}
