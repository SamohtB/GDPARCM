#include "TextureManager.h"

using namespace singleton;

void TextureManager::loadAll() 
{
    sf::Texture* pTexture = nullptr;

    pTexture = new sf::Texture();

    if(!pTexture->loadFromFile("Media/Textures/Desert.png"))
    {
        std::cerr << "BACKGROUND TEXTURE NOT FOUND" << std::endl;
    }

    this->mapTexture[AssetType::BACKGROUND].push_back(pTexture);

    for(int i = 0; i < 480; i++)
    {
    	pTexture = new sf::Texture();
        std::string formattedIndex;

        if(i / 10 == 0)
        {
	        formattedIndex = "00" + std::to_string(i);
        }
        else if (i / 100 == 0)
        {
	        formattedIndex = "0" + std::to_string(i);
        }
        else
        {
	        formattedIndex = std::to_string(i);
        }

		std::string fileName = "Media/Streaming/tile" + formattedIndex + ".png";

        std::cout << fileName + " loaded" << std::endl;

		if (!pTexture->loadFromFile(fileName))
		{
			std::cerr << "BACKGROUND TEXTURE NOT FOUND" << std::endl;
		}

        this->mapTexture[AssetType::ICON].push_back(pTexture);
    }
}

std::vector<sf::Texture*> TextureManager::getTexture(AssetType eType, int nStart, int nEnd) 
{
    if(nStart == -1)
        return this->mapTexture[eType];

    else {
        std::vector<sf::Texture*> vecTexture = this->mapTexture[eType];
        std::vector<sf::Texture*>::const_iterator iStart = vecTexture.begin() + nStart;

        if(nEnd == -1)
            nEnd = nStart + 1;

        std::vector<sf::Texture*>::const_iterator iEnd = vecTexture.begin() + nEnd + 1;
        std::vector<sf::Texture*> vecSublist = std::vector(iStart, iEnd);

        return vecSublist;
    }
}

TextureManager* TextureManager::sharedInstance = nullptr;

TextureManager* TextureManager::getInstance()
{

    if(sharedInstance == nullptr)
    {
	    sharedInstance = new TextureManager();
    }

    return sharedInstance;
}
