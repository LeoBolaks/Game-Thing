//Name: Leo Bolaks
//Login: C00299368

#include "Gameover.h"

Gameover::Gameover()
{
	loadScreen();
}

void Gameover::loadScreen()
{
	if (!m_screenTexture.loadFromFile("ASSETS\\IMAGES\\Game_Over.png"))
	{
		std::cout << "Error loading game over screen" << std::endl;
	}
	m_screenSprite.setTexture(m_screenTexture);

	m_restartButton.setSize(sf::Vector2f(400, 144));
	m_restartButton.setFillColor(sf::Color::Transparent);
	m_restartButton.setOutlineColor(sf::Color::Magenta);
	m_restartButton.setOutlineThickness(2.0f);
	m_restartButton.setPosition(550, 560);
}

sf::Sprite Gameover::getGameOverScreen()
{
	return m_screenSprite;
}

sf::RectangleShape Gameover::getRestartButton()
{
	return m_restartButton;
}

