#include "./Headers/Entity.h"
#include <SFML/Graphics.hpp>

sf::FloatRect Entity::getDimensions() { return sprite.getGlobalBounds(); }
bool Entity::checkCollision(Entity obj) {
  if (this->getDimensions().intersects(obj.getDimensions())) {
    return true;
  }
  return false;
}

sf::Vector2f Entity::getPosition() { return sprite.getPosition(); }
void Entity::shoot() { std::cout << ("This should get overridden"); }
void Entity::setPosition(float x, float y) { sprite.setPosition(x, y); }
void Entity::draw(sf::RenderWindow &window) { window.draw(sprite); }
