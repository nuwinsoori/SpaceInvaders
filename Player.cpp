#include "./Headers/Player.h"
#include "/Headers/Entity.h"
#include <SFML/Graphics.hpp>

Player::Player()
    : lives(3), playerSpeed(300.f), score(0), fireRate(0.75f), shield(false),
      triple(false), rapid(false) {
  setPosition(600.0f, 715.0f);
  if (!texture.loadFromFile("./sprites/player.png")) {
    std::cout << "Error loading player texture!" << std::endl;
  } else {
    sprite.setTexture(texture); // Set texture to sprite
  }
}

void Player::moveLeft(sf::Time deltaTime) {
  sf::FloatRect boundary = getDimensions();
  if (boundary.left > 0) {
    sprite.move(-(playerSpeed * deltaTime.asSeconds()), 0.0f);
  }
}

void Player::moveRight(sf::Time deltaTime) {
  sf::FloatRect boundary = getDimensions();
  if (boundary.left + boundary.width < 1200) {
    sprite.move(playerSpeed * deltaTime.asSeconds(), 0.0f);
  }
}

void Player::shoot() {}

void Player::loseLife() { lives -= 1; }

bool Player::isAlive() {
  if (lives > 0) {
    return true;
  }
  return false;
}
void Player::setSpeed(float newSpeed) { playerSpeed = newSpeed; }

bool Player::getShieldActive() {}

bool Player::getTripleActive() {}

bool Player::getRapidActive() {}

void Player::setShieldActive() {}

void Player::setTripleActive() {}

void Player::setRapidActive() {}
