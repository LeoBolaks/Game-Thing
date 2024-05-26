//Name: Leo Bolaks
//Login: C00299368

// Game class declaration
#pragma once

#include "SFML/Graphics.hpp" 
#include "SFML/Audio.hpp"
#include <iostream>
#include <cstdlib>  // include support for randomizing
#include <ctime>   // supports ctime function

#include "Globals.h"   // include Global header file
#include "Player.h"   // include Player header file
#include "Enemies.h" // include Enemies header file
#include "EnemiesHeavy.h" // include Enemies heavy header file
#include "Gameover.h" // include gameover screen header file

enum class GameState
{
	Start,
	Game
};
class Game
{
	// private data members
	Player player;
	Enemies enemies[MAX_ENEMIES];
	EnemiesHeavy enemiesH[2];
	Gameover gameOver;
	// put your game objects here eg player object and 
	// array of enemy objects etc.
	sf::RenderWindow m_window;

public:
	sf::Font m_scoreFont;  // font for writing text
	sf::Text m_scoreText;  // text to write on the screen
	sf::Font m_killFont; // font for kills
	sf::Text m_killText; // text for kills
	sf::Font m_gunFont; // font for gun text
	sf::Text m_gunText; // text for gun

	sf::Vector2f m_mousePos; // position of mouse on screen
	sf::Texture m_mapTexture; // texture for map
	sf::Sprite m_mapSprite; // sprite for map
	sf::Texture m_platformTexture; // texture for platform
	sf::Sprite m_platformSprite; // sprite for platform
	sf::Texture m_startScreenTexture; // texture for start screen
	sf::Sprite m_startScreenSprite; // sprite for start screen
	sf::Texture m_healthBarTexture; // texture for healthbar
	sf::Sprite m_healthBarSprite; // sprite for healthbar
	sf::Texture m_healingTexture; // texture for healing
	sf::Sprite m_healingSprite; // sprite for healing
	sf::Texture m_superHealTexture; // texture for super healing
	sf::Sprite m_superHealSprite; // sprite for super healing

	sf::SoundBuffer m_menuBuffer; // buffer for menu music
	sf::Sound m_menuSound; // sound for menu music
	sf::SoundBuffer m_gameBuffer; // buffer for game music
	sf::Sound m_gameSound; // sound for game
	sf::SoundBuffer m_healthBuffer; // buffer for health sound
	sf::Sound m_healthSound; // health sound
	sf::SoundBuffer m_piercerBuffer; // buffer for piercer pickup
	sf::Sound m_piercerSound; // sound for piercer pickup

	GameState m_gameState = GameState::Start;

	int m_activeEnemies = 1; // currently active enemies
	int m_deadEnemies = 0; // number of dead enemies
	int m_totaldeadEnemies = 0; // total number of dead enemies
	int m_score = 0;

	int m_currentHealingFrame = 0; // frame number
	float m_healingframeCounter = 0.0f; // frame counter
	float m_healingframeIncrement = 0.3f; // frame increment

	int m_currentSHealingFrame = 0; // frame number
	float m_sHealingframeCounter = 0.0f; // frame counter
	float m_sHealingframeIncrement = 0.3f; // frame increment

	bool m_debugMode = false;
	bool m_gameMusic = false;
	bool m_healing = false;
	bool m_superHealing = false;

public:	  // declaration of member functions	
	Game(); // default constructor
	void loadContent(); // load sprites
	void loadAudio(); // load audio
	void run(); // run
	void processEvents(); // processing events such as key releases
	void update(); // update
	void draw(); /// draw

	void textUpdate(); // update for score and kill texts

	void gameReset(); // reset for game

	void setUpMap(); // set up for map

	void startControl(); // checks if enter has been pressed then starts game

	void playerMove(); // key input for player movement
	void playerShoot(); // left click input for player shooting

	void debugToggle(sf::Event t_event); // upon F1 key release it will toggle debug

	void heavySpawn(); // hardcode starting heavy positions

	void distanceCheck(); // check for distance between player and light tanks
	void playerBulletCollisions(); // player bullet collisions with everything else
	void playerCollisions(); // player collisions with drops and light tanks
	void mouseCollisions(sf::Event t_event); // mouse collision with restart button
	void enemyBulletCollisions(); // enemy bullet collisions with player
	void addEnemies(); // add to total number of light enemies

	void playGameMusic(); // plays game music
	void playHealthSound(); // plays health pick up sound
	void playPiercerSound(); // plays piercer round pick up sound

	void healingAnimation();
	void superHealingAnimation();

	void getMousePos(sf::Event t_event); // gets the current position of mouse
};
