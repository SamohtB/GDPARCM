#pragma once
#ifndef ENTITY_BGObject_H
#define ENTITY_BGObject_H

#include "../BaseClasses/GameObject.h"
#include "../GameCore/Managers/TextureManager.h"
#include "../Config/Settings.h"

namespace entity
{
	using namespace baseclass;
	using namespace singleton;

	class BGObject : public GameObject
	{
	public:
		BGObject(std::string name) : GameObject(name) {}
		void initialize() override;
		void update(sf::Time deltaTime) override;

	private:
		float SCROLL_SPEED = 20.0f;
	};
}

#endif
