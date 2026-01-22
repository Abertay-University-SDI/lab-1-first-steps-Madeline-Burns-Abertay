#pragma once

#include "Framework/BaseLevel.h"

class Level : BaseLevel{
public:
	Level(sf::RenderWindow& window, Input& input);
	~Level() override = default;

	void handleInput(float dt) override;
	void update(float dt);
	void render();
	void spawnFood();
	float dist(sf::Vector2f, sf::Vector2f);

private:
	// Default functions for rendering to the screen.

	// Default variables for level class.
	sf::CircleShape m_player;
	enum direction
	{
		INIT,
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
	direction m_lastPressedDir;
	int m_playerSpeed;

	sf::CircleShape m_food;

	bool m_isGameOver;
	int m_foodCount;
	float m_time;
};