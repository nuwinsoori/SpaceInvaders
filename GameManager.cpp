#include "Headers/GameManager.h"
#include "Headers/Bullet.h"
#include "Headers/Enemy.h"
#include "Headers/Global.h"
#include "Headers/Player.h"

void GameManager::update(sf::Time deltaTime) {
  // Update player and enemy positions, handle bullet movement
  player.update(deltaTime);
  enemy.move(deltaTime);
  handlePlayerShooting();
  handleEnemyShooting();

  // iterates all bullets in vector
  for (auto &bullet : bullets) {
    bullet.update(deltaTime);
  }

  // delete bullets that are out of frame
  for (unsigned int i = 0; i < bullets.size();) {
    if (bullets[i].isOffScreen()) {
      bullets.erase(bullets.begin() + i);
    } else {
      i++; // only increase i if object not removed
    }
  }
}

void GameManager::draw(sf::RenderWindow &window) {
  player.draw(window);
  // TODO:: there will be more enemies so will need to draw all in vector
  enemy.draw(window);
  // Draw each bullet
  for (auto &bullet : bullets) {
    bullet.draw(window);
  }
}

void GameManager::handlePlayerShooting() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    if (playerReloadTime.getElapsedTime().asSeconds() >=
        PLAYER_FIRE_RATE) { // To avoid constant shooting, has cooldown

      // adds bullet object at end of vector
      bullets.push_back(Bullet(
          player.getPosition().x + (player.getDimensions().width / 2), 690.0f,
          -BULLET_VELOCITY)); // Player's bullets go upwards
      playerReloadTime.restart();
    }
  }
}

void GameManager::handleEnemyShooting() {
  // TODO:: SHOULD BE CHANGED TO THIS WHEN ENEMIES IN VECTOR
  // for (auto &enemy : enemies) {
  //   float randomChance = static_cast<float>(rand()) /
  //                        RAND_MAX; // returns a float between 0 and 1
  //   if (randomChance <= 0.0155) { // 1.55% chance of shooting per frame
  //     bullets.push_back(
  //         Bullet(enemy.getPosition().x, enemy.getPosition().y,
  //                BULLET_VELOCITY)); // Enemy's bullets go downwards
  //   }
  // }
  float randomChance =
      static_cast<float>(rand()) / RAND_MAX; // returns a float between 0 and 1
  if (randomChance <= (0.003))               // 0.03% chance per frame
    bullets.push_back(Bullet(enemy.getPosition().x, enemy.getPosition().y,
                             BULLET_VELOCITY)); // Enemy's bullets go downwards
}
