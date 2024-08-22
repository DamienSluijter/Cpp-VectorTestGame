#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "../include/Player.h"
#include "../include/Bullet.h"

float AccelGravity = 1.0f;
float MaxGravity = 12.0f;

bool IsFiring = false;

int main()
{

	sf::RenderWindow window(sf::VideoMode(1200, 800), "Game");
	window.setFramerateLimit(60);

	sf::Clock shotClock;
	float shotCooldown = 0.2f;  

	bool W, A, S, D, Space;

	sf::Texture t;
	t.loadFromFile("images/playerScale.png");

	sf::Texture Pt;
	Pt.loadFromFile("images/PlatformBlock.png");

	sf::Texture Bu;
	Bu.loadFromFile("images/Bullet.png");
	
	Player player(70, -100, 56, 83, t);

	int WorldArray[10][20] = { {1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
						       {1,1,1,0,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0},
						       {1,0,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0},
						       {1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
						       {0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0},
						       {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0},
						       {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0},
						       {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},
						       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						       {1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0}, };

	std::vector <Bullet> bulletVec;
	
	std::vector <Platform> WorldPlats;

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (WorldArray[j][i] == 1)
			{
				Platform p(i * 70, j * 70, 70, 70, Pt);
				WorldPlats.push_back(p);
			}
		}
	}
	sf::View view(sf::Vector2f(0, 0), sf::Vector2f(1200, 800));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		W = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
		A = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		S = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		D = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
		Space = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

		if (Space && shotClock.getElapsedTime().asSeconds() > shotCooldown)
		{
			IsFiring = true;
			shotClock.restart();
		}

		if (IsFiring)
		{
			Bullet newBullet(3, 3);
			newBullet.SetTex(Bu);
			newBullet.SetPos(sf::Vector2f(player.getPosition().x + player.size.x / 2, player.getPosition().y + player.size.y / 2));

			// Set bullet velocity based on the player's direction
			if (player.playerDirection == Player::Left)
			{
				newBullet.SetVelocity(sf::Vector2f(-15.0f, 0)); // Left
			}
			else if (player.playerDirection == Player::Right)
			{
				newBullet.SetVelocity(sf::Vector2f(15.0f, 0)); // Right
			}

			bulletVec.push_back(newBullet);
			IsFiring = false;
		}


			if (bulletVec.size() > 10)
			{
				bulletVec.erase(bulletVec.begin());
			}
		
			
			
		player.Update(W, A, S, D, WorldPlats);
		view.setCenter(player.getPosition().x + player.size.x / 2, player.getPosition().y + player.size.y / 2);

		window.setView(view);
		window.clear(sf::Color(135, 206, 235));

		std::cout << bulletVec.size() << std::endl;
		
		for (Platform& p : WorldPlats)
		{
			window.draw(p);
		}

		for (int i = 0; i < bulletVec.size(); i++) {
			bulletVec[i].Update();  // Update each bullet
			window.draw(bulletVec[i]);  // Draw each bullet
		}

        window.draw(player);
		window.display();
	}
	return 0;
}

