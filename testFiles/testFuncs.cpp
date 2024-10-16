#include "../Enemy.h"
#include "../Global.h"
#include "../Menu.h"
#include "../Player.h"
#include "../PowerUp.h"
#include "../SpecialEnemy.h"
#include "../bullet.h"
#include "../entity.h"
#include "test.h"
#include <SFML/Graphics/Rect.hpp>

#include "iostream"
#include <SFML/System.hpp>

using namespace std;
int playerTests() {
  int Ppassed = 0;
  

  // testing player initalisation
  // lives: 3, fireRate: 0.75, Shooting Style: Normalshooting
  Player *player = new Player();
  if (player->getPlayerLives() == 3 && player->getFireRate() == 0.75 &&
      player->getsShootingStyle() == NORMAL_SHOOTING) {
    cout << "PASSED: player intialisation test" << endl;
    Ppassed++;
  } else {
    cout << "FAILED: player intialisation test" << endl;
  }

  // testing player movement
  player->setPlayerPos(STARTING_X, STARTING_Y);
  player->moveLeft(sf::seconds(1.0f));
  if (player->getPlayerPos().x != STARTING_X) {
    cout << "PASSED: player movement test" << endl;
    Ppassed++;
  } else {
    cout << "FAILED: player movement test" << endl;
  }

  // testing player shooting
  size_t initialBulletSize = player->getBulletCount();
  player->normalShoot();

  sf::Clock clock;
  sf::sleep(sf::seconds(5));
  if (player->getBulletCount() > initialBulletSize) {
    cout << "PASSED: player shooting test" << endl;
    Ppassed++;
  } else {
    cout << "FAILED: player shooting test" << endl;
  }

  delete player;

  return Ppassed;
}

int enemyTests() {
  int Epassed = 0;

  // create getEnemyPosition
  // enemy initialisation test
  Enemy *enemy = new Enemy(ENEMYSTARTX, ENEMYSTARTY, 1);
  if (enemy->getEnemyPos().x == ENEMYSTARTX &&
      enemy->getEnemyPos().y == ENEMYSTARTY && enemy->getPoints() == 40) {
    cout << "PASSED: enemy initialisation test" << endl;
    Epassed++;
  } else {
    cout << "FAILED: enemy initialisation test" << endl;
  }

  
  // enemy movement test
  // sf::Time deltaTime = sf::seconds(3.0f);
  sf::Vector2f initialPos = enemy->getEnemyPos();
  enemy->move(sf::seconds(1.0f));
  if (initialPos != enemy->getEnemyPos()) {
    cout << "PASSED: enemy movement test" << endl;
    Epassed++;
  } else {
    cout << "FAILED: enemy movement test" << endl;
  }

  Enemy *enemy1 = new Enemy();
  // inilising another enemy, calling constructor that calls inilise enemies
  enemy1->clearEnemies();
  enemy1->move(sf::seconds(1.0f));
  if (enemy1->getEnemyCount() > 0) {
    cout << "PASSED: enemy respawn test" << endl;
    Epassed++;
  } else {
    cout << "FAILED: enemy respawn test" << endl;
  }

  delete enemy;
  delete enemy1;

  return Epassed;
}
