#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

using namespace std;

class Entity {
protected:
  sf::Vector2f position;
  unsigned int lives;
  float width;
  float height;
  bool alive;
  sf::Sprite *sprite;
  sf::Texture *texture;
  float speed;

public:
  virtual void shoot() = 0;
  virtual void draw(sf::RenderWindow &window) = 0;
};

#endif
