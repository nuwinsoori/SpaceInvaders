#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Entity {
protected:
  sf::Vector2f position;
  unsigned int health;
  float width;
  float height;
  bool alive;
  string colour;
  sf::Sprite sprite;
  sf::Texture texture;

public:
  sf::FloatRect getDimensions();
  void setPosition(float x, float y);
  bool checkCollision(Entity obj);
  virtual void shoot();
  void draw(sf::RenderWindow &window);
};

#endif
