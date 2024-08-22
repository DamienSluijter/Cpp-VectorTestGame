#include "../include/Bullet.h"
#include "SFML/Graphics.hpp"

Bullet::Bullet(float W, float H)
{
    size.x = W;
    size.y = H;
    velocity = sf::Vector2f(0, 0);
    setScale(-1, 1);
}

void Bullet::SetVelocity(sf::Vector2f vel)
{
    velocity = vel;
}

void Bullet::Fire()
{
    move(velocity);
}

void Bullet::SetPos(sf::Vector2f BulletPos)
{
    setPosition(BulletPos);
}

void Bullet::SetTex(sf::Texture& tex)
{
    setTexture(tex);
}

void Bullet::Update()
{
    Fire();
}