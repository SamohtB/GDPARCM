#pragma once
#ifndef ENTITY_TEXTURE_DISPLAY_H
#define ENTITY_TEXTURE_DISPLAY_H

#include "../BaseClasses/GameObject.h"
#include "../Config/Settings.h"
#include "../BaseClasses/EmptyGameObject.h"

#include "../GameCore/Managers/GameObjectManager.h"
#include "../GameCore/Managers/TextureManager.h"

namespace entity
{
	using namespace baseclass;
	using namespace singleton;

	class TextureDisplay : public GameObject
	{
	public:
		TextureDisplay(std::string name) : GameObject(name) {}
		void initialize() override;
		void update(sf::Time deltaTime) override;

	private:
		unsigned index = 0;
		float ticks = 0.0f;
	};
}

#endif
