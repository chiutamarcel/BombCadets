#include "Player.h"

#include "Entities.h"
#include "Client.h"
#include "Logger.h"

void Player::movement(float deltaTime)
{
	velocity = input * speed * deltaTime;
}

void Player::init()
{
	Entities::getInstance().setPlayer(*this);
	cooldownTimer.restart();
	input = sf::Vector2f(0.0f, 0.0f);
}

Player::Player(sf::Vector2f position, sf::Vector2f size, float speed):
	Character(position, size, speed)
{
	init();
}

Player::Player(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, float speed):
	Character(position, size, texture, speed)
{
	init();
}

Player::Player(sf::Vector2f position, float length, sf::Texture* texture, float speed):
	Character(position, length, texture, speed)
{
	init();
}

Player::Player(sf::Vector2f position, sf::Vector2f size, sf::Color color, float speed):
	Character(position, size, color, speed)
{
	init();
}

Player::Player(sf::Vector2f position, float length, sf::Color color, float speed):
	Character(position, length, color, speed)
{
	init();
}

Player::~Player()
{
}

void Player::update(float deltaTime)
{
	Character::update(deltaTime);
	//sf::Texture* bombo = new sf::Texture;
	//bombo->loadFromFile("Textures\\bomb.png");
	//std::cout << getPosition().x << " " << getPosition().y << std::endl;
	movement(deltaTime);
}

void Player::pollEvents()
{
	// Movement input
	input.y = sf::Keyboard::isKeyPressed(sf::Keyboard::S) -
		sf::Keyboard::isKeyPressed(sf::Keyboard::W);

	input.x = sf::Keyboard::isKeyPressed(sf::Keyboard::D) -
		sf::Keyboard::isKeyPressed(sf::Keyboard::A);

	//	Bomb plant
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) && (this->cooldownTimer.getElapsedTime().asSeconds() > 3.f))
	{
		sf::Vector2f bombPos = this->getShape().getPosition() + this->getShape().getSize() * 0.5f;
		Entities::getInstance().spawnBomb(bombPos);
		Client::getInstance().sendBombPacket(bombPos);
		
		if (this->cooldownTimer.getElapsedTime().asSeconds() >= 3)
			this->cooldownTimer.restart();
	}
}
