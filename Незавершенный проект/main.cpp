#include <iostream>
#include <SFML/Graphics.hpp>
#include "maps.h"
#include "Player.h"
#include "enemy.h"

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(1366, 768), "Test");

	Player player;
	Enemy enemy;

	Clock clock;

	float invistime = 0;

	RectangleShape tile_rect(Vector2f(32.f, 32.f));

	while ((window.isOpen()) && (player.life > 0))
	{
		float time = (float)clock.getElapsedTime().asMilliseconds();
		clock.restart();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::A))
			player.dx = -0.1;
		if (Keyboard::isKeyPressed(Keyboard::D))
			player.dx = 0.1;
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			player.crouch = true;
			if (Keyboard::isKeyPressed(Keyboard::Space))
				player.tileActive = false;
			else
				player.tileActive = true;
		}
		else
			player.crouch = false;
		if ((Keyboard::isKeyPressed(Keyboard::Space)) && (player.onGround) && (!player.crouch)) {
			player.dy = -0.45;
			player.onGround = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::LShift))
			player.dx = player.dx * 2;

		if (player.rect.intersects(enemy.rect) && !player.invis)
		{
			player.life -= 1;
			player.invis = true;
			std::cout << "player life = " << player.life << "\n";
		}

		if (player.invis)
		{
			invistime += time;
			if (invistime > 600)
			{
				player.invis = false;
				invistime = 0;
			}
		}

		player.update(time);
		enemy.update(time);

		window.clear(Color::White);

		for (int i = 0; i < height_map; i++)
			for (int j = 0; j < width_map; j++)
			{
				if (TileMap[i][j] == '0')
				{
					tile_rect.setFillColor(Color::Black);
				}
				if (TileMap[i][j] == '1')
				{
					if (player.tileActive) tile_rect.setFillColor(Color::Red);
					else tile_rect.setFillColor(Color::Green);
				}
				if (TileMap[i][j] == ' ')
				{
					continue;
				}
				
				tile_rect.setPosition(j * 32, i * 32);
				window.draw(tile_rect);
			}

		window.draw(player.rectangle);
		window.draw(enemy.rectangle);
		window.display();
	
	}	

	return 0;
}

/*
#include "Game.h"

using namespace sf;

int main()
{
	Game game;
	game.run();
}
*/
