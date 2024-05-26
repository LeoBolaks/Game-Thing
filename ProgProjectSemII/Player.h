//Name: Leo Bolaks
//Login: C00299368

// Player class declaration
#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Globals.h"

#include <iostream>

/// <summary>
/// enum class for current state of turret
/// </summary>
enum class TurretState
{
	Ready,
	Reloading
};
class Player
{
	// private data members
	sf::Texture m_tankTexture; // tank texture
	sf::Sprite m_tankSprite; // tank sprite

	sf::RectangleShape m_tankHitbox; // tank hitbox
	sf::CircleShape m_gunIndicator; // status of the gun

	sf::Texture m_turretTexture; // turret texture
	sf::Sprite m_turretSprite; // turret sprite

	sf::Texture m_bulletTexture; // bullet texture
	sf::Sprite m_bulletSprite; // bullet sprite

	sf::Texture m_criticalHealthText; // critical health texture
	sf::Sprite m_criticalHealthSprite; // critical health sprite

	sf::Texture m_explosionTexture; // texture for explosion
	sf::Sprite m_explosionSprite; // sprite for explosion

	sf::SoundBuffer m_alarmBuffer; // buffer for alarm sound
	sf::Sound m_alarmSound; // sound for alarm
	sf::SoundBuffer m_fireBuffer; // buffer for firing sound
	sf::Sound m_fireSound; // firing sound
	sf::SoundBuffer m_explosionBuffer; // buffer for explosion
	sf::Sound m_explosionSound; // sound for explosion

	int m_direction; // direction of tank

	float m_speed = 2.0f; // speed of tank
	float m_health = 100.0f; // health of tank
	sf::RectangleShape m_healthBar; // healthbar of the tank

	float m_lightDamage = 5.5f; // light damage to tank
	float m_heavyDamage = 25.0f; // heavy damage to tank
	float m_heal = 30.0f; // healing 

	sf::Vector2f m_location = { 750.0f, 1100.0f }; // initial tank location
	int m_currentFrame = 0; // frame number
	float m_frameCounter = 0.0f; // frame counter
	float m_frameIncrement = 0.5f; // frame increment
	sf::Vector2f m_turretPos; // position of the turret

	sf::Vector2f m_bulletVelocity; // bullet velocity
	sf::Vector2f m_bulletLocation; // location of bullet

	const float RELOAD_COUNTDOWN_DURATION = 240.0f; // reload duration of 4 seconds
	float m_countdown = 0.0f; // countdown for reload

	int m_explosionFrame = 0; // current frame
	float m_explosionIncrement = 0.6f; // frame increment
	float m_explosionFrameTimer = 0.0f; // frame timer

	bool m_firing = false;
	bool m_bulletActive = false;
	bool m_piercingRound = false;
	bool m_alive = true;
	bool m_criticalHealth = false;
	bool m_alarm = false;
	bool m_firingSound = false;
	bool m_explodingSound = false;
	bool m_exploding = false;


public:
	
	Player(); // constructor

	void loadTank(); // load sprites
	void loadAudio(); // load audio

	void update(sf::Vector2f t_mousePos); // update with mouse position passed in from game class

	void healthCheck(); // constant health check

	/// <summary>
	/// return sprites, vectors, and shapes so they can be drawn or used in game class
	/// </summary>
	sf::Sprite getTank();
	sf::Sprite getTurret();
	sf::Sprite getBullet();
	sf::Sprite getCriticalHealth();
	sf::Vector2f getLocation();
	sf::RectangleShape getHitbox();
	sf::RectangleShape getHealthBar();
	sf::Sprite getExplosion();
	sf::CircleShape getGunIndicator();

	/// <summary>
	/// check functions check the current state of the boolion and set functions set the boolions to either true or false
	/// </summary>
	bool checkAlive();
	bool checkPiercingRound();
	bool checkFiring();
	bool checkBullet();
	bool checkCriticalHealth();
	bool checkExploding();
	void setFiringTrue();
	void setBulletTrue();
	void setBulletFalse();
	void setPiercingRoundTrue();
	void healthReset();
	void positionReset();
	void setAliveTrue();
	void setExplodingFalse();

	/// <summary>
	/// move functions
	/// </summary>
	void moveUp();
	void moveUpL();
	void moveUpR();

	void moveDown();
	void moveDownL();
	void moveDownR();

	void moveLeft();
	void moveRight();

	/// <summary>
	/// tank track animations
	/// </summary>
	void animations();

	void turretRotation(sf::Vector2f t_mousePos); // rotates the turret, mouse position is passed in from game class
	void shooting(sf::Vector2f t_mousePos); // shooting, mouse position is passed in from game class

	void collisions(); // deals with player collisions with light enemy tanks

	void lightDamage(); // takes away a small amount of health
	void heavyDamage(); // takes away a large amount of health
	void heal(); // slightly heals player
	void superHeal(); // heals player to full health

	void changeTurretState(); // changes the state of the turret
	void reload(); // reload for gun

	void explosionAnimation(); // animation for explosion

	void updateGunIndicator();

	bool m_enemyContact = false; // public boolion for contact with enemy
	
	TurretState m_turretState = TurretState::Ready; // turret state by default set to ready

};