#include "Player.h"
#include "Enemy.h"
#include "Global.h"
#include "SpecialEnemy.h"
#include "bullet.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <cstdio>
#include <fstream>
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

  // load sounds
  if (!dieBuffer.loadFromFile("./Sounds/explosion.wav")) {
    std::cout << "ERROR: loading sound" << std::endl;
  }
  if (!shootBuffer.loadFromFile("./Sounds/shoot.wav")) {
    std::cout << "ERROR: loading sound" << std::endl;
  }
  if (!shotEnemyBuffer.loadFromFile("./Sounds/invaderkilled.wav")) {
    std::cout << "ERROR: loading sound" << std::endl;
  }

  dieSound.setBuffer(dieBuffer);
  shootSound.setBuffer(shootBuffer);
  shotEnemySound.setBuffer(shotEnemyBuffer);

  // loading highscore
  std::ifstream file("scores.txt");
  if (file.is_open()) {
    std::string line;
    int lineNumber = 0;

    // Read lines until the second line is reached
    while (std::getline(file, line)) {
      lineNumber++;
      if (lineNumber == 2) {
        highScore = std::stoi(line); // Convert string to integer
        break;
      }
    }
    file.close();
  } else {
    std::cout << "Unable to open file!" << std::endl;
  }

  font.loadFromFile("./pixelFont.ttf");

  // showing score
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

sf::Vector2f Player::getLeftTop() {
  sf::Vector2f left; 
  left.x = (sprite->getGlobalBounds().left); 
  left.y = sprite->getGlobalBounds().top;
  return left; 
}

sf::Vector2f Player::getRightTop() {
  sf::Vector2f right;
  right.x = (sprite->getGlobalBounds().left + sprite->getGlobalBounds().width);
  right.y = sprite->getGlobalBounds().top;
  return right; 
}

// Shooting method
void Player::shoot() {
  switch (shootingStyle) {
    case 1:
      normalShoot();
      break;
    case 2:
      rapidFire();
      break;
    case 3:
      tripleShot();
      break;
  }

}

void Player::normalShoot() {
  // get time since player last shot bullet
  float timeSinceShot = playerReloadTime.getElapsedTime().asSeconds();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
      timeSinceShot >= PLAYER_FIRE_RATE) {
    Bullet *bullet = new Bullet(getMiddleTop(), false);
    bullets.push_back(bullet);
    shootSound.play();
    playerReloadTime.restart();
  }
}

void Player::rapidFire() {
  float timeSinceShot = playerReloadTime.getElapsedTime().asSeconds();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
      timeSinceShot >= RAPID_FIRE_RATE) {
    Bullet *bullet = new Bullet(getMiddleTop(), false);
    bullets.push_back(bullet);
    shootSound.play();
    playerReloadTime.restart();
  }

}

void Player::tripleShot() {
    float timeSinceShot = playerReloadTime.getElapsedTime().asSeconds();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
      timeSinceShot >= RAPID_FIRE_RATE) {
    Bullet *middleBullet = new Bullet(getMiddleTop(), false);
    Bullet *leftBullet = new Bullet(getLeftTop(), false);
    Bullet *rightBullet = new Bullet(getRightTop(), false);
    
    bullets.push_back(middleBullet);
    bullets.push_back(leftBullet);
    bullets.push_back(rightBullet);

    shootSound.play();
    playerReloadTime.restart();
  }
}

void Player::extraLife() {
  lives++;
  livesText.setString("Lives: " + std::to_string(lives));
}

void Player::deleteBullet(int index) {
  if (index >= 0 && index < bullets.size()) {
    delete bullets.at(index);
    bullets.erase(bullets.begin() + index);
  }
}

void Player::collision(Enemy &enemy, SpecialEnemy &specialenemy) {
  for (int i = 0; i < bullets.size(); i++) {
    Bullet *currentBullet = bullets.at(i);
    if (currentBullet) { // makes sure is a valid pointer
      if (currentBullet->getDimensions().intersects(
              specialenemy.getDimensions())) {
        specialenemy.die(1); // calls with true to play death sound
        deleteBullet(i);
        i--;
        break;
      }

      for (int j = 0; j < enemy.getEnemyCount(); j++) {
        Enemy *currentEnemy = enemy.enemies.at(j);
        if (currentEnemy) { // Ensure it's a valid pointer
          // Check for collision between the bullet and the current enemy
          if (currentBullet->getDimensions().intersects(
                  currentEnemy->getDimensions())) {

            // kill the hit enemy and update points
            updateScore(currentEnemy->getPoints());
            enemy.enemies.erase(enemy.enemies.begin() + j);
            delete currentEnemy;

            // play sound
            shotEnemySound.play();

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
      dieSound.play();
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
    // Read highscore from "scores.txt"
    std::ifstream infile("scores.txt");
    if (infile) {
      int prev_score;
      infile >> prev_score >> highScore;
    }
    infile.close();

    // Update highscore if current_score is greater
    if (score > highScore) {
      highScore = score;
    }

    // Write current_score and highscore back to "scores.txt"
    std::ofstream outfile("scores.txt");
    outfile << score << "\n" << highScore << "\n";
    outfile.close();
  }
}

bool Player::isAlive() {
  if (lives > 0) {
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
