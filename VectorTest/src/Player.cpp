#include <SFML/Graphics.hpp>
#include "../include/Player.h"
#include <iostream>

extern float AccelGravity;
extern float MaxGravity;

Player::Player(float X, float Y, float W, float H, sf::Texture& t) : playerDirection(Left)
{
	setTexture(t);
	setPosition(X, Y);
	Speed = 6;
	JumpHeight = 18;
	setOrigin(W / 2, 0);

	size.x = W;
	size.y = H;
}

void Player::Update(bool &W, bool &A, bool &S, bool &D, std::vector <Platform>& WorldPlats)
{
	if (W && OnGround) velocity.y = JumpHeight * -1;
	
	if (OnGround == false)
	{
		velocity.y += AccelGravity;
		if (velocity.y > MaxGravity) velocity.y = MaxGravity;
	}

	if (A)
	{
		velocity.x = -1;
		setScale(1, 1);
		playerDirection = Left;
	}

	if (D)  
	{
		velocity.x = 1;
		setScale(-1, 1);
		playerDirection = Right;
	}

	if (!(A or D)) velocity.x = 0;

	move(velocity.x * Speed, 0);
	Collide(velocity.x * Speed, 0, WorldPlats);

	OnGround = false;
	move(0, velocity.y);
	Collide(0, velocity.y, WorldPlats);
}

void Player::Collide(float xvel, float yvel, std::vector<Platform>& WorldPlats)
{
	for (Platform& p : WorldPlats)
	{
		if (getPosition().x - size.x / 2 < p.hitbox.Right &&
			getPosition().x + size.x / 2 > p.hitbox.Left &&
			getPosition().y < p.hitbox.Bottom &&
			getPosition().y + size.y > p.hitbox.Top)
		{
			Collision = true;
		}
		else
		{
			Collision = false;
		}
		if (Collision)
		{
			if (xvel > 0)
			{
				setPosition(p.hitbox.Left - size.x / 2, getPosition().y);
				velocity.x = 0;
			}
			if (xvel < 0)
			{
				setPosition(p.hitbox.Right + size.x / 2, getPosition().y);
				velocity.x = 0;
			}
			if (yvel > 0)
			{
				setPosition(getPosition().x, p.hitbox.Top - size.y);
				velocity.y = 0;
				OnGround = true;
			}
			if (yvel < 0)
			{
				setPosition(getPosition().x, p.hitbox.Bottom);
				velocity.y = 0;
			}
		}
	}
}