#include <iostream>
#include "enemy.h"
#include "maps.h"
#include "Player.h"

using namespace sf;

Enemy::Enemy()
{
	rect = FloatRect(250, 640, 65, 90);
	posX = rect.left;
	dx = 0;
	dy = 0.1;
	speed = -0.1;
	rotation = 1;
	onGround = false;	
}

void Enemy::update(float time)
{
	rect.left += dx * time;
	Collision(0);

	if (!onGround)
	{
		dy = dy + 0.0006 * time;
		dx = 0;
	}
	else
		dx = speed * rotation;
	rect.top += dy * time;
	onGround = false;
	Collision(1);

	rectangle.setSize(Vector2f(rect.width, rect.height));
	rectangle.setFillColor(Color::Cyan);
	rectangle.setPosition(rect.left, rect.top);
}

//Взаимодействие с картой
void Enemy::Collision(int dir)
{
	for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
		for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
		{

			if (TileMap[i][j] == '0')
			{
				if ((dx > 0) && (dir == 0))
				{
					rect.left = j * 32 - rect.width;
					dx = -0.1;
					rotation = -1;
				}
				if ((dx < 0) && (dir == 0))
				{
					rect.left = j * 32 + 32;
					dx = 0.1;
					rotation = -1;
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