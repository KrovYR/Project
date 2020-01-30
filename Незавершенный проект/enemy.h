#pragma once

#include <SFML/Graphics.hpp>

class Enemy
{
public:
	float dx, dy, posX;
	float speed;
	int rotation;
	sf::FloatRect rect;
	bool onGround;
	sf::RectangleShape rectangle;

	Enemy();

	void update(float time);

	//Взаимодействие с картой
	void Collision(int dir);
};