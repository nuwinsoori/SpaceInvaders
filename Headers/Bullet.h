#ifndef BULLET_H
#define BULLET_H
#include "Entity.h"
#include <SFML/Graphics.hpp>

class Bullet : public Entity {
private:
  float velocity;

public:
  Bullet(float startX, float startY, float velocity);
  void update(sf::Time deltaTime);
  bool isOffScreen();
};

#endif
