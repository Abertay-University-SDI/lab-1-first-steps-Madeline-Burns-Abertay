#include "Level.h"

Level::Level(sf::RenderWindow& hwnd, Input& in) :
	BaseLevel(hwnd, in)
{
	// initialise game objects
	m_lastPressedDir = INIT;
	m_player.setRadius(10.0);
	m_player.setFillColor(sf::Color(0, 255, 0));
	m_player.setPosition({ 300, 300 });
	m_playerSpeed = 200;

	m_food.setRadius(6.0);
	m_food.setFillColor(sf::Color(255, 0, 0));
	spawnFood();

	m_isGameOver = false;
	m_foodCount = 0;
	m_time = 0;
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
	if (m_isGameOver) {
		return;
	}
	m_time += dt;
	sf::Vector2f playerPos = m_player.getPosition();
	float playerRadius = m_player.getRadius();
	sf::Vector2f foodPos = m_food.getPosition();
	float foodRadius = m_food.getRadius();
	if (
		playerPos.x <= 0 || playerPos.x >= m_window.getSize().x - 2 * playerRadius || 
		playerPos.y <= 0 || playerPos.y >= m_window.getSize().y - 2 * playerRadius
		) // ughhhhh it doesn't even fit on one line anymore what am i doing
	{
		std::cout << "oof. game over" << std::endl;
		std::cout << "pieces of food collected: " << m_foodCount << std::endl;
		std::cout << "time survived: " << m_time << std::endl;
		m_isGameOver = true;
	}
	switch (m_lastPressedDir)
	{
	case UP:
		playerPos.y -= m_playerSpeed * dt;
		break;
	case DOWN:
		playerPos.y += m_playerSpeed * dt;
		break;
	case LEFT:
		playerPos.x -= m_playerSpeed * dt;
		break;
	case RIGHT:
		playerPos.x += m_playerSpeed * dt;
		break;
	}
	m_player.setPosition(playerPos);
	if (dist(playerPos, foodPos) <= playerRadius + foodRadius)
	{
		m_playerSpeed += m_playerSpeed / 10;
		m_foodCount++;
		std::cout << "fruit " << m_foodCount << " get. new speed: " << m_playerSpeed << std::endl;
		spawnFood();
	}
}

float Level::dist(sf::Vector2f a, sf::Vector2f b)
{
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

// Render level
void Level::render()
{
	beginDraw();
	m_window.draw(m_player);
	m_window.draw(m_food);
	endDraw();
}

void Level::spawnFood()
{
	m_food.setPosition({
		static_cast<float>(rand() % m_window.getSize().x),
		static_cast<float>(rand() % m_window.getSize().y)
	});
}