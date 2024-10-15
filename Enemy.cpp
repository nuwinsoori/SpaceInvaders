
#include "Enemy.h"
#include "Global.h"
#include "Player.h"

Enemy::Enemy() { initializeEnemies(); }

Enemy::Enemy(float PosX, float PosY, int position)
    : pointValue(10), direction(1) {
  texture = new sf::Texture;
  sprite = new sf::Sprite;

  switch (position) {
  case 1:
    texture->loadFromFile("./Sprites/topEnemy.png");
    pointValue = 40;
    break;
  case 2:
    texture->loadFromFile("./Sprites/midEnemy.png");
    pointValue = 20;
    break;
  case 3:
    texture->loadFromFile("./Sprites/botEnemy.png");
    pointValue = 10;
    break;
  }

  frame1 = sf::IntRect(0, 0, 13, 10);  // First frame (left side)
  frame2 = sf::IntRect(14, 0, 13, 10); // Second frame (right side)
  sprite->setTexture(*texture);
  sprite->setPosition(PosX, PosY);
  // set up frame
  sprite->scale(3.0f, 3.0f);
  sprite->setTextureRect(frame1);
}

Enemy::~Enemy() {
  delete this->sprite;
  delete this->texture;
  this->texture = nullptr;
  this->sprite = nullptr;
}

void Enemy::move(sf::Time deltaTime, Enemy& enemy) {
  float timeSinceMove = enemyMoveTime.getElapsedTime().asSeconds();
 
  if (timeSinceMove >= ENEMY_MOVE_TIME) {
    
    for(auto &enemy : enemies) {
      float enemyBottom = enemy->sprite->getGlobalBounds().top + enemy->sprite->getGlobalBounds().height;
      if (willReachEndOfScreen(deltaTime) && enemyBottom == ENEMY_STOP_DESCENT) {
        changeDirection();
      } else if (willReachEndOfScreen(deltaTime)) {
        descent();
        changeDirection();  
      }
    }

    // moves each enemy
    for (auto &enemy : enemies) {
      enemy->sprite->move(
          ENEMY_SPEED * enemy->direction * deltaTime.asSeconds(), 0);
      enemy->switchFrame();
    }
    enemyMoveTime.restart();
  }

  if(enemies.empty()) {
    initializeEnemies();
  }

  for (auto &bullet : bullets) {
    bullet->update(deltaTime);
  }
  deleteOutOfBoundsBullets();
}

void Enemy::switchFrame() {
  isFrame1 = !isFrame1; // Toggle the frame flag
  if (isFrame1) {
    sprite->setTextureRect(frame1);
  } else {
    sprite->setTextureRect(frame2);
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

void Enemy::draw(sf::RenderWindow &window) {
  for (auto &enemy : enemies) {
    window.draw(*enemy->sprite);
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
  int map[5] = {1, 2, 2, 3,
                3}; // The pattern you want to repeat for each column

  for (int col = 0; col < ENEMYCOL; col++) {   // Loop through columns first
    for (int row = 0; row < ENEMYROW; row++) { // Loop through rows

      float EnemyPosX = ENEMYSTARTX + col * ENEMYSPACINGX;
      float EnemyPosY = ENEMYSTARTY + row * ENEMYSPACINGY;

      // Using modulo to cycle through the map array vertically
      int enemyType = map[row % 5]; // Cycle through map based on the row

      Enemy *enemy = new Enemy(EnemyPosX, EnemyPosY, enemyType);
      enemies.push_back(enemy);
    }
  }
}

void Enemy::shoot() {
  for (auto &enemy : enemies) {
    float randomChance = static_cast<float>(rand()) / RAND_MAX;

    sf::Vector2f enemyPos;
    enemyPos.x = (enemy->sprite->getGlobalBounds().left +
                  (enemy->sprite->getGlobalBounds().width / 2));
    enemyPos.y = enemy->sprite->getGlobalBounds().top;

    if (randomChance < 0.0002) {
      Bullet *bullet = new Bullet(enemyPos, true);
      bullets.push_back(bullet);
    }
  }
}

int Enemy::getPoints() { return this->pointValue; }

int Enemy::getEnemyCount() { return enemies.size(); }

void Enemy::deleteOutOfBoundsBullets() {
  for (int i = 0; i < bullets.size(); i++) {
    if (bullets.at(i)->offScreen()) {
      deleteBullet(i);
      i--;
    }
  }
}

void Enemy::deleteBullet(int index) {
  if (index >= 0 && index < bullets.size()) {
    delete bullets.at(index);
    bullets.erase(bullets.begin() + index);
  }
}

sf::FloatRect Enemy::getDimensions() { return sprite->getGlobalBounds(); }
