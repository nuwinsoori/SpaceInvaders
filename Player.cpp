#include "Player.h"
#include "Enemy.h"
#include "Global.h"
#include "SpecialEnemy.h"
#include "bullet.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

// Player Constructor
Player::Player()
    : lives(3), playerSpeed(PLAYER_SPEED), score(0), fireRate(PLAYER_FIRE_RATE), shootingStyle(NORMAL_SHOOTING) {
  texture = new sf::Texture;
  sprite = new sf::Sprite;
  texture->loadFromFile("./Sprites/player.png");
  sprite->setTexture(*texture);
  sprite->setPosition(STARTING_X, STARTING_Y);

  // load sounds for the player 
  if (!dieBuffer.loadFromFile("./Sounds/explosion.wav")) {
    std::cout << "ERROR: loading sound" << std::endl;
  }
  if (!shootBuffer.loadFromFile("./Sounds/shoot.wav")) {
    std::cout << "ERROR: loading sound" << std::endl;
  }
  if (!shotEnemyBuffer.loadFromFile("./Sounds/invaderkilled.wav")) {
    std::cout << "ERROR: loading sound" << std::endl;
  }

  dieSound.setBuffer(dieBuffer);
  shootSound.setBuffer(shootBuffer);
  shotEnemySound.setBuffer(shotEnemyBuffer);

  // loads highscore
  std::ifstream file("scores.txt");
  if (file.is_open()) {
    std::string line;
    int lineNumber = 0;

    // Read lines until the second line is reached
    while (std::getline(file, line)) {
      lineNumber++;
      if (lineNumber == 2) {
        highScore = std::stoi(line); // Convert string to integer
        break;
      }
    }
    file.close();
  } else {
    std::cout << "Unable to open file!" << std::endl;
  }

  font.loadFromFile("./pixelFont.ttf");

  // showing score
  scoreText.setFont(font);
  scoreText.setCharacterSize(24);           // Size in pixels
  scoreText.setFillColor(sf::Color::White); // Color of the text
  scoreText.setPosition(10, 10); // Position on the screen (top-left corner)
  scoreText.setString("Score: " + std::to_string(score));

  // showing lives
  livesText.setFont(font);
  livesText.setCharacterSize(24);           // Size in pixels
  livesText.setFillColor(sf::Color::Green); // Color of the text
  livesText.setPosition(1075,
                        10); // Position on the screen (top-left corner)
  livesText.setString("Lives: " + std::to_string(lives));
}

//parameterised constructor 
Player::Player(int lives, float FireRate, int shootingStyle) {
  this->lives = lives;
  this->fireRate = fireRate;
  this->shootingStyle = shootingStyle;
}


//player destructor 
Player::~Player() {
  //deletes players bullets 
  for (auto &bullet : bullets) {
    delete bullet;
  }
  bullets.clear();

  //deletes powerups 
  for (PowerUp *powerup : powerUpList) {
    delete powerup;
  }
  powerUpList.clear();
}

// Move method
void Player::move(sf::Time deltaTime) {
  sf::FloatRect boundary = sprite->getGlobalBounds();

  //moves player left if left arrow key pressed 
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    //ensures player doesnt go off game window
    if (boundary.left > 0) {
      sprite->move(-(playerSpeed * deltaTime.asSeconds()), 0.0f);
    }
  }

  //move player right if right arrow key pressed 
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
     //ensures player doesnt go off game window
    if (boundary.left + boundary.width < SCREEN_WIDTH) {
      sprite->move(playerSpeed * deltaTime.asSeconds(), 0.0f);
    }
  }

  //undates players bullets 
  for (auto &bullet : bullets) {
    bullet->update(deltaTime);
  }

  //deletes off screen plauyer bullets 
  if (!bullets.empty() && bullets.at(0)->offScreen()) {
    deleteBullet(0);
  }
}

//handles power ups in player 
void Player::updatePowerUps(sf::Time deltaTime) {
  for (size_t i = 0; i < powerUpList.size(); i++) {
    PowerUp *powerUp = powerUpList[i];
    powerUp->move(deltaTime);

    // Check for collision with the player
    if (getDimensions().intersects(powerUp->getDimensions())) {
      collectPowerUp(powerUp->getType());
      // delete from vector
      delete powerUp;
      powerUpList.erase(powerUpList.begin() + i);
      i--;
    }
    // delete from vector if out of bounds
    if (!powerUp->inBounds()) {
      delete powerUp;
      powerUpList.erase(powerUpList.begin() + i);
      i--;
    }
  }
}

//draws power ups in game window 
void Player::drawPowerUps(sf::RenderWindow &window) {
  for (PowerUp *powerUp : powerUpList) {
    window.draw(powerUp->getSprite());
  }
}

//set player x and y pos
// void setPlayerPos(float x, float y) {
//   sprite->setPosition(x, y);
// }

// //returns the player x and y pos
// sf::Vector2f getPlayerPos() {
//   return sprite->getPosition();
// }

//switchcase for different instances of powerup 
void Player::collectPowerUp(int powerType) {
  switch (powerType) {
  case HEALTH:
    extraLife();
    break;
  case TRIPLE:
    shootingStyle = TRIPLE;
    break;
  case RAPID:
    shootingStyle = RAPID_SHOOTING;
    break;
  }
}

//gets the middle top of the player sprite 
sf::Vector2f Player::getMiddleTop() {
  sf::Vector2f center;
  center.x =
      (sprite->getGlobalBounds().left + (sprite->getGlobalBounds().width / 2));
  center.y = sprite->getGlobalBounds().top;
  return center;
}

//gets the left top of the player sprite 
sf::Vector2f Player::getLeftTop() {
  sf::Vector2f left;
  left.x = (sprite->getGlobalBounds().left);
  left.y = sprite->getGlobalBounds().top;
  return left;
}

//gets the right top of the player sprite 
sf::Vector2f Player::getRightTop() {
  sf::Vector2f right;
  right.x = (sprite->getGlobalBounds().left + sprite->getGlobalBounds().width);
  right.y = sprite->getGlobalBounds().top;
  return right;
}

// Shooting methods
void Player::shoot() {
  switch (shootingStyle) {
  case NORMAL_SHOOTING:
    normalShoot();
    break;
  case TRIPLE_SHOOTING:
    tripleShot();
    break;
  case RAPID_SHOOTING:
    rapidFire();
    break;
  }
}

// this is the players normal shooting method 
void Player::normalShoot() {
  // get time since player last shot bullet
  float timeSinceShot = playerReloadTime.getElapsedTime().asSeconds();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
      timeSinceShot >= PLAYER_FIRE_RATE) {
    Bullet *bullet = new Bullet(getMiddleTop(), false);
    bullets.push_back(bullet);
    shootSound.play();
    playerReloadTime.restart();
  }
}

//this defines shooting with rapid fire on 
void Player::rapidFire() {
  // get time since player last shot bullet
  float timeSinceShot = playerReloadTime.getElapsedTime().asSeconds();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
      timeSinceShot >= RAPID_FIRE_RATE) {
    Bullet *bullet = new Bullet(getMiddleTop(), false);
    bullets.push_back(bullet);
    shootSound.play();
    playerReloadTime.restart();
  }
}

//this defines shooting with triple shot
void Player::tripleShot() {
  // get time since player last shot bullet
  float timeSinceShot = playerReloadTime.getElapsedTime().asSeconds();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
      timeSinceShot >= TRIPLE_FIRE_RATE) {
    Bullet *middleBullet = new Bullet(getMiddleTop(), false);
    Bullet *leftBullet = new Bullet(getLeftTop(), false);
    Bullet *rightBullet = new Bullet(getRightTop(), false);

    bullets.push_back(middleBullet);
    bullets.push_back(leftBullet);
    bullets.push_back(rightBullet);

    shootSound.play();
    playerReloadTime.restart();
  }
}

//defines extra life power up
void Player::extraLife() {
  lives++;
  livesText.setString("Lives: " + std::to_string(lives));
}

//funtion that deltes player bullets 
void Player::deleteBullet(int index) {
  if (index >= 0 && index < bullets.size()) {
    delete bullets.at(index);
    bullets.erase(bullets.begin() + index);
  }
}

//checks if player bullets have collided with any enemies & special enemies 
void Player::collision(Enemy &enemy, SpecialEnemy &specialenemy) {
  for (int i = 0; i < bullets.size(); i++) {
    Bullet *currentBullet = bullets.at(i);
    if (currentBullet) { // makes sure is a valid pointer

      // collision with special enemy
      if (currentBullet->getDimensions().intersects(
              specialenemy.getDimensions())) {
        PowerUp *newPowerUp = specialenemy.die(true); // die() returns a PowerUp
        specialenemy.goStart();                       // goes out of view
        if (newPowerUp) {
          powerUpList.push_back(newPowerUp); // Add to activePowerUps vector
        }
        updateScore(specialenemy.getSEPoints());
        deleteBullet(i);
        i--;
        break;
      }

      //collision with enemy 
      for (int j = 0; j < enemy.getEnemyCount(); j++) {
        Enemy *currentEnemy = enemy.enemies.at(j);
        if (currentEnemy) { // Ensure it's a valid pointer

          // Check for collision between the bullet and the current enemy
          if (currentBullet->getDimensions().intersects(
                  currentEnemy->getDimensions())) {

            // kill the hit enemy and update points
            updateScore(currentEnemy->getPoints());
            enemy.enemies.erase(enemy.enemies.begin() + j);
            delete currentEnemy;

            // play sound
            shotEnemySound.play();

            // delete bullet and adjust index
            deleteBullet(i);
            i--;
            break;
          }
        }
      }
    }
  }
}

//updates the score 
void Player::updateScore(int points) {
  this->score += points;
  scoreText.setString("Score: " + std::to_string(score)); // update score text
}

//checks if player has been hit with an enemies bullet 
void Player::hit(Enemy &enemy) {
  for (int i = 0; i < enemy.bullets.size();) {
    Bullet *currentBullet = enemy.bullets.at(i);
    if (currentBullet->getDimensions().intersects(getDimensions())) {
      loseLife();
      enemy.deleteBullet(i);
      dieSound.play();
    } else {
      i++; // Only increment i if no deletion occurred
    }
  }
}

// Losing life method
void Player::loseLife() {
  lives -= 1;
  livesText.setString("Lives: " + std::to_string(lives));
  if (isAlive()) {
    updateSprite();
  } else {
    // Read highscore from "scores.txt"
    std::ifstream infile("scores.txt");
    if (infile) {
      int prev_score;
      infile >> prev_score >> highScore;
    }
    infile.close();

    // Update highscore if current_score is greater
    if (score > highScore) {
      highScore = score;
    }

    // Write current_score and highscore back to "scores.txt"
    std::ofstream outfile("scores.txt");
    outfile << score << "\n" << highScore << "\n";
    outfile.close();
  }
}

//cjecks if player is still alive 
bool Player::isAlive() {
  if (lives > 0) {
    return true;
  } else {
    return false;
  }
}

// Update sprite method
void Player::updateSprite() {
  std::string newSprite;
  if (lives >= 3) {
    livesText.setFillColor(sf::Color::Green);
    newSprite = "./Sprites/player.png";
  } else if (lives == 2) {
    livesText.setFillColor(sf::Color::Yellow);
    newSprite = "./Sprites/player(2livesleft).png";
  } else if (lives == 1) {
    livesText.setFillColor(sf::Color::Red);
    newSprite = "./Sprites/player(1lifeleft).png";
  } else {
    std::cout << "ERROR: Should be dead" << std::endl;
    return;
  }

  if (!texture->loadFromFile(newSprite)) {
    std::cout << "Error loading player texture!" << std::endl;
  }
  sprite->setTexture(*texture); // set texture to new sprite
}

//draws player, its bullets, and the score. 
void Player::draw(sf::RenderWindow &window) {
  for (auto &bullet : bullets) {
    bullet->draw(window);
  }
  window.draw(*sprite);
  window.draw(scoreText);
  window.draw(livesText);
};

//setter for lives 
void Player::setPlayerLives(int lives) {
  this->lives = lives;
}

//returns player lives 
int Player::getPlayerLives() {
  return lives; 
}

//gets player fireRate 
float Player::getFireRate() {
  return fireRate;
}

//returns player shooting style 
int Player::getsShootingStyle() {
  if(shootingStyle == 1) {
    return NORMAL_SHOOTING; 
  } else if (shootingStyle == 2) {
    return TRIPLE_SHOOTING;
  } else if (shootingStyle == 3) {
    return RAPID_SHOOTING; 
  }
  return 0;
}

//returns size of bullet vector
size_t Player::getBulletCount() {
  return bullets.size(); 
}

