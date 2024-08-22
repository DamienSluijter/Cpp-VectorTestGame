#pragma once
#include "Hitbox.h"

class Entity : public sf::Sprite
{
public:
	sf::Vector2f velocity, size;
	Hitbox hitbox;
};
