#include "Player.h"
#include "Global.h"
#include "bullet.h"
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

// Constructor
Player::Player()
    : lives(3), playerSpeed(PLAYER_SPEED), score(0), fireRate(PLAYER_FIRE_RATE),
      shield(false), triple(false), rapid(false) {
  texture = new sf::Texture;
  sprite = new sf::Sprite;
  texture->loadFromFile("./Sprites/player.png");
  sprite->setTexture(*texture);
  sprite->setPosition(STARTING_X, STARTING_Y);
}

// Move method
void Player::move(sf::Time deltaTime) {
  sf::FloatRect boundary = sprite->getGlobalBounds();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    if (boundary.left > 0) {
      sprite->move(-(playerSpeed * deltaTime.asSeconds()), 0.0f);
    }
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    if (boundary.left + boundary.width < 1200) {
      sprite->move(playerSpeed * deltaTime.asSeconds(), 0.0f);
    }
  }

  for (auto &bullet : bullets) {
    bullet->update(deltaTime);
  }
}

// Shooting method
void Player::shoot() {
  // get time since player last shot bullet
  float timeSinceShot = playerReloadTime.getElapsedTime().asSeconds();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
      timeSinceShot >= PLAYER_FIRE_RATE) {
    bullets *bullet = new Bullet(sprite->getPosition(), false);
    bullets.push_back(bullet);
    playerReloadTime.restart();
  }
}

// Losing life method
void Player::loseLife() {
  lives -= 1;
  if (isAlive()) {
    updateSprite();
  } else {
    // TODO: Add game over logic
  }
}

bool Player::isAlive() {
  if (lives >= 0) {
    return true;
  } else {
    return false;
  }
}

// Update sprite method
void Player::updateSprite() {
  if (lives == 3) {
    sprite = "./Sprites/player.png";
  } else if (lives == 2) {
    sprite = "./Sprites/player(2livesleft).png";
  } else if (lives == 1) {
    sprite = "./Sprites/player(1lifeleft).png";
  } else {
    std::cout << "ERROR: Should be dead" << std::endl;
    return;
  }

  if (!texture->loadFromFile(newSprite)) {
    std::cout << "Error loading player texture!" << std::endl;
  }
  sprite->setTexture(*texture); // set texture to new sprite
}

void Player::draw(sf::RenderWindow &window) {
  for (auto &bullet : bullets) {
    bullet->draw(window);
  }
  window.draw(*sprite);
};
