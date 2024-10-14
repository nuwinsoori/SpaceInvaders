#include "SpecialEnemy.h"
#include "Enemy.h"
#include "Global.h"
#include "entity.h"

SpecialEnemy::SpecialEnemy() : pointVal(100), isActive(false) {
  texture = new sf::Texture;
  sprite = new sf::Sprite;
  texture->loadFromFile("./Sprites/"
                        "21-214046_space-invaders-ufo-shaped-sticker-space-"
                        "invaders-sprites-png.png");
  sprite->setTexture(*texture);
  sprite->setPosition(SE_STARTING_X, SE_STARTING_Y);
  sprite->setScale(SE_SCALE, SE_SCALE);
}

SpecialEnemy::~SpecialEnemy() {
  delete this->sprite;
  delete this->texture;
  this->texture = nullptr;
  this->sprite = nullptr;
}

void SpecialEnemy::spawn() {
  float spawnChance = static_cast<float>(rand()) / RAND_MAX;
  if (spawnChance < 0.002) {
    isActive = true;
    std::cout << "active" << std::endl;
  }
}

void SpecialEnemy::move(sf::Time deltaTime) {
  if (isActive) {
    sprite->move(SE_SPEED * deltaTime.asSeconds(), 0);
  }
}

bool SpecialEnemy::checkIfOffScreen() {}

void SpecialEnemy::draw(sf::RenderWindow &window) { window.draw(*sprite); }

int SpecialEnemy::getSEPoints() { return this->pointVal; }
