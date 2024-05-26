//Name: Leo Bolaks
//Login: C00299368

#include "EnemiesHeavy.h"

EnemiesHeavy::EnemiesHeavy()
{
	loadTank();
	loadAudio();
}

/// <summary>
/// loads sprites
/// </summary>
void EnemiesHeavy::loadTank()
{
	if (!m_tankTexture.loadFromFile("ASSETS\\IMAGES\\Enemy_H.png"))
	{
		std::cout << "Error loading heavy tank" << std::endl;
	}
	m_tankSprite.setTexture(m_tankTexture);
	m_tankSprite.setPosition(200, 70);
	m_tankSprite.setTextureRect(sf::IntRect(0, 7, 120, 126));
	m_tankSprite.setOrigin(60, 63);

	if (!m_bulletTexture.loadFromFile("ASSETS\\IMAGES\\E2_Round.png"))
	{
		std::cout << "Error loading heavy tank round" << std::endl;
	}
	m_bulletSprite.setTexture(m_bulletTexture);
	m_bulletSprite.setPosition(m_tankSprite.getPosition());
	m_bulletSprite.setOrigin(11, 26);

	if (!m_healthTexture.loadFromFile("ASSETS\\IMAGES\\Enemy_Health.png"))
	{
		std::cout << "Error loading enemy healthbar" << std::endl;
	}
	m_healthSprite.setTexture(m_healthTexture);
	m_healthSprite.setOrigin(30, 5);

	if (!m_piercerRoundTexture.loadFromFile("ASSETS\\IMAGES\\Piercer.png"))
	{
		std::cout << "Error loading piercing round powerup" << std::endl;
	}
	m_piercerRoundSprite.setTexture(m_piercerRoundTexture);
	m_piercerRoundSprite.setOrigin(26, 26);
	m_piercerRoundSprite.setScale(1.3f, 1.3f);
	m_piercerRoundSprite.setPosition(-100, -100);
	m_piercerRoundSprite.setTextureRect(sf::IntRect(0, 0, 51, 51));

	if (!m_explosionTexture.loadFromFile("ASSETS\\IMAGES\\Explosion.png"))
	{
		std::cout << "Error loading explosion image" << std::endl;
	}
	m_explosionSprite.setTexture(m_explosionTexture);
	m_explosionSprite.setTextureRect(sf::IntRect{ 0,0,100,100 });
	m_explosionSprite.setPosition(-150.0f, -150.0f);
	m_explosionSprite.setOrigin(50.0f, 50.0f);
	m_explosionSprite.setScale(2.2, 2.2);
}

/// <summary>
/// loads audio
/// </summary>
void EnemiesHeavy::loadAudio()
{
	if (!m_firingBuffer.loadFromFile("ASSETS\\SOUNDS\\Enemy_Fire.wav"))
	{
		std::cout << "Error loading heavy enemy firing sound" << std::endl;
	}
	m_firingSound.setBuffer(m_firingBuffer);
	m_firingSound.setPitch(0.75);
	m_firingSound.setVolume(70);

	if (!m_explosionBuffer.loadFromFile("ASSETS\\SOUNDS\\Explosion.wav"))
	{
		std::cout << "Error loading light tank explosion sound" << std::endl;
	}
	m_explosionSound.setBuffer(m_explosionBuffer);
	m_explosionSound.setPitch(0.75);

}

sf::Sprite EnemiesHeavy::getTank()
{
	return m_tankSprite;
}

sf::Sprite EnemiesHeavy::getBullet()
{
	return m_bulletSprite;
}

sf::Sprite EnemiesHeavy::getHealthbar()
{
	return m_healthSprite;
}

sf::Sprite EnemiesHeavy::getPiercerRound()
{
	return m_piercerRoundSprite;
}

sf::Sprite EnemiesHeavy::getExplosion()
{
	return m_explosionSprite;
}

bool EnemiesHeavy::checkBullet()
{
	return m_activeBullet;
}

bool EnemiesHeavy::checkDamage()
{
	return m_damaged;
}

bool EnemiesHeavy::checkAlive()
{
	return m_aliveH;
}

bool EnemiesHeavy::checkExploding()
{
	return m_exploding;
}

void EnemiesHeavy::setAliveFalse()
{
	m_aliveH = false;
}

void EnemiesHeavy::setDamageTrue()
{
	m_damaged = true;
}

void EnemiesHeavy::setBulletFalse()
{
	m_activeBullet = false;
}

void EnemiesHeavy::setDamageFalse()
{
	m_damaged = false;
}

void EnemiesHeavy::setExplodingTrue()
{
	m_exploding = true;
}

/// <summary>
/// heavy enemy class update
/// </summary>
void EnemiesHeavy::update()
{
	if (m_aliveH)
	{
		move();
	}
	else
	{
		respawn();
	}
	if (m_piercerActive)
	{
		piercerMove();
	}
	if (!m_aliveH && m_exploding)
	{
		explosionAnimation();
	}
	animationsPowerUp();
	reload();
	shooting();

}

/// <summary>
/// reloads cannon
/// </summary>
void EnemiesHeavy::reload()
{
	if (!m_aliveH)
	{
		m_reloadCountdown = 0;
	}
	if (m_reloadCountdown != RELOAD_COUNTDOWN_DURATION) // constant is set to 480 to have a 8 second timer
	{
		m_reloadCountdown++;
	}
	else
	{
		m_fireSound = false;
		m_reloadCountdown = 0;
		m_activeBullet = true; // Set bullet active when reload finishes
	}

}

/// <summary>
/// shooting down in a straight line
/// </summary>
void EnemiesHeavy::shooting()
{
	float bulletSpeed = 15.0f;
	if (!m_activeBullet)
	{
		m_bulletSprite.setPosition(m_tankSprite.getPosition()); // sets bullet to turret position
		m_bulletLocation = m_tankSprite.getPosition();
	}
	else
	{
		if (!m_fireSound)
		{
			m_firingSound.play();
			m_fireSound = true;
		}
		m_bulletLocation.y += bulletSpeed;
		m_bulletSprite.setPosition(m_bulletLocation);
	}
	if (m_bulletLocation.y > SCREEN_HEIGHT + 51)
	{
		m_activeBullet = false;
	}
}

/// <summary>
/// randomly generates the piercer powerup
/// </summary>
void EnemiesHeavy::setPiercer()
{
	int num; // random number which is generated

	num = (rand() % 6) + 1; // generates a random number between 1 and 15
	if (num == 2 || num == 4)
	{
		m_piercerLocation = m_tankSprite.getPosition();
		m_piercerActive = true;
	}

}

/// <summary>
/// resets piercer round
/// </summary>
void EnemiesHeavy::piercerReset()
{
	m_piercerActive = false;
	m_piercerRoundSprite.setPosition(-100, -100);
	m_piercerSpeed = 10.0f;
}

/// <summary>
/// moves the piercer round if it is spawned
/// </summary>
void EnemiesHeavy::piercerMove()
{
	if (m_piercerLocation.y < 200) // if the enemy location is greater than the x position
	{
		
			m_piercerLocation.y += m_piercerSpeed; // stops accelerating and just increases the location
		
	}
	else if (m_piercerLocation.y > 200) // if the tank location is less than the specified position location
	{
		if (m_speed > 0) // if speed is less than 0
		{
			m_piercerSpeed -= m_piercerDecrement; // decelerates tank 
			m_piercerLocation.y += m_piercerSpeed;
		}
		else
		{
			m_piercerSpeed = 0.0f; // if speed is 0, sets speed to 0
		}
	}
	m_piercerRoundSprite.setPosition(m_piercerLocation);
}

/// <summary>
/// respawns the heavy enemies once timer runs out
/// </summary>
void EnemiesHeavy::respawn()
{
	if (!m_explodingSound)
	{
		m_explosionSound.play();
		m_explodingSound = true;
	}
	m_damaged = false;
	m_tankSprite.setTextureRect(sf::IntRect(120, 7, 120, 126));
	m_location.x = -126;
	if (!m_activeBullet)
	{
		m_bulletSprite.setColor(sf::Color::Transparent);
	}

	if (m_respawnCountdown != RESPAWN_COUNTDOWN_DURATION) // constant is set to 600 to have a 10 second timer
	{
		m_respawnCountdown++;
	}
	else
	{
		setPiercer();
		m_explodingSound = false;
		m_tankSprite.setPosition(m_location);
		m_healthSprite.setPosition(m_location);
		m_respawnCountdown = 0;
		m_tankSprite.setTextureRect(sf::IntRect(0, 7, 120, 126)); // changes sprite back to alive one
		m_bulletSprite.setColor(sf::Color::White);
		m_aliveH = true;
	}
}

/// <summary>
/// animates piercer powerup
/// </summary>
void EnemiesHeavy::animationsPowerUp()
{
	int lastFrame = m_currentFrame;
	m_frameCounter += m_frameIncrement;
	m_currentFrame = static_cast<int>(m_frameCounter) % 12;
	if (lastFrame != m_currentFrame)
	{
		m_piercerRoundSprite.setTextureRect(sf::IntRect{ m_currentFrame * 51, 0, 51, 51 });
	}

}

/// <summary>
/// animates explosion
/// </summary>
void EnemiesHeavy::explosionAnimation()
{
	m_explosionSprite.setPosition(m_tankSprite.getPosition()); // sets explosion sprite to the destroyed tank sprite
	int frame;
	const int ROWS = 6;
	const int COLS = 8;
	const int SIZE = 100;
	int col;
	int row;

	m_explosionFrameTimer += m_explosionIncrement;
	frame = static_cast<int>(m_explosionFrameTimer);

	if (frame != m_explosionFrame)
	{
		col = frame % 8;
		row = frame / 6;
		m_explosionSprite.setTextureRect(sf::IntRect(col * SIZE, row * SIZE, SIZE, SIZE));
	}
	if (frame > 47)
	{
		m_explosionFrameTimer -= 48.0f;
		frame = 0;
		m_exploding = false;
	}

}

void EnemiesHeavy::setPosition(int xPos, int yPos)
{
	m_tankSprite.setPosition(xPos, yPos);
}

/// <summary>
/// moves tank to the right
/// </summary>
void EnemiesHeavy::move()
{
	m_location = m_tankSprite.getPosition();
	m_location.x += m_speed;
	if (m_location.x > SCREEN_WIDTH + 126)
	{
		m_location.x = -126;
	}
	m_tankSprite.setPosition(m_location);
	m_bulletSprite.setPosition(m_location);
	m_healthSprite.setPosition(m_location.x, m_location.y - 70);
}
