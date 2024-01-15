#pragma once
#ifndef SINGLETON_TEXTURE_MANAGER_H
#define SINGLETON_TEXTURE_MANAGER_H

#include <iostream>
#include <unordered_map>
#include "SFML/Graphics.hpp"
#include "../../BaseClasses/Enums/AssetType.h"

namespace singleton
{

    class TextureManager : private sf::NonCopyable
    {
    public:
        TextureManager() {}
		static TextureManager* getInstance();
        std::vector<sf::Texture*> getTexture(AssetType eType, int nStart = -1, int nEnd = -1);

	private:
		std::unordered_map<AssetType, std::vector<sf::Texture*>> mapTexture;

	public:
		void loadAll();
		

    private:
    	static TextureManager* sharedInstance;
    };
}
#endif // !SINGLETON_PHYSICS_GENERATOR_MANAGER_H


