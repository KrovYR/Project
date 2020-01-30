/*
#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class Game
{
public:
					Game();
	void			run();

private:
	void			processEvents();
	void			update(sf::Time deltaTime);
	void			render();
	void			handlePlayerInput(sf::Keyboard::Key key, bool isPresed);

private:
	sf::RenderWindow window;
	sf::Time TimePerFrame;
	Player player;
};
*/