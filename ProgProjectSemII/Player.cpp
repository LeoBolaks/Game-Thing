//Name: Leo Bolaks
//Login: C00299368

#include "Player.h"   // include Player header file

// Player function definitions here

Player::Player()
{

	loadTank();
	loadAudio();
}
/// <summary>
/// loads everything to do with the tank
/// </summary>
void Player::loadTank()
{
	if (!m_tankTexture.loadFromFile("ASSETS\\IMAGES\\Player_Tank.png"))
	{
		std::cout << "Error loading player tank" << std::endl;
	}
	m_tankSprite.setTexture(m_tankTexture);
	m_tankSprite.setTextureRect(sf::IntRect(0, 0, 91, 150));
	m_tankSprite.setOrigin(46, 75);
	m_tankSprite.setRotation(180.0f);
	m_tankSprite.setPosition(750.0f, 1050.0f);

	if (!m_turretTexture.loadFromFile("ASSETS\\IMAGES\\Player_Turret.png"))
	{
		std::cout << "Error loading player turret" << std::endl;
	}
	m_turretSprite.setTexture(m_turretTexture);
	m_turretSprite.setPosition(m_tankSprite.getPosition());
	m_turretSprite.setOrigin(46.0f, 45.0f);
	m_turretSprite.setRotation(180);

	if (!m_bulletTexture.loadFromFile("ASSETS\\IMAGES\\P_Round.png"))
	{
		std::cout << "Error loading player tank round" << std::endl;
	}
	m_bulletSprite.setTexture(m_bulletTexture);
	m_bulletSprite.setPosition(m_turretSprite.getPosition());
	m_bulletSprite.setRotation(m_turretSprite.getRotation());
	m_bulletSprite.setOrigin(3.0f, 8.0f);

	if (!m_criticalHealthText.loadFromFile("ASSETS\\IMAGES\\Critical_Damage.png"))
	{
		std::cout << "Error loading critical health image" << std::endl;
	}
	m_criticalHealthSprite.setTexture(m_criticalHealthText);

	if (!m_explosionTexture.loadFromFile("ASSETS\\IMAGES\\Player_Explosion.png"))
	{
		std::cout << "Error loading explosion image" << std::endl;
	}
	m_explosionSprite.setTexture(m_explosionTexture);
	m_explosionSprite.setTextureRect(sf::IntRect{ 0,0,100,100 });
	m_explosionSprite.setPosition(-150.0f, -150.0f);
	m_explosionSprite.setOrigin(50.0f, 50.0f);
	m_explosionSprite.setScale(2.5, 2.5);


	m_tankHitbox.setSize(sf::Vector2f(70, 130));
	m_tankHitbox.setFillColor(sf::Color::Transparent);
	m_tankHitbox.setOutlineColor(sf::Color::Green);
	m_tankHitbox.setOutlineThickness(1.0f);
	m_tankHitbox.setOrigin(35, 65);
	m_tankHitbox.setPosition(m_tankSprite.getPosition());

	m_healthBar.setFillColor(sf::Color::Green);
	m_healthBar.setSize(sf::Vector2f(m_health,35));
	m_healthBar.setScale(3.5f, 1.0f);
	m_healthBar.setPosition(30, 1150);

	m_gunIndicator.setFillColor(sf::Color::Green);
	m_gunIndicator.setRadius(23);
	m_gunIndicator.setOrigin(sf::Vector2f{ 23,23 });
	m_gunIndicator.setPosition(1450, 1165);
}

/// <summary>
/// returns tank sprite
/// </summary>
/// <returns></returns>
sf::Sprite Player::getTank()
{

	return m_tankSprite;
}
/// <summary>
/// returns turret sprite
/// </summary>
/// <returns></returns>
sf::Sprite Player::getTurret()
{
	return m_turretSprite;
}

/// <summary>
/// moves player up on the screen
/// </summary>
void Player::moveUp()
{
	m_direction = NORTH;
	m_location = m_tankSprite.getPosition();

	if (m_location.y > 235.0f)
	{
		m_location.y -= m_speed * 1.5f;
	}
	m_tankSprite.setRotation(180.0f);
	m_tankHitbox.setRotation(0.0f);
	m_tankHitbox.setSize(sf::Vector2f(70, 130));
	m_tankHitbox.setOrigin(35, 65);
	
	animations();

	m_turretSprite.setPosition(m_tankSprite.getPosition());
	m_tankHitbox.setPosition(m_location);
	m_tankSprite.setPosition(m_location);
	
}

/// <summary>
/// loads all audio to do with the player
/// </summary>
void Player::loadAudio()
{
	if (!m_alarmBuffer.loadFromFile("ASSETS\\SOUNDS\\Alarm.wav"))
	{
		std::cout << "Error loading alarm sound" << std::endl;
	}
	m_alarmSound.setBuffer(m_alarmBuffer);
	m_alarmSound.setLoop(true);
	m_alarmSound.setVolume(70);

	if (!m_fireBuffer.loadFromFile("ASSETS\\SOUNDS\\Fire.wav"))
	{
		std::cout << "Error loading firing sound" << std::endl;
	}
	m_fireSound.setBuffer(m_fireBuffer);

	if (!m_explosionBuffer.loadFromFile("ASSETS\\SOUNDS\\Player_Explosion.wav"))
	{
		std::cout << "Error loading playerExplosion" << std::endl;
	}
	m_explosionSound.setBuffer(m_explosionBuffer);
	

}
/// <summary>
/// moves player up and left diagonally
/// </summary>
void Player::moveUpL()
{
	m_direction = NW;
	m_location = m_tankSprite.getPosition();
	if (m_location.y > 235.0f)
	{
		m_location.y -= m_speed * 0.5f;
	}
	if (m_location.x > 75.0f)
	{
		m_location.x -= m_speed * 0.5f;
	}
	m_tankSprite.setRotation(135.0f);
	m_tankHitbox.setSize(sf::Vector2f(130, 130));
	m_tankHitbox.setOrigin(65, 65);

	
	m_turretSprite.setPosition(m_tankSprite.getPosition());
	m_tankHitbox.setPosition(m_location);
	m_tankSprite.setPosition(m_location);

}

/// <summary>
/// moves player up and right diagonally
/// </summary>
void Player::moveUpR()
{
	m_direction = NE;
	m_location = m_tankSprite.getPosition();
	if (m_location.y > 235.0f)
	{
		m_location.y -= m_speed * 0.5f;
	}
	if (m_location.x < SCREEN_WIDTH - 75.0f)
	{
		m_location.x += m_speed * 0.5f;
	}
	m_tankSprite.setRotation(225.0f);
	m_tankHitbox.setSize(sf::Vector2f(130, 130));
	m_tankHitbox.setOrigin(65, 65);
	
	m_turretSprite.setPosition(m_tankSprite.getPosition());
	m_tankHitbox.setPosition(m_location);
	m_tankSprite.setPosition(m_location);

}
bool Player::checkPiercingRound()
{
	return m_piercingRound;
}
sf::Sprite Player::getCriticalHealth()
{
	return m_criticalHealthSprite;
}
/// <summary>
/// moves the player down the screen
/// </summary>
void Player::moveDown()
{
	m_direction = SOUTH;
	m_location = m_tankSprite.getPosition();
	if (m_location.y < SCREEN_HEIGHT - 145.0f)
	{
		m_location.y += m_speed * 1.5f;
	}
	m_tankSprite.setRotation(0.0f);
	m_tankHitbox.setRotation(0.0f);
	m_tankHitbox.setSize(sf::Vector2f(70, 130));
	m_tankHitbox.setOrigin(35, 65);

	animations();

	m_turretSprite.setPosition(m_tankSprite.getPosition());
	m_tankHitbox.setPosition(m_location);
	m_tankSprite.setPosition(m_location);

}
bool Player::checkAlive()
{
	return m_alive;
}
/// <summary>
/// moves the player down and left diagonally
/// </summary>
void Player::moveDownL()
{
	m_direction = SW;
	m_location = m_tankSprite.getPosition();
	if (m_location.y < SCREEN_HEIGHT - 145.0f)
	{
		m_location.y += m_speed * 0.5f;
	}
	if (m_location.x > 75.0f)
	{
		m_location.x -= m_speed * 0.5f;
	}
	m_tankSprite.setRotation(45.0f);
	m_tankHitbox.setSize(sf::Vector2f(130, 130));
	m_tankHitbox.setOrigin(65, 65);
	
	m_turretSprite.setPosition(m_tankSprite.getPosition());
	m_tankHitbox.setPosition(m_location);
	m_tankSprite.setPosition(m_location);

}
/// <summary>
/// moves the player down and right diagonally
/// </summary>
void Player::moveDownR()
{
	m_direction = SE;
	m_location = m_tankSprite.getPosition();
	if (m_location.y < SCREEN_HEIGHT - 145.0f)
	{
		m_location.y += m_speed * 0.5f;
	}
	if (m_location.x < SCREEN_WIDTH - 75.0f)
	{
		m_location.x += m_speed * 0.5f;
	}
	m_tankSprite.setRotation(-45.0f);
	m_tankHitbox.setSize(sf::Vector2f(130, 130));
	m_tankHitbox.setOrigin(65, 65);

	m_turretSprite.setPosition(m_tankSprite.getPosition());
	m_tankHitbox.setPosition(m_location);
	m_tankSprite.setPosition(m_location);

}

/// <summary>
/// moves the player left on the screen
/// </summary>
void Player::moveLeft()
{
	m_direction = WEST;
	m_location = m_tankSprite.getPosition();
	if (m_location.x > 75.0f)
	{
		m_location.x -= m_speed * 1.5f;
	}
	m_tankSprite.setRotation(90.0f);
	m_tankHitbox.setRotation(90.0f);
	m_tankHitbox.setSize(sf::Vector2f(70, 130));
	m_tankHitbox.setOrigin(35, 65);

	animations();

	m_turretSprite.setPosition(m_tankSprite.getPosition());
	m_tankHitbox.setPosition(m_location);
	m_tankSprite.setPosition(m_location);

}
/// <summary>
/// moves the player right on the screen
/// </summary>
void Player::moveRight()
{
	m_direction = EAST;
	m_location = m_tankSprite.getPosition();
	if (m_location.x < SCREEN_WIDTH - 75.0f)
	{ 
	m_location.x += m_speed * 1.5f;
	}
	m_tankSprite.setRotation(270.0f);
	m_tankHitbox.setRotation(90.0f);
	m_tankHitbox.setSize(sf::Vector2f(70, 130));
	m_tankHitbox.setOrigin(35, 65);

	animations();

	m_turretSprite.setPosition(m_tankSprite.getPosition());
	m_tankHitbox.setPosition(m_location);
	m_tankSprite.setPosition(m_location);

}

void Player::setPiercingRoundTrue()
{
	m_piercingRound = true;
}

/// <summary>
/// this function deals with movement animations
/// </summary>
void Player::animations()
{
	
	int lastFrame = m_currentFrame;
	m_frameCounter += m_frameIncrement;
	m_currentFrame = static_cast<int>(m_frameCounter) % 6;
	if (lastFrame != m_currentFrame)
	{
		m_tankSprite.setTextureRect(sf::IntRect{ m_currentFrame * 91, 0, 91, 150 });
	} 

}

/// <summary>
/// update for player class
/// </summary>
/// <param name="t_mousePos"></param>
void Player::update(sf::Vector2f t_mousePos)
{
	if (m_alive) // if alive will allow the player to move, shoot, reload, and collide 
	{
		turretRotation(t_mousePos);
		healthCheck();
		shooting(t_mousePos);
		if (m_firing)
		{
			changeTurretState();
		}
		if (m_enemyContact)
		{
			collisions();
		}
		if (!m_enemyContact)
		{
			m_speed = std::abs(m_speed); // absolute operation changes any number from a negative to positive value
		}
		updateGunIndicator();
	}
	if (!m_alive && m_exploding) // if not alive and exploding, will play the exploding animation
	{
		explosionAnimation();
	}
}

sf::Sprite Player::getBullet()
{
	return m_bulletSprite;
}

sf::Vector2f Player::getLocation()
{
	return m_location;
}

/// <summary>
/// checks current health of tank
/// </summary>
void Player::healthCheck()
{
	m_healthBar.setSize(sf::Vector2f(m_health, 35));
	if (m_health > 20.0f) // if health is greater than 20
	{
		m_healthBar.setFillColor(sf::Color::Green); // sets colour to green
		m_criticalHealth = false; // sets critical health to false
		m_alarm = false; // turns off alarm
		m_alarmSound.stop();
	}
	else // if it is less than 20
	{
		m_healthBar.setFillColor(sf::Color::Red); // sets colour to red
		m_criticalHealth = true; // sets critical health to true and plays alarm sound
		if (!m_alarm)
		{
			m_alarmSound.play();
			m_alarm = true;
		}
	}
	if (m_health > 100.0f)
	{
		m_health = 100.0f; // sets to 100 to stay within the health box
	}
	if (m_health <= 0.0f) // same for less than 0
	{
		m_health = 0.0f;
		m_alive = false;
		m_exploding = true;
		m_alarmSound.stop();
		if (!m_explodingSound)
		{
			m_explosionSound.play();
			m_explodingSound = true;
		}
	}

}

sf::RectangleShape Player::getHitbox()
{
	return m_tankHitbox;
}

sf::RectangleShape Player::getHealthBar()
{
	return m_healthBar;
}

bool Player::checkFiring()
{
	return m_firing;
}

bool Player::checkBullet()
{
	return m_bulletActive;
}

void Player::setFiringTrue()
{
	m_firing = true;
}

void Player::setBulletTrue()
{
	m_bulletActive = true;
}

void Player::setBulletFalse()
{
	m_bulletActive = false;
}

void Player::turretRotation(sf::Vector2f t_mousePos)
{
	float angleDegrees; // angle in degrees
	float angleRadians; // angle in radians
	sf::Vector2f line; // the line from the turret to the mouse

	m_turretPos = m_tankSprite.getPosition(); // calculates the turret end position
	line = t_mousePos - m_turretPos; // calculates the line between the turret and the mouse
	angleRadians = std::atan2f(line.y, line.x); // gets tan inverse of the line
	angleDegrees = angleRadians * 180.0f / 3.1415926f; // converts radians to degrees
	m_turretSprite.setRotation(angleDegrees - 90.0f); // rotates the turret to the degree and takes away 90 to accomodate for sprite rotation
	

}

void Player::healthReset()
{
	m_health = 100;
}

bool Player::checkCriticalHealth()
{
	return m_criticalHealth;
}

/// <summary>
/// changes turret state to reloading after firing to start reload
/// </summary>
void Player::changeTurretState()
{
	if (m_turretState == TurretState::Ready)
	{
		m_turretState = TurretState::Reloading;
	}
	if (m_turretState == TurretState::Reloading)
	{
		reload();
	}

}

/// <summary>
/// shooting towards the mouse pointers last position
/// </summary>
/// <param name="t_mousePos"></param>
void Player::shooting(sf::Vector2f t_mousePos)
{
	if (!m_bulletActive)
	{
		float length;
		float speed = 30.0f;

		m_bulletSprite.setPosition(m_turretSprite.getPosition()); // sets bullet to turret position
		m_bulletSprite.setRotation(m_turretSprite.getRotation()); // sets bullet rotation to turret rotation
		m_bulletVelocity = t_mousePos - m_turretSprite.getPosition();
		length = std::sqrt(m_bulletVelocity.x * m_bulletVelocity.x + m_bulletVelocity.y * m_bulletVelocity.y); // calculates the magnitude of the vector
		m_bulletVelocity /= length;
		m_bulletVelocity *= speed;
	}
	else if (m_bulletActive) // if the bullet is active
	{
		if (!m_firingSound) // plays shooting sound
		{
			m_fireSound.play();
			m_firingSound = true;
		}
		m_bulletLocation = m_bulletSprite.getPosition();
		m_bulletLocation += m_bulletVelocity;
		m_bulletSprite.setPosition(m_bulletLocation);

	}
	if (m_bulletLocation.y < 0 || m_bulletLocation.x < 0 || m_bulletLocation.y > 1200 || m_bulletLocation.x > 1500)
	{
		m_bulletActive = false;
		m_piercingRound = false;
	}

	
}

/// <summary>
/// upon game reset this resets the player position
/// </summary>
void Player::positionReset()
{
	m_location = { 750, 1050 };
	m_tankSprite.setPosition(m_location);
	m_turretSprite.setPosition(m_location);
	m_bulletSprite.setPosition(m_location);
	m_tankHitbox.setPosition(m_location);
	m_tankSprite.setRotation(180);
}

void Player::setAliveTrue()
{
	m_alive = true;
}

/// <summary>
/// deals with collisions by reversing speed, and the second it is no longer colliding will use absolute operation in update to change speed
/// back to normal
/// </summary>
void Player::collisions()
{
	switch (m_direction)
	{
	case NORTH:
		m_location.y += m_speed; // Adjusts position
		m_speed = -m_speed; // Reverses speed
		break;
	case EAST:
		m_location.x -= m_speed; // Adjusts position
		m_speed = -m_speed; // Reverses speed
		break;
	case SOUTH:
		m_location.y -= m_speed; // Adjusts position
		m_speed = -m_speed; // Reverses speed
		break;
	case WEST:
		m_location.x += m_speed; // Adjusts position
		m_speed = -m_speed; // Reverses speed
		break;
	case NW:
		m_location.x += m_speed; // Adjusts position
		m_location.y += m_speed; // Adjusts position
		m_speed = -m_speed; // Reverses speed
		break;
	case NE:
		m_location.x -= m_speed; // Adjusts position
		m_location.y += m_speed; // Adjusts position
		m_speed = -m_speed; // Reverses speed
		break;
	case SW:
		m_location.x -= m_speed; // Adjusts position
		m_location.y += m_speed; // Adjusts position
		m_speed = -m_speed; // Reverses speed
		break;
	case SE:
		m_location.x -= m_speed; // Adjusts position
		m_location.y -= m_speed; // Adjusts position
		m_speed = -m_speed; // Reverses speed
		break;
	default:
		break;
	}

}

/// <summary>
/// reloads player tank gun
/// </summary>
void Player::reload()
{
	if (m_countdown != RELOAD_COUNTDOWN_DURATION) // constant is set to 240 to have a 4 second timer
	{
		m_countdown++;
	}
	else
	{
		m_turretState = TurretState::Ready; // sets turret state to ready so player can fire again
		m_countdown = 0;
		m_firing = false;
		m_bulletActive = false;
		m_firingSound = false;
	}

}

/// <summary>
/// deals light damage to player
/// </summary>
void Player::lightDamage()
{
	if (m_health < m_lightDamage)
	{
		m_health = 0; //sets health to 0 if its already less than what the light damage will do
	}
	else
	{
		m_health -= m_lightDamage;
	}
}

/// <summary>
/// deals heavy damage to player
/// </summary>
void Player::heavyDamage()
{
	if (m_health < m_heavyDamage)
	{
		m_health = 0; // sets health to 0 if its already less than what the heavy damage will do
	}
	else
	{
		m_health -= m_heavyDamage;
	}
}

sf::Sprite Player::getExplosion()
{
	return m_explosionSprite;
}

/// <summary>
/// heals sprite without going over 100 health
/// </summary>
void Player::heal()
{
	float smallHeal = 0.0f;
	if (m_health >= 70.0f)
	{
		smallHeal = 100.0f - m_health;
		m_health += smallHeal;
	}
	else
	{
		m_health += m_heal;
	}
	
}

bool Player::checkExploding()
{
	return m_exploding;
}

sf::CircleShape Player::getGunIndicator()
{
	return m_gunIndicator;
}

/// <summary>
/// heals player to full health
/// </summary>
void Player::superHeal()
{
	float heal = 0.0f;

	heal = 100.0f - m_health;
	m_health += heal;
}

/// <summary>
/// sets exploding sound and animation boolions to false
/// </summary>
void Player::setExplodingFalse()
{
	m_exploding = false;
	m_explodingSound = false;
}

/// <summary>
/// exploding animation - taken from pete
/// </summary>
void Player::explosionAnimation()
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

void Player::updateGunIndicator()
{
	if (m_turretState == TurretState::Ready)
	{
		m_gunIndicator.setFillColor(sf::Color::Green);
	}
	if (m_turretState == TurretState::Ready && m_piercingRound)
	{
		m_gunIndicator.setFillColor(sf::Color::Magenta);
	}
	if (m_turretState == TurretState::Reloading)
	{
		m_gunIndicator.setFillColor(sf::Color::Red);
	}
}






