#include <SFML/Graphics.hpp>
#include "maps.h"

using namespace sf;

class Player
{
public:
	float dx, dy, posX;
	FloatRect rect;
	bool onGround;
	RectangleShape rectangle;

	Player()
	{
		rect = FloatRect(100, 100, 75, 100);
		posX = rect.left;
		dx = dy = 0.1;
		onGround = false;
	}

	void update(float time)
	{
		rect.left += dx * time;
		Collision(0);

		if (!onGround)
		{
			dy = dy + 0.0005 * time;
		}
		rect.top += dy * time;
		onGround = false;		
		Collision(1);

		rectangle.setSize(Vector2f(rect.width, rect.height));
		rectangle.setFillColor(Color::Red);
		rectangle.setPosition(rect.left, rect.top);		
		
		dx = 0;
	}

	void Collision(int dir)
	{
		for (int i = rect.top/32; i < (rect.top + rect.height)/32; i++)
			for (int j = rect.left/32; j < (rect.left + rect.width)/32; j++)
			{

				if (TileMap[i][j] == '0')
				{
					if ((dx > 0) && (dir == 0))
					{
						rect.left = j * 32 - rect.width;
					}
					if ((dx < 0) && (dir == 0))
					{
						rect.left = j * 32 + 32;
					}
					if ((dy > 0) && (dir == 1))
					{
						rect.top = i * 32 - rect.height;
						dy = 0;
						onGround = true;
					}
					if ((dy < 0) && (dir == 1))
					{
						rect.top = i * 32 + 32;
						dy = 0;
					}
				}

			}
	}

};

int main()
{
	RenderWindow window(VideoMode(1366, 768), "Test");

	Player player;

	Clock clock;

	RectangleShape tile_rect(Vector2f(32.f, 32.f));

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}
	
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			player.dx = -0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			player.dx = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			if (player.onGround)
			{
				player.dy = -0.4;
				player.onGround = false;
			}
		}		 

		player.update(time);

		window.clear(Color::White);

		for (int i = 0; i < height_map; i++)
			for (int j = 0; j < width_map; j++)
			{
				if (TileMap[i][j] == '0')
				{
					tile_rect.setFillColor(Color::Black);
				}
				if (TileMap[i][j] == ' ')
				{
					continue;
				}
				
				tile_rect.setPosition(j * 32, i * 32);
				window.draw(tile_rect);
			}

		window.draw(player.rectangle);
		window.display();
	
	}	

	return 0;
}