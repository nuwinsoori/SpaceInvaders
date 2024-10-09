
#include "Enemy.h"
#include "Global.h"

Enemy::Enemy() { initializeEnemies(); }

Enemy::Enemy(float PosX, float PosY) : pointValue(10), direction(1) {
  texture = new sf::Texture;
  sprite = new sf::Sprite;
  texture->loadFromFile("./Sprites/1163.png");
  sprite->setTexture(*texture);
  sprite->setPosition(PosX, PosY);
  sprite->scale(0.25f, 0.25f);
}

void Enemy::move(sf::Time deltaTime) {
  float timeSinceMove = enemyMoveTime.getElapsedTime().asSeconds();
  if (timeSinceMove >= ENEMY_MOVE_TIME) {
    if (willReachEndOfScreen(deltaTime)) {
      descent();
      changeDirection();
    }

    for (auto &enemy : enemies) {
      enemy->sprite->move(
          ENEMY_SPEED * enemy->direction * deltaTime.asSeconds(), 0);
    }
    enemyMoveTime.restart();
  }

  for(auto &bullet : bullets) {
    bullet->update(deltaTime);
  }

}

bool Enemy::willReachEndOfScreen(sf::Time deltaTime) {
  for (auto &enemy : enemies) {
    float next_x_right = enemy->sprite->getPosition().x +
                         enemy->sprite->getGlobalBounds().width +
                         ENEMY_SPEED * enemy->direction * deltaTime.asSeconds();
    float next_x_left = enemy->sprite->getPosition().x +
                        ENEMY_SPEED * enemy->direction * deltaTime.asSeconds();
    if (next_x_left <= 0 || next_x_right >= SCREEN_WIDTH) {
      return true;
    }
  }
  return false;
}

void Enemy::drawAll(sf::RenderWindow &window) {
  for (auto &enemy : enemies) {
    enemy->draw(window);
  }
  for (auto &bullet : bullets) {
    bullet->draw(window);
  }
}

void Enemy::descent() {
  for (auto &enemy : enemies) {
    enemy->sprite->move(0, ENEMY_DESEND_AMOUNT);
  }
  enemyMoveTime.restart();
}

void Enemy::changeDirection() {
  for (auto &enemy : enemies) {
    enemy->direction *= -1;
  }
}

void Enemy::update(sf::Time deltaTime) {}
void Enemy::initializeEnemies() {
  enemies.clear();

  for (int row = 0; row < ENEMYROW; row++) {
    for (int col = 0; col < ENEMYCOL; col++) {

      float EnemyPosX = ENEMYSTARTX + col * ENEMYSPACINGX;
      float EnemyPosY = ENEMYSTARTY + row * ENEMYSPACINGY;

      Enemy *enemy = new Enemy(EnemyPosX, EnemyPosY);
      enemies.push_back(enemy);
    }
  }

}

void Enemy::draw(sf::RenderWindow &window) { window.draw(*sprite); }

void Enemy::shoot() {
  for(auto &enemy : enemies) {
    float randomChance = static_cast<float>(rand())/RAND_MAX;

    sf::Vector2f shootingPos; 
    shootingPos.x = enemy->sprite->getPosition().x; 
    shootingPos.y = enemy->sprite->getPosition().y;

    if(randomChance < 0.002) {
      Bullet *bullet = new Bullet(shootingPos, true);
      bullets.push_back(bullet);
    }
  }

} // Handles shooting

void Enemy::die() {} // handles if enemy dies
