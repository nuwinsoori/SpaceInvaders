#ifndef SPECIALENEMY_H
#define SPECIALENEMY_H

#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

class SpecialEnemy : public Enemy {
private:
  unsigned int pointVal;
  sf::Sprite *sprite;
  sf::Texture *texture;
  sf::Clock SEMoveTime;
  bool isActive;

public:
  SpecialEnemy();
  ~SpecialEnemy();
  void move(sf::Time deltaTime);
  bool HasReachedTarget(sf::Vector2f target, sf::RenderWindow &window);
  bool checkIfOffScreen();
  int getSEPoints();
  void update(sf::Time deltaTime);
  void spawn();
  void draw(sf::RenderWindow &window) override;
  void DropPowerUp();
  void die();
  sf::FloatRect getDimensions() { return sprite->getGlobalBounds(); }
};

#endif
