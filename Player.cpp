#include "Player.h"
#include "Enemy.h"
#include "Global.h"
#include "bullet.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <string>

// Constructor
Player::Player()
    : lives(3), playerSpeed(PLAYER_SPEED), score(0), fireRate(PLAYER_FIRE_RATE),
      shield(false), triple(false), rapid(false) {
  texture = new sf::Texture;
  sprite = new sf::Sprite;
  texture->loadFromFile("./Sprites/player.png");
  sprite->setTexture(*texture);
  sprite->setPosition(STARTING_X, STARTING_Y);

  // showing score
  font.loadFromFile("./pixelFont.ttf");

  scoreText.setFont(font);
  scoreText.setCharacterSize(24);           // Size in pixels
  scoreText.setFillColor(sf::Color::White); // Color of the text
  scoreText.setPosition(10, 10); // Position on the screen (top-left corner)
  scoreText.setString("Score: " + std::to_string(score));

  // showing lives
  livesText.setFont(font);
  livesText.setCharacterSize(24);           // Size in pixels
  livesText.setFillColor(sf::Color::Green); // Color of the text
  livesText.setPosition(1075,
                        10); // Position on the screen (top-left corner)
  livesText.setString("Lives: " + std::to_string(lives));
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
    if (boundary.left + boundary.width < SCREEN_WIDTH) {
      sprite->move(playerSpeed * deltaTime.asSeconds(), 0.0f);
    }
  }

  for (auto &bullet : bullets) {
    bullet->update(deltaTime);
  }
  if (!bullets.empty() && bullets.at(0)->offScreen()) {
    deleteBullet(0);
  }
}

sf::Vector2f Player::getMiddleTop() {
  sf::Vector2f center;
  center.x =
      (sprite->getGlobalBounds().left + (sprite->getGlobalBounds().width / 2));
  center.y = sprite->getGlobalBounds().top;
  return center;
}

// Shooting method
void Player::shoot() {
  // get time since player last shot bullet
  float timeSinceShot = playerReloadTime.getElapsedTime().asSeconds();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
      timeSinceShot >= PLAYER_FIRE_RATE) {
    Bullet *bullet = new Bullet(getMiddleTop(), false);
    bullets.push_back(bullet);
    playerReloadTime.restart();
  }
}

void Player::deleteBullet(int index) {
  if (index >= 0 && index < bullets.size()) {
    delete bullets.at(index);
    bullets.erase(bullets.begin() + index);
  }
}

void Player::collision(Enemy &enemy) {
  for (int i = 0; i < bullets.size(); i++) {
    Bullet *currentBullet = bullets.at(i);
    if (currentBullet) { // makes sure is a valid pointer

      for (int j = 0; j < enemy.getEnemyCount(); j++) {
        Enemy *currentEnemy = enemy.enemies.at(j);
        if (currentEnemy) { // Ensure it's a valid pointer
          // Check for collision between the bullet and the current enemy
          if (currentBullet->getDimensions().intersects(
                  currentEnemy->getDimensions())) {

            // kill the hit enemy and update points
            updateScore(currentEnemy->getPoints());
            currentEnemy->die();

            std::cout << score << std::endl;

            // adjust index
            enemy.enemies.erase(enemy.enemies.begin() + j);

            // delete bullet and adjust index
            deleteBullet(i);
            i--;
            break;
          }
        }
      }
    }
  }
}

void Player::updateScore(int points) {
  this->score += points;
  scoreText.setString("Score: " + std::to_string(score)); // update score text
}

void Player::hit(Enemy &enemy) {
  for (int i = 0; i < enemy.bullets.size();) {
    Bullet *currentBullet = enemy.bullets.at(i);
    if (currentBullet->getDimensions().intersects(getDimensions())) {
      loseLife();
      enemy.deleteBullet(i);
    } else {
      i++; // Only increment i if no deletion occurred
    }
  }
}

// Losing life method
void Player::loseLife() {
  lives -= 1;
  livesText.setString("Lives: " + std::to_string(lives));
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
  std::string newSprite;
  if (lives == 3) {
    livesText.setFillColor(sf::Color::Green);
    newSprite = "./Sprites/player.png";
  } else if (lives == 2) {
    livesText.setFillColor(sf::Color::Yellow);
    newSprite = "./Sprites/player(2livesleft).png";
  } else if (lives == 1) {
    livesText.setFillColor(sf::Color::Red);
    newSprite = "./Sprites/player(1lifeleft).png";
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
  window.draw(scoreText);
  window.draw(livesText);
};
