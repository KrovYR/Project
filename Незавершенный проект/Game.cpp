/*
#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace sf;

Game::Game()
	: window(VideoMode(1366, 768), "Game")
{
	TimePerFrame = seconds(1.f / 60.f);
}

void Game::run()
{
	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;
	while (window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}

void Game::processEvents()
{
	Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case Event::Closed:
			window.close();
			break;
		}
		if (event.type == Event::Closed)
			window.close();
	}
}

void Game::update(Time deltaTime)
{
	Vector2f movement(0.f, 0.f);

	if (player.posY < 500)
		player.onGround = false;
	else {
		player.onGround = true;
		player.speedY = 0;
	}
		

	if (player.moveLeft)
		player.speedX = -50.f;
	if (player.moveRight)
		player.speedX = 50.f;
	if (player.Jump)
		player.speedY = 70.f;
	if (player.Run)
		player.speedX *= 2;

	player.update(deltaTime.asSeconds());
}

void Game::render()
{
	window.clear(Color::White);
	window.draw(player.rectangle);
	window.display();
}

void Game::handlePlayerInput(Keyboard::Key key, bool isPresed)
{
	if (key == Keyboard::A)
		player.moveLeft = isPresed;
	else if (key == Keyboard::D)
		player.moveRight = isPresed;
	else if (key == Keyboard::Space)
		player.Jump = isPresed;
	else if (key == Keyboard::LShift)
		player.Run = isPresed;
}
*/