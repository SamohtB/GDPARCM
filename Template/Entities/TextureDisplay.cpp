#include "TextureDisplay.h"

using namespace entity;

void TextureDisplay::initialize() {}

void TextureDisplay::update(sf::Time deltaTime)
{
	if(index > 480) { return; }

	this->ticks += deltaTime.asSeconds();

	if(this->ticks >= 0.5f)
	{
		this->ticks = 0.0f;

		std::string name = "Icon_" + std::to_string(index);

		EmptyGameObject* object = new EmptyGameObject(name);

		sf::Texture* texture = TextureManager::getInstance()->getTexture(AssetType::ICON)[index];
		object->setTexture(texture);
		object->setEnabledStatus(true);

		auto renderer = new Renderer(name + " Renderer");
		renderer->AssignDrawable(object->getSprite());
		object->attachComponent(renderer);

		GameObjectManager::getInstance()->addObject(object);

		float row = static_cast<float>(index / 29);
		float col = static_cast<float>(index % 29);

		float x = col * 65;
		float y = row * 65;

		object->getSprite()->setTextureRect(sf::IntRect(0, 0, 64, 64));
		object->setPosition(x, y);

		index++;
	}
}

