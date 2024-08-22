#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::Sprite {
private:
    sf::Vector2f velocity;
    sf::Vector2f size;

public:
    Bullet(float W, float H);

    void SetVelocity(sf::Vector2f vel);
    void Fire();
    void SetPos(sf::Vector2f BulletPos);
    void SetTex(sf::Texture& tex);
    void Update();
};