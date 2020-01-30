#include "Player.h"
#include "maps.h"

using namespace sf;

Player::Player()
{
	life = 5;
	rect = FloatRect(100, 100, 75, 100);
	posX = rect.left;
	dx = dy = 0.1;
	crouch = false;
	onGround = false;
	tileActive = true;
	invis = false;

	rectangle.setSize(Vector2f(rect.width, rect.height));
	rectangle.setFillColor(Color::Blue);
}

void Player::update(float time)
{
	rect.left += dx * time;
	collision(0);

	if (!onGround)
	{
		dy = dy + 0.0006 * time;
	}
	rect.top += dy * time;
	onGround = false;
	collision(1);

	rectangle.setPosition(rect.left, rect.top);

	dx = 0;
}

//Взаимодействие с картой
void Player::collision(int dir)
{
	for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
		for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
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
					tileActive = true;
				}
				if ((dy < 0) && (dir == 1))
				{
					rect.top = i * 32 + 32;
					dy = 0;
				}
			}

			if ((TileMap[i][j] == '1') && (tileActive))
			{
				if ((dy > 0) && (dir == 1))
				{
					rect.top = i * 32 - rect.height;
					dy = 0;
					onGround = true;
				}
			}

		}
}

/*
#include "Player.h"

using namespace sf;

Player::Player()
{
	rectangle.setSize(Vector2f(75.f, 100.f));
	rectangle.setPosition(Vector2f(100.f, 100.f));
	rectangle.setFillColor(Color::Black);

	posX = 100.f;
	posY = 100.f;

	speedX = 50.f;
	speedY = 70.f;

	moveLeft = false;
	moveRight = false;
	Jump = false;
	Run = false;

	onGround = false;
}

void Player::update(float time)
{
	posX += speedX * time;

	if (!onGround)
		speedY += 9.8 * time;
	
	posY += speedY * time;
}
*/