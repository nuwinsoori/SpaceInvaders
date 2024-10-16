#include "bullet.h"
#include "Global.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

// bullet constructor that defines values needed for bullets
Bullet::Bullet(sf::Vector2f position, bool rotate) {
  velocity = BULLET_VELOCITY;
  sprite = new sf::Sprite;
  texture = new sf::Texture;
  // loads in sprite and texture
  texture->loadFromFile("./Sprites/bullet.png");
  sprite->setTexture(*texture);
  sprite->setPosition(position);
  sprite->setOrigin(sprite->getLocalBounds().width / 2,
                    sprite->getLocalBounds().height / 2);
  sprite->setScale(0.5f, 0.5f);
  if (rotate == true) {
    // enemies rotate so inverse velocity and change rotation of bullet
    velocity = -BULLET_VELOCITY;
    sprite->rotate(180);
  }
}

// bullet destructor
Bullet::~Bullet() {
  delete this->sprite;
  delete this->texture;
  this->texture = nullptr;
  this->sprite = nullptr;
}

// checks if bullet if off screen
bool Bullet::offScreen() {
  sf::FloatRect bulletBounds = sprite->getGlobalBounds();
  return (bulletBounds.top + bulletBounds.height < 0 ||
          bulletBounds.top > SCREEN_HEIGHT);
}

// moves the bullet
void Bullet::update(sf::Time deltaTime) {
  sprite->move(0, velocity * deltaTime.asSeconds());
}

// draws bullets in the game window
void Bullet::draw(sf::RenderWindow &window) { window.draw(*sprite); }
