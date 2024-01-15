#pragma once
#ifndef ENTITY_ICON_H
#define ENTITY_ICON_H

#include "../BaseClasses/GameObject.h"
#include "../Config/Settings.h"

namespace entity
{
	using namespace baseclass;

	class Icon : public GameObject
	{
	public:
		Icon(std::string name) : GameObject(name) {}
		void initialize() override;
	};
}

#endif
#pragma once
