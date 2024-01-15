#pragma once
#ifndef GAMECORE_GAME_H
#define GAMECORE_GAME_H

#include <chrono>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "../Config/Settings.h"

#include "Managers/TextureManager.h"
#include "Managers/GameObjectManager.h"

#include "../Entities/BGObject.h"
#include "../Entities/FPSCounter.h"
#include "../Entities/TextureDisplay.h"

namespace gamecore
{
	using namespace singleton;
	using namespace entity;

	class BaseRunner : private sf::NonCopyable
	{
	public:
		BaseRunner();
		void run();

		static BaseRunner* getInstance();
		float getFPS();

	private:
		static BaseRunner* sharedInstance;
		sf::RenderWindow renderWindow;

		void processInput();
		void update(sf::Time deltaTime);
		void render();

		std::chrono::high_resolution_clock::time_point start;
		std::chrono::high_resolution_clock::time_point end;
		float fps = 0.0f;
	};
}

#endif


