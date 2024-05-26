//Name: Leo Bolaks
//Login: C00299368
#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Globals.h"

#include <iostream>
#include <cstdlib>  // include support for randomizing
#include <ctime>   // supports ctime function

class Enemies
{
	sf::Texture m_tankTexture; // tank texture
	sf::Sprite m_tankSprite; // tank sprite
	sf::Texture m_turretTexture; // turret texture
	sf::Sprite m_turretSprite; // turret sprite
	sf::Texture m_bulletTexture; // bullet texture
	sf::Sprite m_bulletSprite; // bullet sprite
	sf::Texture m_healthDropTexture; // texture for health drop
	sf::Sprite m_healthDropSprite; // sprite for health drop
	sf::Texture m_superHealthTexture; // texture for super health drop
	sf::Sprite m_superHealthSprite; // sprite for super health drop
	sf::Texture m_explosionTexture; // texture for explosion
	sf::Sprite m_explosionSprite; // sprite for explosion

	sf::SoundBuffer m_fireBuffer; // buffer for firing
	sf::Sound m_firingSound; // firing sound
	sf::SoundBuffer m_explosionBuffer; // buffer for explosion
	sf::Sound m_explosionSound; // sound for explosion

	sf::CircleShape m_stopDistance; // distance from tank to player tank to stop at

	sf::Vector2f m_location; // location
	sf::Vector2f m_tankVelocity; // velocity

	sf::Vector2f m_bulletVelocity{ 0,0 }; // velocity of the bullet
	sf::Vector2f m_bulletLocation{ 0,0 }; // location of the bullet

	const float RESPAWN_COUNTDOWN_DURATION = 300.0f; // reload duration of 5 seconds
	float m_countdown = 0.0f; // countdown for reload

	int m_currentFrame = 0; // frame number
	float m_frameCounter = 0.0f; // frame counter
	float m_frameIncrement = 0.3f; // frame increment

	const float RELOAD_COUNTDOWN_DURATION = 300.0f;
	float m_reloadCountdown = 0.0f;
	float m_speed = 1.3f; // speed

	int m_explosionFrame = 0; // current frame
	float m_explosionIncrement = 0.6f; // frame increment
	float m_explosionFrameTimer = 0.0f; // frame timer
	
	bool m_healthDropActive = false;
	bool m_alive = true;
	bool m_fireSound = false;
	bool m_exploding = false;
	bool m_explodingSound = false;
	bool m_stopMove = false;
	bool m_killed = false;
	bool m_bulletActive = false;

public:

	Enemies(); // constructor

	void loadTank(); // load sprites
	void loadAudio(); // load audio

	void update(sf::Vector2f t_playerLocation); // update
	/// <summary>
	/// returns sprites and shapes so they can be drawn in the game class
	/// </summary>
	/// <returns></returns>
	sf::Sprite getTank(); 
	sf::Sprite getTurret(); 
	sf::Sprite getBullet();
	sf::CircleShape getStopDistance();
	sf::Sprite getHealthDrop();
	sf::Sprite getSuperHealthDrop();
	sf::Sprite getExplosion();

	/// <summary>
	/// check functions check current state of boolion and set functions set them to either true or false
	/// </summary>
	/// <returns></returns>
	bool checkAlive();
	bool checkExploding();
	void setAliveFalse();
	void setAlivetrue();
	void setExplodingTrue();
	void setStopMoveTrue();
	void setStopMoveFalse();
	void setKilledTrue();
	void setBulletActiveFalse();

	void setBulletPosition();
	void spawn(); // random spawn generator
	void move(sf::Vector2f t_playerLocation); // move, players location is passed in from game class
	void turretRotate(sf::Vector2f t_playerLocation); // rotate turret, player location is passed from game class
	void respawn(); // respawn

	bool checkHealthDropActive(); // checks if health drop is active

	void reload(); // reload

	void shooting(sf::Vector2f t_playerLocation); // shooting, players location is passed from game class

	void healthDropCheck(); // random generator for health drop spawns
	void healthDropReset(); // resets position of health drops

	void animations(); // health drop animations
	void explosionAnimation(); // explosion animation

};