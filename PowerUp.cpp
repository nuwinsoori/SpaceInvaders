#include "PowerUp.h"
#include "Global.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

// PowerUp::PowerUp(sf::Vector2f enemyPosition) {
//   healthPower = sf::IntRect(0, 0, 15, 13);
//   tripleShoot = sf::IntRect(15, 0, 15, 13);
//   rapidShoot = sf::IntRect(30, 0, 15, 13);
//
//   texture = new sf::Texture;
//   sprite = new sf::Sprite;
//
//   if (!texture->loadFromFile("./Sprites/powerUps.png")) {
//     std::cout << "ERROR: loading sprite (powerups)" << std::endl;
//   }
//   sprite->setTexture(*texture);
// }

PowerUp::PowerUp(sf::Vector2f enemyPosition) {
  healthPower = sf::IntRect(0, 0, 15, 13);
  tripleShoot = sf::IntRect(15, 0, 15, 13);
  rapidShoot = sf::IntRect(30, 0, 15, 13);

  if (!texture.loadFromFile("./Sprites/powerUps.png")) {
    std::cout << "ERROR: loading sprite (powerups)" << std::endl;
  }
  sprite.setTexture(texture);
  sprite.setScale(3.0f, 3.0f);

  // Initialize random seed based on current time
  std::srand(static_cast<unsigned>(std::time(0)));

  // set location as enemies
  sprite.setPosition(enemyPosition);

  // Generate a random number between 0 and 2 and cast it to the enum type
  power randomPower = static_cast<power>(std::rand() % 3);

  // based on the random number chooses type of powerup
  switch (randomPower) {
  case HEALTH:
    sprite.setTextureRect(healthPower);
    rolledPowerup = HEALTH;
    break;
  case TRIPLE:
    sprite.setTextureRect(tripleShoot);
    rolledPowerup = TRIPLE;
    break;
  case RAPID:
    sprite.setTextureRect(rapidShoot);
    rolledPowerup = RAPID;
    break;
  }
}

void PowerUp::hide() {}

// draws powerups
void PowerUp::draw(sf::RenderWindow &window) { window.draw(sprite); }

// allows powerups to move (decend)
void PowerUp::move(sf::Time deltaTime) {
  sprite.move(0, POWERUP_SPEED * deltaTime.asSeconds());
}

// check if any part of powerup if in game window
bool PowerUp::inBounds() {
  return (sprite.getGlobalBounds().top <= SCREEN_HEIGHT);
}

// returns rolled powerup
int PowerUp::getType() { return rolledPowerup; }

// powerup destructor
PowerUp::~PowerUp() {}
