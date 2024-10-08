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
  std::vector<Enemy> enemies;

public:
  Enemy();
  Enemy(float PosX, float PosY, const sf::Texture &texture);
  void move(sf::Time deltaTime);
  void descent();
  void changeDirection();
  bool reachedEndOfScreen();
  void update(sf::Time deltaTime); 
  void initializeEnemies();
  void draw(sf::RenderWindow &window); 
};

#endif
