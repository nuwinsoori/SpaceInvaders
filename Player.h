#ifndef PLAYER_H
#define PLAYER_H

#include "Enemy.h"
#include "Global.h"
#include "SpecialEnemy.h"
#include "bullet.h"
#include "entity.h"
#include <SFML/Audio.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class Player : public Entity {
protected:
  int lives;
  unsigned int playerSpeed;
  unsigned int score;
  unsigned int highScore;
  float fireRate;
  int shootingStyle;
  sf::Clock playerReloadTime, powerUpTime;
  sf::Font font;
  sf::Text scoreText;
  sf::Text livesText;
  sf::SoundBuffer shootBuffer, dieBuffer, shotEnemyBuffer;
  std::vector<PowerUp *> powerUpList;
  sf::Sound shootSound, dieSound, shotEnemySound;
  // sf::Sprite powerUpBar;
  // sf::Texture powerUpBarTexture;
  sf::RectangleShape powerUpbar;

public:
  Player(); // Constructor
  Player(int lives, float FireRate, int shootingStyle);
  ~Player();
  std::vector<Bullet *> bullets;
  void update(sf::Time deltaTime); // Moves the player
  void moveLeft(sf::Time deltaTime);
  void moveRight(sf::Time deltaTime);
  void setPlayerLives(int lives); // Sets player lives
  int getPlayerLives();           // Gets player lives
  float getFireRate();
  int getsShootingStyle();
  void setPlayerPos(float x, float y);
  sf::Vector2f getPlayerPos();
  void loseLife();               // Handles life loss
  void updateSprite();           // Updates the player's sprite
  bool isAlive();                // Checks if the player is still alive
  void setSpeed(float newSpeed); // Sets player's speed
  float getTop();                // Gets player's top position
  bool getTripleActive();        // Checks if triple shot is active
  void shoot() override;         // Handles shooting
  void deleteBullet(int index);  // deletes out of bounds bullets
  void collision(Enemy &enemy,
                 SpecialEnemy &specialenemy); // bullet collision check
  void updateScore(int points);
  void hit(Enemy &enemy);
  sf::Vector2f getMiddleTop();
  sf::Vector2f getLeftTop();
  sf::Vector2f getRightTop();
  void draw(sf::RenderWindow &window) override;
  void drawPowerUpBar(sf::RenderWindow &window);
  void normalShoot();
  void rapidFire();
  void tripleShot();
  void extraLife();
  size_t getBulletCount();
  sf::FloatRect getDimensions() { return sprite->getGlobalBounds(); }
  void updatePowerUps(sf::Time deltaTime);
  void collectPowerUp(int powerType);
  void drawPowerUps(sf::RenderWindow &window);
};

#endif
