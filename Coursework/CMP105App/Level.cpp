#include "Level.h"

Level::Level(sf::RenderWindow& hwnd, Input& in) :
	BaseLevel(hwnd, in)
{
	// initialise game objects
	m_player.setRadius(10.0);
	m_player.setFillColor(sf::Color(0, 255, 0));
	m_player.setPosition({ 300, 300 });
}

// handle user input
void Level::handleInput(float dt)
{
	if (m_input.isKeyDown(sf::Keyboard::Scancode::W))
	{
		m_lastPressedDir = UP;
	}
	if (m_input.isKeyDown(sf::Keyboard::Scancode::S))
	{
		m_lastPressedDir = DOWN;
	}
	if (m_input.isKeyDown(sf::Keyboard::Scancode::A))
	{
		m_lastPressedDir = LEFT;
	}
	if (m_input.isKeyDown(sf::Keyboard::Scancode::D))
	{
		m_lastPressedDir = RIGHT;
	}
}

// Update game objects
void Level::update(float dt)
{
	sf::Vector2f pos = m_player.getPosition();
	float radius = m_player.getRadius();
	if (pos.x <= 0 || pos.y <= radius || pos.x >= m_window.getSize().x - 2 * radius || pos.y >= m_window.getSize().y + 2 * radius) // this is just getting uglier by the second
	{
		pos = {m_window.getSize().x / 2.0f, m_window.getSize().y / 2.0f};
	}
	int speed = 200;
	switch (m_lastPressedDir)
	{
	case UP:
		pos.y -= speed * dt;
		break;
	case DOWN:
		pos.y += speed * dt;
		break;
	case LEFT:
		pos.x -= speed * dt;
		break;
	case RIGHT:
		pos.x += speed * dt;
		break;
	}
	m_player.setPosition(pos);
}

// Render level
void Level::render()
{
	beginDraw();
	m_window.draw(m_player);
	endDraw();
}

