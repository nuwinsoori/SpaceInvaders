
#include "Enemy.h"
#include "Global.h"
#include "Player.h"

// copy constructor that calls initaliseEnemies and creates and instance of
// enemies
Enemy::Enemy() { initializeEnemies(); }

// paramaterised constructor that defines values
Enemy::Enemy(float PosX, float PosY, int position)
    : pointValue(10), direction(1) {
  texture = new sf::Texture;
  sprite = new sf::Sprite;

  // switch case that handles the enemy sprite sheet
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
  default:
    std::cout << "ERROR: invalid enemy sprite" << std::endl;
  }

  frame1 = sf::IntRect(0, 0, 13, 10);  // First frame (left side)
  frame2 = sf::IntRect(14, 0, 13, 10); // Second frame (right side)
  sprite->setTexture(*texture);        // sets texture for sprites
  sprite->setPosition(PosX, PosY);     // sets position of sprite

  // set up frame
  sprite->scale(3.0f, 3.0f);
  sprite->setTextureRect(frame1);
}

// enemy destructor
Enemy::~Enemy() {
  delete this->sprite;
  delete this->texture;
  this->texture = nullptr;
  this->sprite = nullptr;
}

// enemy move function that handles enemy movement
void Enemy::move(sf::Time deltaTime) {
  // varible that hold the time since enemy last moved
  float timeSinceMove = enemyMoveTime.getElapsedTime().asSeconds();

  if (timeSinceMove >= ENEMY_MOVE_TIME) {
    // loop that handles enemies movement
    for (auto &enemy : enemies) {
      ////var that gets bottom of the enemy sprite
      float enemyBottom = enemy->sprite->getGlobalBounds().top +
                          enemy->sprite->getGlobalBounds().height;

      // this if statement ensures that enemies dont move infinately
      if (willReachEndOfScreen(deltaTime) &&
          enemyBottom == ENEMY_STOP_DESCENT) {
        changeDirection();
        // this moves the enemies down and across
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

  // respawns enemies if they are killed
  if (enemies.empty()) {
    initializeEnemies();
  }

  // loops through and updates enemies bullets based on time that passed
  for (auto &bullet : bullets) {
    bullet->update(deltaTime);
  }
  // calls function to delete bullets of screen
  deleteOutOfBoundsBullets();
}

// handles enemies animation
void Enemy::switchFrame() {
  isFrame1 = !isFrame1; // Toggle the frame flag
  if (isFrame1) {
    sprite->setTextureRect(frame1);
  } else {
    sprite->setTextureRect(frame2);
  }
}

// checks if enemies have reached edge of screen
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

// draws the enemies and there bullets in the game window
void Enemy::draw(sf::RenderWindow &window) {
  for (auto &enemy : enemies) {
    window.draw(*enemy->sprite);
  }
  for (auto &bullet : bullets) {
    bullet->draw(window);
  }
}

// moves enemies down
void Enemy::descent() {
  for (auto &enemy : enemies) {
    enemy->sprite->move(0, ENEMY_DESEND_AMOUNT);
  }
  enemyMoveTime.restart();
}

// changes the direction of enemies
void Enemy::changeDirection() {
  for (auto &enemy : enemies) {
    enemy->direction *= -1;
  }
}

// creates the columns and rows of enemies
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

  // counts how many times enemies have spawned
  respawnedCount++;
}

// get the amount of time enemies have spawned
int Enemy::getRespawnedCount() { return respawnedCount; }

// handles enemy shoot logic
void Enemy::shoot() {
  for (auto &enemy : enemies) {
    float randomChance = static_cast<float>(rand()) / RAND_MAX;

    // defines enemy position
    sf::Vector2f enemyPos;
    enemyPos.x = (enemy->sprite->getGlobalBounds().left +
                  (enemy->sprite->getGlobalBounds().width / 2));
    enemyPos.y = enemy->sprite->getGlobalBounds().top;

    // handles the chance enemies shoot
    if (randomChance < ENEMY_SHOOT_CHANCE * respawnedCount) {
      // dynamically allocates bullets
      Bullet *bullet = new Bullet(enemyPos, true);
      // adds bullets to bullet array
      bullets.push_back(bullet);
    }
  }
}

// get pointval of enemy m
int Enemy::getPoints() { return this->pointValue; }

// returns the size of enemy array
int Enemy::getEnemyCount() { return enemies.size(); }

void Enemy::clearEnemies() {
  for (auto &enemy : enemies) {
    delete enemy;
  }
  enemies.clear();
}

sf::Vector2f Enemy::getEnemyPos() { return sprite->getPosition(); }

sf::Vector2f Enemy::getEnemiesyPos() {
  for (auto &enemy : enemies) {
    enemy->getEnemyPos();
  }
}

// deletes bullets if off screen
void Enemy::deleteOutOfBoundsBullets() {
  for (size_t i = 0; i < bullets.size(); i++) {
    if (bullets.at(i)->offScreen()) {
      deleteBullet(i);
      i--;
    }
  }
}

// deletes bullents and erases them
void Enemy::deleteBullet(int index) {
  if (index >= 0 && index < bullets.size()) {
    delete bullets.at(index);
    bullets.erase(bullets.begin() + index);
  }
}

// returns sprite dimentions
sf::FloatRect Enemy::getDimensions() { return sprite->getGlobalBounds(); }
