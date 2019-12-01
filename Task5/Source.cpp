#include "Map.h"
#include "view.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

//Класс игрока
class Player
{
private:
	float x, y;
public:
	float w, h, dx, dy, speed; // координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
	int dir; // направление (direction) движения игрока
	bool onGround;
	enum {left, right, up, down, jump, stay} state;
	String File; // файл с расширением
	Image image;
	Texture texture;
	Sprite sprite;

	Player(String F, float X, float Y, float W, float H)
	{
		dx = 0;
		dy = 0;
		speed = 0;
		dir = 0;
		onGround = false;
		File = F;
		w = W;
		h = H;
		image.loadFromFile("Assets/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X;
		y = Y;
		sprite.setTextureRect(IntRect(0, 0, w, h));
		sprite.setOrigin(w / 2, 0);
	}

	void update(float time)
	{
		switch(dir)
		{
		case 0:
			dx = speed;
			dy = 0;
			break;
		case 1: 
			dx = -speed; 
			dy = 0; 
			break;
		case 2: 
			dx = 0; 
			dy = speed; 
			break;
		case 3: 
			dx = 0; 
			dy = -speed; 
			break;
		}

		x += dx * time;
		y += dy * time;

		speed = 0;
		sprite.setPosition(x, y);
		InteractionWithMap();
	}

	void InteractionWithMap()
	{

		for (int i = y / 32; i < (y + h) / 32; i++)
		{
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				if (TileMap[i][j] == '4')
				{
					if (dx < 0)
					{
						x = j * 32 + 32;
					}
				}
			}
		}

	}

	float GetPlayerCoordinateX()
	{
		return x;
	}

	float GetPlayerCoordinateY()
	{
		return y;
	}
};

int main()
{

	RenderWindow window(VideoMode(1920, 1080), "Game");

	view.reset(FloatRect(0, 0, 1366, 768));

	float CurrentFrame = 0;
	Clock clock;

	Player p("Character.png", 250, 250, 96.0, 96.0);

	Image map_image;
	map_image.loadFromFile("Assets/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 400;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
		{
			p.sprite.setScale(-1, 1);
			p.dir = 1;
			p.speed = 0.1;
			CurrentFrame += 0.003 * time;
			if (CurrentFrame > 4)
			{
				CurrentFrame -= 4;
			}
			p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
			GetPlayerCoordinateForView(p.GetPlayerCoordinateX(), p.GetPlayerCoordinateY());
		}
		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
		{			
			p.sprite.setScale(1, 1);
			p.dir = 0;
			p.speed = 0.1;
			CurrentFrame += 0.003 * time;
			if (CurrentFrame > 4)
			{
				CurrentFrame -= 4;
			}
			p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
			GetPlayerCoordinateForView(p.GetPlayerCoordinateX(), p.GetPlayerCoordinateY());
		}
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			p.sprite.setColor(Color::Blue);
		}

		p.update(time);

		window.setView(view);
		window.clear();
		// Рисуем карту
		for (int i = 0; i < HEIGHT_MAP; i++)
		{
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == '1')
				{
					s_map.setTextureRect(IntRect(0, 0, 64, 64));
				}
				if (TileMap[i][j] == '2')
				{
					s_map.setTextureRect(IntRect(64, 0, 64, 64));
				}
				if (TileMap[i][j] == '3')
				{
					s_map.setTextureRect(IntRect(128, 0, 64, 64));
				}
				if (TileMap[i][j] == '4')
				{
					s_map.setTextureRect(IntRect(0, 64, 64, 64));
				}
				if (TileMap[i][j] == ' ')
				{
					s_map.setTextureRect(IntRect(64, 64, 64, 64));
				}
				if (TileMap[i][j] == '5')
				{
					s_map.setTextureRect(IntRect(128, 64, 64, 64));
				}
				if (TileMap[i][j] == '6')
				{
					s_map.setTextureRect(IntRect(0, 128, 64, 64));
				}
				if (TileMap[i][j] == '6')
				{
					s_map.setTextureRect(IntRect(64, 128, 64, 64));
				}
				if (TileMap[i][j] == '6')
				{
					s_map.setTextureRect(IntRect(128, 128, 64, 64));
				}

				s_map.setPosition(j * 64, i * 64);

				window.draw(s_map);
			}
		}
		window.draw(p.sprite);
		window.display();
	}

	return 0;
}