#pragma once
#include "Entity.h"
#include "Platform.h"
#include <vector>

class Player : public Entity
{
private:
	bool Collision;
	float Speed;
	bool OnGround;
	float JumpHeight;

public:
	enum Direction { Left, Right };
	Direction playerDirection;

	Player(float X, float Y, float W, float H, sf::Texture& t);
	void Update(bool &W, bool &A, bool &S, bool &D, std::vector <Platform>& WorldPlats);
	void Collide(float xvel, float yvel, std::vector<Platform>& WorldPlats);
};
