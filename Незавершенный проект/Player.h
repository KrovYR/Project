#pragma once

#include <SFML/Graphics.hpp>

class Player
{
public:
	float dx, dy, posX;
	int life;
	sf::FloatRect rect;
	bool invis, onGround, tileActive, crouch;
	sf::RectangleShape rectangle;

	Player();

	void update(float time);

	//Взаимодействие с картой
	void collision(int dir);
};

/*
#pragma once

#include <SFML/Graphics.hpp>

class Player
{
public:
					Player();
	void			update(float time);

	sf::RectangleShape rectangle;
	float posX, posY;
	float speedX, speedY;
	bool moveLeft, moveRight, Jump, Run;
	bool onGround;
};
*/