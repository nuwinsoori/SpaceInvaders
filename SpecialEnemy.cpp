#include "SpecialEnemy.h"
#include "Global.h"
#include "PowerUp.h"

SpecialEnemy::SpecialEnemy() : pointVal(100), isActive(false) {
  texture.loadFromFile("./Sprites/"
                       "21-214046_space-invaders-ufo-shaped-sticker-space-"
                       "invaders-sprites-png.png");
  sprite.setTexture(texture);
  sprite.setPosition(SE_STARTING_POS);
  sprite.setScale(SE_SCALE, SE_SCALE);

  // load sounds
  if (!dieBuffer.loadFromFile("./Sounds/invaderkilled.wav")) {
    std::cout << "ERROR: loading sound (SE)" << std::endl;
  }
  if (!activeBuffer.loadFromFile("./Sounds/ufoActive.wav")) {
    std::cout << "ERROR: loading sound (SE)" << std::endl;
  }

  dieSound.setBuffer(dieBuffer);
  activeSound.setBuffer(activeBuffer);
  activeSound.setLoop(1);
}

SpecialEnemy::~SpecialEnemy() {}

void SpecialEnemy::spawn() {
  float spawnChance = static_cast<float>(rand()) / RAND_MAX;
  if (!isActive && spawnChance < SE_SPAWN_CHANCE) {
    isActive = true;
    activeSound.setLoop(1);
    activeSound.play();
  }
}

void SpecialEnemy::move(sf::Time deltaTime) {
  if (isActive) {
    sprite.move(SE_SPEED * deltaTime.asSeconds(), 0);
    checkIfOffScreen();
  }
}

void SpecialEnemy::checkIfOffScreen() {
  if (sprite.getGlobalBounds().left >= SCREEN_WIDTH) {
    die(0);
  }
}

// void SpecialEnemy::die() {
//   sprite->setPosition(SE_STARTING_POS);
//   isActive = false;
//   activeSound.setLoop(0);
// }

PowerUp *SpecialEnemy::die(bool killed) {
  isActive = false;
  activeSound.setLoop(0);

  if (killed) {
    dieSound.play();
    return DropPowerUp();
  }
  sprite.setPosition(SE_STARTING_POS);
  return nullptr;
}

// TODO: CHANGE THIS
PowerUp *SpecialEnemy::DropPowerUp() { return new PowerUp(dropLocation()); }

sf::Vector2f SpecialEnemy::dropLocation() {
  float x = sprite.getPosition().x;
  float y = sprite.getPosition().y;
  return sf::Vector2f(x, y);
}

// sf::Vector2f SpecialEnemy::dropLocation() { return sf::Vector2f(600.0f,
// 0.0f); }

void SpecialEnemy::draw(sf::RenderWindow &window) { window.draw(sprite); }

int SpecialEnemy::getSEPoints() { return this->pointVal; }
void SpecialEnemy::goStart() { sprite.setPosition(SE_STARTING_POS); }
