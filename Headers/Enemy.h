#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include <SFML/System/Vector2.hpp>
#include <iostream>

class Enemy : public Entity {
protected:
  float EnemySpeed;
  int directon;
  float descendAmount;
  unsigned int pointValue;

public:
  Enemy();
  void move(sf::Time deltaTime);
  void descent();
  void changeDirection();
  bool reachedEndOfScreen();
};

#endif
