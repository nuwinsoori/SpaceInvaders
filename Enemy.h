#ifndef ENEMY_H
#define ENEMY_H
#include "bullet.h"
#include "entity.h"

class Enemy : public Entity {
protected:
  unsigned int pointValue;
  std::vector<Enemy *> enemies;
  std::vector<Bullet *> bullets;
  float chanceToShoot;
  int direction;
  sf::Clock enemyMoveTime;

public:
  Enemy();
  void drawAll(sf::RenderWindow &window);
  Enemy(float PosX, float PosY);
  void move(sf::Time deltaTime);
  void descent();
  void changeDirection();
  bool willReachEndOfScreen(sf::Time deltaTime);
  void update(sf::Time deltaTime);
  void initializeEnemies();
  void draw(sf::RenderWindow &window) override;
  void shoot() override; // Handles shooting
  void die();
  sf::Vector2f shootPos(); 

};

#endif
