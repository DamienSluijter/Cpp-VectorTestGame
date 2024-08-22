#pragma once
#include "Entity.h"
#include "Platform.h"

class Platform : public Entity
{
private:
	
public:
	Platform(float X, float Y, float W, float H, sf::Texture& Pt);
};
