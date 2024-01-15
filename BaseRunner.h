#pragma once
#ifndef GAMECORE_GAME_H
#define GAMECORE_GAME_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "Config/Settings.h"

namespace gamecore
{
	class BaseRunner : private sf::NonCopyable
	{
	public:
		BaseRunner();
		void run();

		static BaseRunner* getInstance();
		static BaseRunner* sharedInstance;
		float getFPS();

	private:
		sf::RenderWindow renderWindow;
		float fps = 0.0f;

		void processInput();
		void update(sf::Time deltaTime);
		void render();
	};
}

#endif


