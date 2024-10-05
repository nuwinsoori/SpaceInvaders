#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy : public Entity {
protected:
  float EnemySpeed;
  int directon;
  float descendAmount;
  unsigned int pointValue;

public:
  Enemy();
  void move(sf::Time deltaTime, float EnemySpeed, float screenWidth);
  void descent();
  void changeDirection();
  bool reachedEndOfScreen();
};

#endif
