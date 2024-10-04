#include "./Headers/Player.h"
#include "Headers/Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>

Player::Player()
    : lives(3), playerSpeed(300.f), score(0), fireRate(0.75f), shield(false),
      triple(false), rapid(false) {
  setPosition(600.0f, 715.0f);
  if (!texture.loadFromFile("./sprites/player.png")) {
    std::cout << "Error loading player texture!" << std::endl;
  }
  sprite.setTexture(texture); // Set texture to sprite
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

// reduce player lives and change sprite
void Player::loseLife() {
  lives -= 1;
  if (!isAlive()) {
    // gameover
  } else {
    std::cout << lives << std::endl; // DEUGGING
    updateSprite();
  }
}

void Player::updateSprite() {
  std::string newSprite;
  if (lives == 3) {
    newSprite = "./Sprites/player.png";
  } else if (lives == 2) {
    newSprite = "./Sprites/player(2livesleft).png";
  } else if (lives == 1) {
    newSprite = "./Sprites/player(1lifeleft).png";
  } else {
    std::cout << "ERROR: Should be dead" << std::endl;
    return;
  }

  if (!texture.loadFromFile(newSprite)) {
    std::cout << "Error loading player texture!" << std::endl;
  }
  sprite.setTexture(texture); // set texture to new sprite
}

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
