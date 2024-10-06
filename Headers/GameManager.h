#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"

class GameManager {
protected:
  std::vector<Enemy> enemies;
  std::vector<Bullet> bullets;
  Player player;
  Enemy enemy;
  sf::Clock playerReloadTime;

public:
  GameManager() { srand(static_cast<unsigned>(time(0))); }
  void newLevel();
  void checkCollisions();
  void gameOver();
  void update(sf::Time deltaTime);
  void draw(sf::RenderWindow &window);

  void handleEnemyShooting();
  void handlePlayerShooting();
};

#endif
