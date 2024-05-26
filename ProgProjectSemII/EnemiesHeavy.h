//Name: Leo Bolaks
//Login: C00299368

#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Globals.h"

#include <iostream>
#include <cstdlib>  // include support for randomizing
#include <ctime>   // supports ctime function

class EnemiesHeavy
{
	sf::Texture m_tankTexture; // texture for tank
	sf::Sprite m_tankSprite; // sprite for tank
	sf::Texture m_bulletTexture; // texture for bullet
	sf::Sprite m_bulletSprite; // sprite for bullet
	sf::Texture m_healthTexture; // texture for health
	sf::Sprite m_healthSprite; // sprite for health
	sf::Texture m_piercerRoundTexture; // texture for piercer round
	sf::Sprite m_piercerRoundSprite; // sprite for piercer round
	sf::Texture m_explosionTexture; // texture for explosion
	sf::Sprite m_explosionSprite; // sprite for explosion

	sf::SoundBuffer m_firingBuffer; // buffer for firing
	sf::Sound m_firingSound; // sound for firing
	sf::SoundBuffer m_explosionBuffer; // buffer for explosion
	sf::Sound m_explosionSound; // sound for explosion

	sf::Vector2f m_location;
	float m_speed = 1.5f;

	sf::Vector2f m_piercerLocation;
	float m_piercerSpeed = 5.0f;
	float m_piercerDecrement = 0.01f;

	const float RELOAD_COUNTDOWN_DURATION = 480.0f; // set to 480 for a 8 second timer
	float m_reloadCountdown = 0.0f;
	float m_respawnCountdown = 0.0f;
	const float RESPAWN_COUNTDOWN_DURATION = 600.0f; // set to 600 for a 10 second timer

	sf::Vector2f m_bulletLocation;

	int m_currentFrame = 0; // frame number
	float m_frameCounter = 0.0f; // frame counter
	float m_frameIncrement = 0.3f; // frame increment

	int m_explosionFrame = 0; // current frame
	float m_explosionIncrement = 0.6f; // frame increment
	float m_explosionFrameTimer = 0.0f; // frame timer

	bool m_activeBullet = false; // if the bullet is active
	bool m_damaged = false; // if the tank is damaged
	bool m_aliveH = true; // if the tank is alive
	bool m_piercerActive = false;
	bool m_fireSound = false;
	bool m_exploding = false;
	bool m_explodingSound = false;

public:
	EnemiesHeavy();

	void loadTank();
	void loadAudio();

	sf::Sprite getTank();
	sf::Sprite getBullet();
	sf::Sprite getHealthbar();
	sf::Sprite getPiercerRound();
	sf::Sprite getExplosion();

	bool checkBullet();
	bool checkDamage();
	bool checkAlive();
	bool checkExploding();

	void setAliveFalse();
	void setDamageTrue();
	void setBulletFalse();
	void setDamageFalse();
	void setExplodingTrue();

	void update();

	void reload();
	void shooting();

	void setPiercer();
	void piercerReset();
	void piercerMove();

	void respawn();

	void animationsPowerUp();
	void explosionAnimation();

	void setPosition(int xPos, int yPos);
	void move();

	
};