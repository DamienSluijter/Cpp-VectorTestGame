#include <SFML/Graphics.hpp>
#include "../include/Platform.h"
#include <vector>

Platform::Platform(float X, float Y, float W, float H, sf::Texture& Pt)
{
	size.x = W;
	size.y = H;
	
	setTexture(Pt);
	setPosition(X, Y);

	hitbox.Left = X;
	hitbox.Right = X + size.x;
	hitbox.Top = Y;
	hitbox.Bottom = Y + size.y;

}