#pragma once
#ifndef BASE_CLASS_EMPTY_GAME_OBJECT_H
#define BASE_CLASS_EMPTY_GAME_OBJECT_H

#include "GameObject.h"
namespace baseclass
{
	class EmptyGameObject : public GameObject
	{
	public:
		EmptyGameObject(std::string name);
		~EmptyGameObject() override;

        void initialize() override;
		void setTexture(sf::Texture* texture);

	private:
		sf::Texture* texture;
	};
}


#endif // !BASE_CLASS_EMPTY_GAME_OBJECT_H



