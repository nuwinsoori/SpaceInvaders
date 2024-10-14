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
  sprite->setPosition(SE_STARTING_POS);
  sprite->setScale(SE_SCALE, SE_SCALE);

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

SpecialEnemy::~SpecialEnemy() {
  delete this->sprite;
  delete this->texture;
  this->texture = nullptr;
  this->sprite = nullptr;
}

void SpecialEnemy::spawn() {
  float spawnChance = static_cast<float>(rand()) / RAND_MAX;
  if (!isActive && spawnChance < 0.002) {
    isActive = true;
    activeSound.setLoop(1);
    activeSound.play();
  }
}

void SpecialEnemy::move(sf::Time deltaTime) {
  if (isActive) {
    sprite->move(SE_SPEED * deltaTime.asSeconds(), 0);
    checkIfOffScreen();
  }
}

void SpecialEnemy::checkIfOffScreen() {
  if (sprite->getGlobalBounds().left >= SCREEN_WIDTH) {
    die(0);
  }
}

void SpecialEnemy::die(bool killed) {
  sprite->setPosition(SE_STARTING_POS);
  isActive = false;
  activeSound.setLoop(0);

  if (killed) {
    dieSound.play();
  }
}

void SpecialEnemy::draw(sf::RenderWindow &window) { window.draw(*sprite); }

int SpecialEnemy::getSEPoints() { return this->pointVal; }
