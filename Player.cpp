#include "./Headers/Player.h"
#include "./Headers/Global.h"
#include "Headers/Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Player::Player()
    : lives(3), playerSpeed(PLAYER_SPEED), score(0), fireRate(PLAYER_FIRE_RATE),
      shield(false), triple(false), rapid(false) {
  sprite.setPosition(STARTING_X, STARTING_Y);
  if (!texture.loadFromFile("./Sprites/player.png")) {
    std::cout << "Error loading player texture!" << std::endl;
  }
  sprite.setTexture(texture); // Set texture to sprite
}

void Player::update(sf::Time deltaTime) {
  sf::FloatRect boundary = getDimensions();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    if (boundary.left > 0) {
      sprite.move(-(playerSpeed * deltaTime.asSeconds()), 0.0f);
    }
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    if (boundary.left + boundary.width < 1200) {
      sprite.move(playerSpeed * deltaTime.asSeconds(), 0.0f);
    }
  }
}

void Player::shoot() {}

// reduce player lives and change sprite
void Player::loseLife() {
  lives -= 1;
  if (!isAlive()) {
    // TODO:: Add gameover
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

float Player::getTop() { return sprite.getGlobalBounds().top; };

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
