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
public:
  enum GameState { Playing, GameOver };

protected:
  std::vector<Enemy> enemies;
  std::vector<Bullet> bullets;
  Player player;
  Enemy enemy;
  sf::Clock playerReloadTime;
  GameState currentState;
  sf::Texture bulletTexture;
  sf::Texture enemyTexture;

public:
  GameManager();
  bool loadAssets();
  void newLevel();
  void checkCollisions();
  void initializeEnemies();
  void update(sf::Time deltaTime);
  void draw(sf::RenderWindow &window);
  void checkGameOver();
  void restartGame();
  GameState getCurrentState();

  void handleEnemyShooting();
  void handlePlayerShooting();
};

#endif
