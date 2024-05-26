//Name: Leo Bolaks
//Login: C00299368

#include "Enemies.h"
/// <summary>
/// Constructor for light enemy class
/// </summary>
Enemies::Enemies()
{
	loadTank();
	loadAudio();
}
/// <summary>
/// loads all sprite assets to do with the light tank
/// </summary>
void Enemies::loadTank()
{
	if (!m_tankTexture.loadFromFile("ASSETS\\IMAGES\\Enemy_Tank.png"))
	{
		std::cout << "Error loading enemy light tank" << std::endl;
	}
	m_tankSprite.setTexture(m_tankTexture);
	m_tankSprite.setTextureRect(sf::IntRect(0, 0, 91, 120));
	m_tankSprite.setOrigin(46.0f, 60.0f);
	spawn();

	if (!m_turretTexture.loadFromFile("ASSETS\\IMAGES\\Enemy_Turret_Light.png"))
	{
		std::cout << "Error loading enemy light tank turret" << std::endl;
	}
	m_turretSprite.setTexture(m_turretTexture);
	m_turretSprite.setOrigin(36.0f, 52.0f);
	m_turretSprite.setPosition(m_location);

	if (!m_bulletTexture.loadFromFile("ASSETS\\IMAGES\\E1_Round.png"))
	{
		std::cout << "Error loading light enemy round" << std::endl;
	}
	m_bulletSprite.setTexture(m_bulletTexture);
	m_bulletSprite.setPosition(m_tankSprite.getPosition());
	m_bulletSprite.setRotation(m_turretSprite.getRotation());
	m_bulletSprite.setOrigin(3, 6);

	if (!m_healthDropTexture.loadFromFile("ASSETS\\IMAGES\\Health_Kit.png"))
	{
		std::cout << "Error loading health kit" << std::endl;
	}
	m_healthDropSprite.setTexture(m_healthDropTexture);
	m_healthDropSprite.setOrigin(26, 26);
	m_healthDropSprite.setScale(1.3, 1.3);
	m_healthDropSprite.setTextureRect(sf::IntRect(0, 0, 51, 51));

	if (!m_superHealthTexture.loadFromFile("ASSETS\\IMAGES\\Super_Health_kit.png"))
	{
		std::cout << "Error loading super health sprite" << std::endl;
	}
	m_superHealthSprite.setTexture(m_superHealthTexture);
	m_superHealthSprite.setOrigin(26, 26);
	m_superHealthSprite.setScale(1.3, 1.3);
	m_superHealthSprite.setTextureRect(sf::IntRect(0, 0, 51, 51));

	if (!m_explosionTexture.loadFromFile("ASSETS\\IMAGES\\Explosion.png"))
	{
		std::cout << "Error loading explosion image" << std::endl;
	}
	m_explosionSprite.setTexture(m_explosionTexture);
	m_explosionSprite.setTextureRect(sf::IntRect{ 0,0,100,100 });
	m_explosionSprite.setPosition(-150.0f, -150.0f);
	m_explosionSprite.setOrigin(50.0f, 50.0f);
	m_explosionSprite.setScale(2.2, 2.2);

	m_stopDistance.setRadius(500.0f);
	m_stopDistance.setFillColor(sf::Color::Transparent);
	m_stopDistance.setOutlineColor(sf::Color::Red);
	m_stopDistance.setOutlineThickness(1.0f);
	m_stopDistance.setOrigin(500.0f, 500.0f);
	m_stopDistance.setPosition(m_tankSprite.getPosition());
	
}
/// <summary>
/// loads all audio assets to do with the light tank
/// </summary>
void Enemies::loadAudio()
{
	if (!m_fireBuffer.loadFromFile("ASSETS\\SOUNDS\\Enemy_Fire.wav"))
	{
		std::cout << "Error loading enemy firing sound " << std::endl;
	}
	m_firingSound.setBuffer(m_fireBuffer);
	m_firingSound.setVolume(70);

	if (!m_explosionBuffer.loadFromFile("ASSETS\\SOUNDS\\Explosion.wav"))
	{
		std::cout << "Error loading light tank explosion sound" << std::endl;
	}
	m_explosionSound.setBuffer(m_explosionBuffer);
}
/// <summary>
/// update for light tank class
/// </summary>
/// <param name="t_playerLocation"></param>
void Enemies::update(sf::Vector2f t_playerLocation)
{
	if (m_alive)
	{
		move(t_playerLocation);
	}
	else
	{
		respawn();
	}
	if (!m_alive && m_exploding)
	{
		explosionAnimation();
	}
	animations();
	turretRotate(t_playerLocation);
	reload();
	shooting(t_playerLocation);
	
	
}
/// <summary>
/// all get functions return objects to draw them in game
/// </summary>
/// <returns></returns>
sf::Sprite Enemies::getTank()
{
	return m_tankSprite;
}

sf::Sprite Enemies::getTurret()
{
	return m_turretSprite;
}

sf::Sprite Enemies::getBullet()
{
	return m_bulletSprite;
}

sf::CircleShape Enemies::getStopDistance()
{
	return m_stopDistance;
}

sf::Sprite Enemies::getHealthDrop()
{
	return m_healthDropSprite;
}

sf::Sprite Enemies::getSuperHealthDrop()
{
	return m_superHealthSprite;
}

sf::Sprite Enemies::getExplosion()
{
	return m_explosionSprite;
}
/// <summary>
/// all check functions are used to check boolions
/// </summary>
/// <returns></returns>
bool Enemies::checkAlive()
{
	return m_alive;
}

bool Enemies::checkExploding()
{
	return m_exploding;
}
/// <summary>
/// set functions either set the boolion to true or false
/// </summary>
void Enemies::setAliveFalse()
{
	m_alive = false;
}

void Enemies::setAlivetrue()
{
	m_alive = true;
}

void Enemies::setExplodingTrue()
{
	m_exploding = true;
}

void Enemies::setStopMoveTrue()
{
	m_stopMove = true;
}

void Enemies::setStopMoveFalse()
{
	m_stopMove = false;
}

void Enemies::setKilledTrue()
{
	m_killed = true;
}

void Enemies::setBulletActiveFalse()
{
	m_bulletActive = false;
}

void Enemies::setBulletPosition()
{
	m_bulletSprite.setPosition(-10, -10);
}
/// <summary>
/// Random spawn generator, all positions are hard coded and there is 12 of them in total
/// </summary>
void Enemies::spawn()
{
	m_alive = true;
	int num; // random number which is generated

	num = (rand() % 12) + 1; // generates a random number between 1 and 12
	// each position is hard coded depending on the number generated
	if (num == 1)
	{
		m_location = { 500, -100 };
		m_tankSprite.setPosition(m_location);
		m_turretSprite.setPosition(m_location);
		m_stopDistance.setPosition(m_location);
	}
	if (num == 2)
	{
		m_location = { 1000, -100 };
		m_tankSprite.setPosition(m_location);
		m_turretSprite.setPosition(m_location);
		m_stopDistance.setPosition(m_location);
	}
	if (num == 3)
	{
		m_location = { 750, -100 };
		m_tankSprite.setPosition(m_location);
		m_turretSprite.setPosition(m_location);
		m_stopDistance.setPosition(m_location);
	}
	if (num == 4)
	{
		m_location = { -100, 400 };
		m_tankSprite.setPosition(m_location);
		m_turretSprite.setPosition(m_location);
		m_stopDistance.setPosition(m_location);
	}
	if (num == 5)
	{
		m_location = { -100, 700 };
		m_tankSprite.setPosition(m_location);
		m_turretSprite.setPosition(m_location);
		m_stopDistance.setPosition(m_location);
	}
	if (num == 6)
	{
		m_location = { -100, 900 };
		m_tankSprite.setPosition(m_location);
		m_turretSprite.setPosition(m_location);
		m_stopDistance.setPosition(m_location);
	}
	if (num == 7)
	{
		m_location = { 1600, 400 };
		m_tankSprite.setPosition(m_location);
		m_turretSprite.setPosition(m_location);
		m_stopDistance.setPosition(m_location);
	}
	if (num == 8)
	{
		m_location = { 1600, 700 };
		m_tankSprite.setPosition(m_location);
		m_turretSprite.setPosition(m_location);
		m_stopDistance.setPosition(m_location);
	}
	if (num == 9)
	{
		m_location = { 1600, 900 };
		m_tankSprite.setPosition(m_location);
		m_turretSprite.setPosition(m_location);
		m_stopDistance.setPosition(m_location);
	}
	if (num == 10)
	{
		m_location = { 200, -100 };
		m_tankSprite.setPosition(m_location);
		m_turretSprite.setPosition(m_location);
		m_stopDistance.setPosition(m_location);
	}
	if (num == 11)
	{
		m_location = { -100, 300 };
		m_tankSprite.setPosition(m_location);
		m_turretSprite.setPosition(m_location);
		m_stopDistance.setPosition(m_location);
	}
	if (num == 12)
	{
		m_location = { 850, -100 };
		m_tankSprite.setPosition(m_location);
		m_turretSprite.setPosition(m_location);
		m_stopDistance.setPosition(m_location);
	}

}
/// <summary>
/// function deals with enemy movement towards the player, it also rotates the tank to face the player as it is moving
/// </summary>
/// <param name="t_playerLocation"></param>
void Enemies::move(sf::Vector2f t_playerLocation)
{
	if (!m_stopMove)
	{
		float length; // vector along which the tank will move
		float angleDegrees; // angle in degrees
		float angleRadians; // angle in radians
		sf::Vector2f line; // line between player location and enemy location

		m_tankVelocity = t_playerLocation - m_tankSprite.getPosition();
		length = std::sqrt(m_tankVelocity.x * m_tankVelocity.x + m_tankVelocity.y * m_tankVelocity.y); // calculates the magnitude of the vector
		line = t_playerLocation - m_tankSprite.getPosition();
		angleRadians = std::atan2f(line.y, line.x); // gets tan inverse of the line
		angleDegrees = angleRadians * 180.0f / 3.1415926f; // converts radians to degrees
		m_tankSprite.setRotation(angleDegrees - 90.0f); // sets the tanks rotation and takes away 90 to accomodate for sprite rotation
		m_tankVelocity /= length; // velocity is then divided by length
		m_tankVelocity *= m_speed; // multiplies the velocity by the speed to extend the vector
		m_location += m_tankVelocity; // changes location of the tank
		// sprites are set to the position of the location
		m_tankSprite.setPosition(m_location);
		m_stopDistance.setPosition(m_tankSprite.getPosition());
		m_turretSprite.setPosition(m_tankSprite.getPosition());
	}
}
/// <summary>
/// rotates turret to always face player no matter if tank is moving or not
/// </summary>
/// <param name="t_playerLocation"></param>
void Enemies::turretRotate(sf::Vector2f t_playerLocation)
{
	float angleDegrees; // angle in degrees
	float angleRadians; // angle in radians
	sf::Vector2f line; // the line from the turret to the mouse

	line = m_location - t_playerLocation; // calculates the line between the location of the tank and the player position
	angleRadians = std::atan2f(line.y, line.x); // gets tan inverse of the line
	angleDegrees = angleRadians * 180.0f / 3.1415926f; // converts radians to degrees
	m_turretSprite.setRotation(angleDegrees + 90.0f); // rotates the turret to the degree and adds 90 to accomodate for sprite rotation


}
/// <summary>
/// sets the tank to a dead sprite and sets sprites such as turret to invisible,then runs a timer after which itll reset sprite colours to be visible again
/// and runs the spawn function to randomly generate a new position
/// </summary>
void Enemies::respawn()
{
	if (!m_explodingSound)
	{
		m_explosionSound.play();
		m_explodingSound = true;
	}
	m_killed = false;
	m_tankSprite.setTextureRect(sf::IntRect(91, 0, 91, 120));
	m_turretSprite.setColor(sf::Color::Transparent);
	if (!m_bulletActive)
	{
		m_bulletSprite.setColor(sf::Color::Transparent);
	}

	if (m_countdown != RESPAWN_COUNTDOWN_DURATION) // constant is set to 300 to have a 5 second timer
	{
		m_countdown++;
	}
	else
	{
		healthDropCheck();
		m_explodingSound = false;
		m_tankSprite.setTextureRect(sf::IntRect(0, 0, 91, 120)); // changes sprite back to alive one
		m_turretSprite.setColor(sf::Color::White); // disables transparancy
		m_bulletSprite.setColor(sf::Color::White);
		m_countdown = 0; // sets countdown to 0
		spawn(); // randomly generates new position
	}

}
// check for if health drop is active
bool Enemies::checkHealthDropActive()
{
	return m_healthDropActive;
}
/// <summary>
/// after enemy has fired this reloads the gun and prevents enemy from firing non-stop
/// </summary>
void Enemies::reload()
{
	if (!m_alive)
	{
		m_reloadCountdown = 0;
	}
	if (m_reloadCountdown != RELOAD_COUNTDOWN_DURATION) // constant is set to 300 to have a 5 second timer
	{
		m_reloadCountdown++;
	}
	else
	{
		m_fireSound = false;
		m_reloadCountdown = 0;
		m_bulletActive = true; // Set bullet active when reload finishes
	}
}
/// <summary>
/// this function deals with light tank shooting towards the player, it calculates the velocity vector along which the bullet will fly across
/// </summary>
/// <param name="t_playerLocation"></param>
void Enemies::shooting(sf::Vector2f t_playerLocation)
{
	if (m_alive)
	{
		if (!m_bulletActive)
		{
			float length;
			float speed = 15.0f;

			m_bulletSprite.setPosition(m_turretSprite.getPosition()); // sets bullet to turret position
			m_bulletSprite.setRotation(m_turretSprite.getRotation()); // sets bullet rotation to turret rotation
			m_bulletVelocity = t_playerLocation - m_turretSprite.getPosition();
			length = std::sqrt(m_bulletVelocity.x * m_bulletVelocity.x + m_bulletVelocity.y * m_bulletVelocity.y); // calculates the magnitude of the vector
			m_bulletVelocity /= length;
			m_bulletVelocity *= speed;
		}

		else
		{
			if (!m_fireSound)
			{
				m_firingSound.play();
				m_fireSound = true;
			}
			// Move the bullet
			m_bulletLocation = m_bulletSprite.getPosition() + m_bulletVelocity;
			m_bulletSprite.setPosition(m_bulletLocation);
		}
	}
	else if (!m_alive && m_bulletActive)
	{
		m_bulletLocation = m_bulletSprite.getPosition() + m_bulletVelocity;
		m_bulletSprite.setPosition(m_bulletLocation);
	}
	if (m_bulletLocation.x < 0 || m_bulletLocation.x > SCREEN_WIDTH || m_bulletLocation.y < 0 || m_bulletLocation.y > SCREEN_HEIGHT)
	{
		// Bullet is out of bounds, deactivate it
		m_bulletActive = false;
	}

}
/// <summary>
/// random generator for a health drop
/// </summary>
void Enemies::healthDropCheck()
{
	m_healthDropActive = true;
	int num; // random number which is generated

	num = (rand() % 20) + 1; // generates a random number between 1 and 10
	if (num == 3 || num == 6 || num == 9 || num == 12 || num == 16 || num == 20)
	{
		m_healthDropSprite.setPosition(m_tankSprite.getPosition());
	}
	else if (num == 10)
	{
		m_superHealthSprite.setPosition(m_tankSprite.getPosition());
	}
	
	
}
/// <summary>
/// when picked up by player, resets the health drop off screen
/// </summary>
void Enemies::healthDropReset()
{
	m_healthDropSprite.setPosition(-100, -100);
	m_superHealthSprite.setPosition(-100, -100);
	m_healthDropActive = false;
}
/// <summary>
/// deals with the healthdrop idle animations
/// </summary>
void Enemies::animations()
{
	int lastFrame = m_currentFrame;
	m_frameCounter += m_frameIncrement;
	m_currentFrame = static_cast<int>(m_frameCounter) % 15;
	if (lastFrame != m_currentFrame)
	{
		m_healthDropSprite.setTextureRect(sf::IntRect{ m_currentFrame * 51, 0, 51, 51 });
		m_superHealthSprite.setTextureRect(sf::IntRect{ m_currentFrame * 51,0,51,51 });
	}
}
/// <summary>
/// deals with the explosion animation - taken from petes code
/// </summary>
void Enemies::explosionAnimation()
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
