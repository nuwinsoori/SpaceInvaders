#include "Headers/GameManager.h"
#include "Headers/Bullet.h"
#include "Headers/Enemy.h"
#include "Headers/Global.h"
#include "Headers/Player.h"

GameManager::GameManager()
    : currentState(Playing), enemy(ENEMYSTARTX, ENEMYSTARTY, enemyTexture) {
  srand(static_cast<unsigned>(time(0)));

  loadAssets();
  initializeEnemies();
}

bool GameManager::loadAssets() {
  if (!bulletTexture.loadFromFile("./Sprites/bullet.png")) {
    std::cout << "Error loading bullet texture!" << std::endl;
    return false;
  }
  if (!enemyTexture.loadFromFile("./Sprites/1163.png")) {
    std::cout << "Error loading enemy texture." << endl;
    return false;
  }
  return true;
}

void GameManager::update(sf::Time deltaTime) {
  if (currentState == Playing) {
    // Update player and enemy positions, handle bullet movement
    player.update(deltaTime);
    handlePlayerShooting();
    handleEnemyShooting();

    // iterates all bullets in vector
    for (auto &bullet : bullets) {
      bullet.update(deltaTime);
    }

    // iterates all enemies in vector
    for (auto &enemy : enemies) {
      enemy.move(deltaTime);
    }

    // delete bullets that are out of frame
    for (unsigned int i = 0; i < bullets.size();) {
      if (bullets[i].isOffScreen()) {
        bullets.erase(bullets.begin() + i);
      } else {
        i++; // only increase i if object not removed
      }
    }

  } else if (currentState == GameOver) {
    // TODO:: add gameover message and play again button.
    // by implementing the restartGame function.
  }
}

void GameManager::initializeEnemies() {
  enemies.clear();

  for (int row = 0; row < ENEMYROW; row++) {
    for (int col = 0; col < ENEMYCOL; col++) {

      float EnemyPosX = ENEMYSTARTX + col * ENEMYSPACINGX;
      float EnemyPosY = ENEMYSTARTY + row * ENEMYSPACINGY;

      Enemy enemy(EnemyPosX, EnemyPosY, enemyTexture);

      enemies.push_back(enemy);
    }
  }
}

void GameManager::draw(sf::RenderWindow &window) {
  player.draw(window);
  for (auto &enemy : enemies) {
    enemy.draw(window);
  }
  // Draw each bullet
  for (auto &bullet : bullets) {
    bullet.draw(window);
  }
}

void GameManager::handlePlayerShooting() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    if (playerReloadTime.getElapsedTime().asSeconds() >= PLAYER_FIRE_RATE) {

      bullets.push_back(
          Bullet(player.getPosition().x + (player.getDimensions().width / 2),
                 690.0f, -BULLET_VELOCITY, bulletTexture));

      playerReloadTime.restart();
    }
  }
}

void GameManager::handleEnemyShooting() {
  for (auto &enemy : enemies) {
    float randomChance = static_cast<float>(rand()) /
                         RAND_MAX; // returns a float between 0 and 1
    if (randomChance <=
        0.0002) { // 0.002 chance shooting per frame (120fps), per enemy
      bullets.push_back(Bullet(enemy.getPosition().x, enemy.getPosition().y,
                               BULLET_VELOCITY, bulletTexture));
    }
  }
}

void GameManager::checkGameOver() {
  if (player.getPlayerLives() <= 0) {
    currentState = GameOver;
  }
  // add if enemies reach certian position
}

void GameManager::restartGame() {
  player.setPlayerLives(3);
  currentState = Playing;
}

GameManager::GameState GameManager::getCurrentState() { return currentState; }
