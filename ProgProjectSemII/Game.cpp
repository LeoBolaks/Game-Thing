// Name: Leo Bolaks
// Login: C00299368
// Date: 20-03-2024
//---------------------------------------------------------------------------
// Project description: this games purpose is to have the player survive for
// as long as possible while trying to rack up a high score and a high kill 
// count, this game features functions which deal with rotations of turrets
// and tanks based on the positions of either the mouse or the player
// there are also sound accompanying the gameplay
// ---------------------------------------------------------------------------
// Known Bugs:
// ?

//////////////////////////////////////////////////////////// 
// include correct library file for release and debug versions
//////////////////////////////////////////////////////////// 

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib")




#include "Game.h"   // include Game header file

Game aGame;
int main()
{
	aGame.loadContent();
	aGame.loadAudio();
	aGame.run();

	return 0;
}

Game::Game() : m_window(sf::VideoMode(static_cast<int>(SCREEN_WIDTH), static_cast<int>(SCREEN_HEIGHT)), "Joint Project Game", sf::Style::Default)
// Default constructor
{
}

void Game::loadContent()
// Load the font file & setup the message string
{
	if (!m_scoreFont.loadFromFile("ASSETS/FONTS/digital.ttf"))
	{
		std::cout << "error with Score font file";
	}

	// set up the message string 
	m_scoreText.setFont(m_scoreFont);  // set the font for the text
	m_scoreText.setCharacterSize(55); // set the text size
	m_scoreText.setFillColor(sf::Color::White); // set the text colour
	m_scoreText.setOutlineColor(sf::Color::Black); // set text outline colour
	m_scoreText.setOutlineThickness(5); // set text outline thickness
	m_scoreText.setPosition(400, 1128);  // its position on the screen

	if (!m_killFont.loadFromFile("ASSETS/FONTS/digital.ttf"))
	{
		std::cout << "error with Kill font file";
	}

	// set up the message string 
	m_killText.setFont(m_killFont);  // set the font for the text
	m_killText.setCharacterSize(55); // set the text size
	m_killText.setFillColor(sf::Color::White); // set the text colour
	m_killText.setOutlineColor(sf::Color::Black); // set text outline colour
	m_killText.setOutlineThickness(5); // set text outline thickness
	m_killText.setPosition(1000, 1128);  // its position on the screen

	if (!m_gunFont.loadFromFile("ASSETS/FONTS/digital.ttf"))
	{
		std::cout << "Error loading gun font file" << std::endl;
	}
	m_gunText.setFont(m_gunFont);
	m_gunText.setCharacterSize(55);
	m_gunText.setFillColor(sf::Color::White);
	m_gunText.setOutlineColor(sf::Color::Black);
	m_gunText.setOutlineThickness(5);
	m_gunText.setString("Gun Status:");
	m_gunText.setPosition(1150, 1128);

	if (!m_startScreenTexture.loadFromFile("ASSETS\\IMAGES\\Start.png"))
	{
		std::cout << "Error loading start screen" << std::endl;
	}
	m_startScreenSprite.setTexture(m_startScreenTexture);

	if (!m_healthBarTexture.loadFromFile("ASSETS\\IMAGES\\HealthBar.png"))
	{
		std::cout << "Error loading healthbar surrounding" << std::endl;
	}
	m_healthBarSprite.setTexture(m_healthBarTexture);
	m_healthBarSprite.setPosition(5,1148);

	if (!m_healingTexture.loadFromFile("ASSETS\\IMAGES\\Healing.png"))
	{
		std::cout << "Error loading healing animation" << std::endl;
	}
	m_healingSprite.setTexture(m_healingTexture);
	m_healingSprite.setTextureRect(sf::IntRect(0, 0, 1500, 1200));

	if (!m_superHealTexture.loadFromFile("ASSETS\\IMAGES\\Super_Healing.png"))
	{
		std::cout << "Error loading healing animation" << std::endl;
	}
	m_superHealSprite.setTexture(m_superHealTexture);
	m_superHealSprite.setTextureRect(sf::IntRect(0, 0, 1500, 1200));
}


void Game::run()
// This function contains the main game loop which controls the game. 
{
	heavySpawn();
	setUpMap();
	srand((int)time(nullptr)); // set the seed once

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);

	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// the clock object keeps the time.
	sf::Clock clock;

	clock.restart();

	while (m_window.isOpen())
	{
		// check if the close window button is clicked on
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			
			if (event.type == sf::Event::Closed)
				m_window.close();
		}

		//get the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();

		//update every 60th of a second
		//only when the time since last update is greater than 1/60 update the world.
		if (timeSinceLastUpdate > timePerFrame)
		{
			update();
			draw();

			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
		processEvents();
	}  // end while loop

}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::MouseMoved == newEvent.type) // user moved the mouse
		{
			getMousePos(newEvent);
		}
		if (!player.checkAlive())
		{
			if (sf::Event::MouseButtonReleased == newEvent.type)
			{
				mouseCollisions(newEvent);
			}
		}
		if (newEvent.type == sf::Event::KeyReleased && newEvent.key.code == sf::Keyboard::F1)
		{
			debugToggle(newEvent);
		}
	}
}

void Game::update()
{
	// update any game variables here
	if (m_gameState == GameState::Game) // if the game state is set to game, it will begin running everything to do with the actual gameplay aspect
	{
		if (player.checkAlive()) // if player is alive it will update the keyboard inputs for movement and shooting and also the check for collisions
		{
			playerMove();
			playerCollisions();
			playerShoot();
		}
		else
		{
			m_gameSound.stop(); // stops playing in game music upon players death
		}
		for (int i = 0; i < m_activeEnemies; i++)
		{
			enemies[i].update(player.getLocation()); // updates the light enemy class update and passes players location into it
		}
		for (int i = 0; i < 2; i++)
		{
			enemiesH[i].update(); // updates the heavy enemy class update
		}

		if (m_healing)
		{
			healingAnimation();
		}
		if (m_superHealing)
		{
			superHealingAnimation();
		}

		distanceCheck(); // check for distance
		addEnemies(); // addition of enemies
		player.update(m_mousePos); // updates player update and passes in the mouse position
		playerBulletCollisions(); // collisions between the player bullet and enemies
		enemyBulletCollisions(); // collisions between enemy bullet and player
		textUpdate(); // updates kill and score texts
		m_menuSound.stop(); // stops menu music
		playGameMusic(); // plays game music
	}
	else if (m_gameState == GameState::Start)
	{
		startControl(); // only allows the user to click enter when the game is started
	}

}

void Game::draw()
// This function draws the game world
{
	// Clear the screen and draw your game sprites
	m_window.clear();
	if (m_gameState == GameState::Game) // will draw everything to do with gameplay 
	{
		m_window.draw(m_mapSprite);
		
		for (int i = 0; i < m_activeEnemies; i++) // will draw everything to do with the light enemy tanks
		{
			m_window.draw(enemies[i].getHealthDrop()); // draws health drop
			m_window.draw(enemies[i].getSuperHealthDrop()); // draws super health drop
			if (m_debugMode) // will draw stopping distance circle if in debug mode
			{
				m_window.draw(enemies[i].getStopDistance());
			}
			m_window.draw(enemies[i].getTank()); // draws enemy tank
			m_window.draw(enemies[i].getBullet()); // draws enemy bullet
			m_window.draw(enemies[i].getTurret()); // draws enemy turret
		}
		for (int i = 0; i < m_activeEnemies; i++) // will separately draw the explosion above enemy light tanks
		{
			if (enemies[i].checkExploding())
			{
				m_window.draw(enemies[i].getExplosion()); // draws explosion if tank is dead
			}
		}
		m_window.draw(m_platformSprite);
		for (int i = 0; i < 2; i++) // draws everything to do with heavy tanks
		{
			m_window.draw(enemiesH[i].getPiercerRound()); // drops piercer round
			m_window.draw(enemiesH[i].getBullet()); // draws heavy tank bullet
			m_window.draw(enemiesH[i].getTank()); // draws heavy tank
			if (enemiesH[i].checkDamage()) // will draw healthbar if heavy tank is damaged
			{
				m_window.draw(enemiesH[i].getHealthbar()); // if heavy is damaged, will draw healthbar
			}
		}
		for (int i = 0; i < 2; i++)
		{
			if (enemiesH[i].checkExploding())
			{
				m_window.draw(enemiesH[i].getExplosion()); // will draw explosion animation if heavy enemy is dead
			}
		}

		m_window.draw(player.getTank()); // draws player tank
		if (player.checkAlive()) // will draw the turret and bullet if player is alive
		{
			m_window.draw(player.getBullet());
			m_window.draw(player.getTurret());
		}
		if (player.checkExploding())
		{
			m_window.draw(player.getExplosion()); // draws explosion if player is dead
		}
		if (m_debugMode)
		{
			m_window.draw(player.getHitbox()); // will draw hitbox of player if in debug mode
		}
		if (player.checkCriticalHealth()) // draws red outline around screen if health is critical
		{
			m_window.draw(player.getCriticalHealth());
		}
		if (m_healing) // if player heals will draw green healing outline
		{
			m_window.draw(m_healingSprite);
		}
		if (m_superHealing) // if player super heals will draw blue super heal outline
		{
			m_window.draw(m_superHealSprite);
		}
		m_window.draw(m_healthBarSprite); // draws healthbar sprite
		m_window.draw(player.getHealthBar()); // draws player healthbar
		m_window.draw(m_gunText); // draws gun text
		m_window.draw(player.getGunIndicator()); // draws gun status indicator
		if (!player.checkAlive())
		{
			m_window.draw(gameOver.getGameOverScreen()); // draws game over screen if player is dead
			if (m_debugMode)
			{
				m_window.draw(gameOver.getRestartButton()); // draws restart button outline if debug is on
			}
		}
		m_window.draw(m_scoreText);  // draws score text
		m_window.draw(m_killText); // draws kill text
	}
	else if (m_gameState == GameState::Start)
	{
		m_window.draw(m_startScreenSprite); // draws starting screen if state of game is start
	}

	m_window.display();
}

/// <summary>
/// fully restarts the game from the beginning
/// </summary>
void Game::gameReset()
{
	m_activeEnemies = 1;
	m_deadEnemies = 0;
	for (int i = 0; i < MAX_ENEMIES; i++) // resets light enemies
	{
		enemies[i].setAlivetrue();
		enemies[i].spawn();
		enemies[i].healthDropReset();
	}
	for (int i = 0; i < 2; i++) // resets heavy enemies
	{
		enemiesH[i].piercerReset();
		enemiesH[i].setDamageFalse();
	}
	heavySpawn(); // sets the heavy tank position
	player.healthReset(); // resets player health
	player.positionReset(); // resets player position
	player.setAliveTrue(); // sets alive to true
	player.setExplodingFalse(); // sets exploding to false
	m_gameSound.play(); // plays game music
	// resets game parameters
	m_score = 0;
	m_totaldeadEnemies = 0;
	m_deadEnemies = 0;

}

/// <summary>
/// update for kill and score text
/// </summary>
void Game::textUpdate()
{
	std::string score;
	score = std::to_string(m_score);
	m_scoreText.setString("SCORE: " + score);
	if (player.checkAlive()) // will resize and reposition text for game over screen after death
	{
		m_scoreText.setPosition(420, 1128);
		m_scoreText.setCharacterSize(55);
	}
	else if (!player.checkAlive())
	{
		m_scoreText.setPosition(545, 722);
		m_scoreText.setCharacterSize(85);
	}

	std::string kills;
	kills = std::to_string(m_totaldeadEnemies);
	m_killText.setString("KILLS: " + kills);
	if (player.checkAlive()) // will resize and reposition text for game over screen after death
	{
		m_killText.setPosition(750, 1128);
		m_killText.setCharacterSize(55);
	}
	else if (!player.checkAlive())
	{
		m_killText.setPosition(545, 820);
		m_killText.setCharacterSize(85);
	}
}
/// <summary>
/// set up for map
/// </summary>
void Game::setUpMap()
{
	if (!m_mapTexture.loadFromFile("ASSETS\\IMAGES\\Map.png"))
	{
		std::cout << "Error loading map" << std::endl;
	}
	m_mapSprite.setTexture(m_mapTexture);

	if (!m_platformTexture.loadFromFile("ASSETS\\IMAGES\\Platform.png"))
	{
		std::cout << "Error loading platform" << std::endl;
	}
	m_platformSprite.setTexture(m_platformTexture);
}

/// <summary>
/// allows user to start game
/// </summary>
void Game::startControl()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		m_gameState = GameState::Game;
	}
}

/// <summary>
/// this function deals with any keyboard imputs for player movement
/// </summary>
void Game::playerMove()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		player.moveUp();
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		player.moveLeft();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		player.moveDown();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player.moveRight();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		player.moveDownL();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player.moveDownR();
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		player.moveUpL();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player.moveUpR();
	}

}

/// <summary>
/// mouse input for player shooting
/// </summary>
void Game::playerShoot()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && player.m_turretState == TurretState::Ready)
	{
		player.setFiringTrue();
		player.setBulletTrue();
	}
}

/// <summary>
/// loads all audio
/// </summary>
void Game::loadAudio()
{
	if (!m_menuBuffer.loadFromFile("ASSETS\\SOUNDS\\Menu.wav"))
	{
		std::cout << "Error loading menu music" << std::endl;
	}
	m_menuSound.setBuffer(m_menuBuffer);
	m_menuSound.setLoop(true);
	m_menuSound.play();

	if (!m_gameBuffer.loadFromFile("ASSETS\\SOUNDS\\Game.wav"))
	{
		std::cout << "Error loading game music" << std::endl;
	}
	m_gameSound.setBuffer(m_gameBuffer);
	m_gameSound.setLoop(true);

	if (!m_healthBuffer.loadFromFile("ASSETS\\SOUNDS\\Health.wav"))
	{
		std::cout << "Error loading healthkit sound" << std::endl;
	}
	m_healthSound.setBuffer(m_healthBuffer);
	m_healthSound.setVolume(120);

	if (!m_piercerBuffer.loadFromFile("ASSETS\\SOUNDS\\Piercer.wav"))
	{
		std::cout << "Error loading piercer pickup sound" << std::endl;
	}
	m_piercerSound.setBuffer(m_piercerBuffer);


}

/// <summary>
/// hardcoded heavy spawn
/// </summary>
void Game::heavySpawn()
{
	enemiesH[0].setPosition(0, 90);
	enemiesH[1].setPosition(-600, 90);
}

/// <summary>
/// checks distance if player is intersecting with distance circle of light enemy
/// </summary>
void Game::distanceCheck()
{
	for (int i = 0; i < m_activeEnemies; i++)
	{
		if (enemies[i].getStopDistance().getGlobalBounds().intersects(player.getTank().getGlobalBounds()))
		{
			enemies[i].setStopMoveTrue();
		}
		else
		{
			enemies[i].setStopMoveFalse();
		}
	}

}

/// <summary>
/// player bullet collisions with enemies
/// </summary>
void Game::playerBulletCollisions()
{
	for (int i = 0; i < m_activeEnemies; i++) 
	{
		if (player.getBullet().getGlobalBounds().intersects(enemies[i].getTank().getGlobalBounds()) && player.checkBullet()) // if collides with light enemy
		{
			if (enemies[i].checkAlive()) // if light enemy is alive
			{
				if (!player.checkPiercingRound()) // if player doesn't have piercer equipped
				{
					player.setBulletFalse(); // will set bullet to false
				}
				enemies[i].setExplodingTrue(); // sets exploding to true
				m_deadEnemies++; // adds to dead enemies
				m_totaldeadEnemies++; // adds to total dead enemies
				m_score += 10; // adds to score
			}
			enemies[i].setAliveFalse(); // sets alive to false
			enemies[i].setKilledTrue(); // sets killed to true
		}
	}
	for (int i = 0; i < 2; i++)
	{
		if (player.getBullet().getGlobalBounds().intersects(enemiesH[i].getTank().getGlobalBounds())) // if collides with heavy tank
		{
			if (enemiesH[i].checkDamage()) // if heavy enemy is damaged
			{
				enemiesH[i].setAliveFalse(); // set alive to false
				if (!player.checkPiercingRound()) // if no piercing round equipped
				{
					player.setBulletFalse(); // set bullet to false
				}
				m_score += 20; // adds to score
				m_totaldeadEnemies++; // adds to total dead enemies
				enemiesH[i].setExplodingTrue(); // sets exploding to true
			}
			else // if not damaged
			{
				enemiesH[i].setDamageTrue(); // sets damaged to true
				if (!player.checkPiercingRound())
				{
					player.setBulletFalse();
				}
				m_score += 5;
			}
		}
		
	}

}

/// <summary>
/// player collisions with light tanks
/// </summary>
void Game::playerCollisions()
{
	
	bool contact = false; // by default contact set to false

	for (int i = 0; i < m_activeEnemies; i++)
	{
		if (player.getHitbox().getGlobalBounds().intersects(enemies[i].getTank().getGlobalBounds())) // if player collides with light enemy
		{
			if (enemies[i].checkAlive())
			{
				contact = true; // sets contact to true
			}
		}
	}
	player.m_enemyContact = contact; // sets boolion to true or false depending on outcome
		
	
	
	for (int i = 0; i < m_activeEnemies; i++)
	{
		if (player.getHitbox().getGlobalBounds().intersects(enemies[i].getHealthDrop().getGlobalBounds())) // if collides with healthdrop
		{
			if (enemies[i].checkHealthDropActive()) // if it is active
			{
				player.heal(); // heals player
				enemies[i].healthDropReset(); // resets health drop
				playHealthSound();
				m_healing = true;
			}
		}
		if (player.getHitbox().getGlobalBounds().intersects(enemies[i].getSuperHealthDrop().getGlobalBounds())) // if collides with super healthdrop
		{
			player.superHeal();
			enemies[i].healthDropReset();
			playHealthSound();
			m_superHealing = true;
		}
	}
	for (int i = 0; i < 2; i++)
	{
		if (player.getHitbox().getGlobalBounds().intersects(enemiesH[i].getPiercerRound().getGlobalBounds())) // if collides with piercing round power up
		{
			enemiesH[i].piercerReset();
			player.setPiercingRoundTrue();
			playPiercerSound();
		}
	}

}

/// <summary>
/// checks mouse collisions with restart game box
/// </summary>
/// <param name="t_event"></param>
void Game::mouseCollisions(sf::Event t_event)
{
	if (m_mousePos.x > 560 && m_mousePos.x < 940 && m_mousePos.y > 570 && m_mousePos.y < 690 && t_event.MouseButtonReleased)
	{
		gameReset();
	}
}

/// <summary>
/// enemy bullet collisions with enemy
/// </summary>
void Game::enemyBulletCollisions()
{
	for (int i = 0; i < m_activeEnemies; i++)
	{
		if (enemies[i].getBullet().getGlobalBounds().intersects(player.getHitbox().getGlobalBounds()))
		{
			enemies[i].setBulletActiveFalse();
			enemies[i].setBulletPosition();
			player.lightDamage();
		}
	}
	for (int i = 0; i < 2; i++)
	{
		if (enemiesH[i].getBullet().getGlobalBounds().intersects(player.getHitbox().getGlobalBounds()))
		{
			enemiesH[i].setBulletFalse();
			player.heavyDamage();
		}
	}
}

/// <summary>
/// adds light enemies based on how many light enemies were killed
/// </summary>
void Game::addEnemies()
{	
	if (m_deadEnemies == 5)
	{
		m_activeEnemies = 2;
	}
	if (m_deadEnemies == 10)
	{
		m_activeEnemies = 4;
	}
	if (m_deadEnemies == 20)
	{
		m_activeEnemies = 6;
	}
		
	
}

/// <summary>
/// constantly gets mouse position
/// </summary>
/// <param name="t_event"></param>
void Game::getMousePos(sf::Event t_event)
{
	m_mousePos.x = static_cast<float>(t_event.mouseMove.x);
	m_mousePos.y = static_cast<float>(t_event.mouseMove.y);

}

/// <summary>
/// toggle for debug
/// </summary>
/// <param name="t_event"></param>
void Game::debugToggle(sf::Event t_event)
{	
	if (!m_debugMode)
	{
		m_debugMode = true;
	}
	else
	{
		m_debugMode = false;
	}
	
}

/// <summary>
/// plays game music
/// </summary>
void Game::playGameMusic()
{
	if (!m_gameMusic)
	{
		m_gameSound.play();
		m_gameMusic = true;
	}
}

/// <summary>
/// plays health pickup sound
/// </summary>
void Game::playHealthSound()
{
	m_healthSound.play();
}

/// <summary>
/// plays piercer pickup sound
/// </summary>
void Game::playPiercerSound()
{
	m_piercerSound.play();
}
/// <summary>
/// normal healing animation
/// </summary>
void Game::healingAnimation()
{
	int lastFrame = m_currentHealingFrame;
	m_healingframeCounter += m_healingframeIncrement;
	m_currentHealingFrame = static_cast<int>(m_healingframeCounter) % 10;
	if (lastFrame != m_currentHealingFrame)
	{
		m_healingSprite.setTextureRect(sf::IntRect{ m_currentHealingFrame * 1500, 0, 1500, 1200 });
	}
	if (m_currentHealingFrame == 9) // when animation is at final frame
	{
		m_healing = false; // sets to false to prevent animation from cycling again
		// resets parameters to do with actual animation
		m_currentHealingFrame = 0;
		m_healingframeCounter = 0.0;
		lastFrame = 0;
	}
}
/// <summary>
/// super healing animation
/// </summary>
void Game::superHealingAnimation()
{
	int lastFrame = m_currentSHealingFrame;
	m_sHealingframeCounter += m_sHealingframeIncrement;
	m_currentSHealingFrame = static_cast<int>(m_sHealingframeCounter) % 10;
	if (lastFrame != m_currentSHealingFrame)
	{
		m_superHealSprite.setTextureRect(sf::IntRect{ m_currentSHealingFrame * 1500, 0, 1500, 1200 });
	}
	if (m_currentSHealingFrame == 9) // when animation is at final frame
	{
		m_superHealing = false; // sets to false to prevent animation from cycling again
		// resets parameters to do with actual animation
		m_currentSHealingFrame = 0;
		m_sHealingframeCounter = 0.0;
		lastFrame = 0;
	}
}
