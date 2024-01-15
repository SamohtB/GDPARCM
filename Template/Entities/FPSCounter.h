#pragma once
#ifndef ENTITY_FPSCOUNTER_H
#define ENTITY_FPSCOUNTER_H

#include "../BaseClasses/GameObject.h"
#include "../Config/Settings.h"

#include "../GameCore/BaseRunner.h"

namespace gamecore {
    class BaseRunner;
}

namespace entity
{
	using namespace baseclass;

	class FPSCounter : public GameObject
	{
	public:
		FPSCounter(std::string name) : GameObject(name) {}
		void initialize() override;
		void update(sf::Time deltaTime) override;

	private:
		sf::Text* statsText = nullptr;
		sf::Time updateTime = sf::seconds(0.0f);
	};
}

#endif
