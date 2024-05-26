//Name: Leo Bolaks
//Login: C00299368

#pragma once

#include "SFML/Graphics.hpp"
#include "Globals.h"

#include <iostream>

class Gameover
{

	sf::Texture m_screenTexture; // texture for game over screen
	sf::Sprite m_screenSprite; // sprite for game over screen
	sf::RectangleShape m_restartButton; // rectangle shape for restart button

public:
	Gameover();

	void loadScreen();

	/// <summary>
	/// returns sprite and rectangle shape
	/// </summary>
	/// <returns></returns>
	sf::Sprite getGameOverScreen();
	sf::RectangleShape getRestartButton();

	

};