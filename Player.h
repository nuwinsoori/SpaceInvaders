#ifndef PLAYER_H
#define PLAYER_H

#include "Enemy.h"
#include "Global.h"
#include "bullet.h"
#include "entity.h"
#include "SpecialEnemy.h"
#include <SFML/Audio.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class Player : public Entity {
protected:
  int lives;
  unsigned int playerSpeed;
  unsigned int score;
  unsigned int highScore;
  float fireRate;
  bool shield;
  bool triple;
  bool rapid;
  sf::Clock playerReloadTime;
  sf::Font font;
  sf::Text scoreText;
  sf::Text livesText;
  sf::SoundBuffer shootBuffer, dieBuffer, shotEnemyBuffer;
  sf::Sound shootSound, dieSound, shotEnemySound;

public:
  Player(); // Constructor
  std::vector<Bullet *> bullets;
  void move(sf::Time deltaTime);  // Moves the player
  void setPlayerLives(int lives); // Sets player lives
  int getPlayerLives();           // Gets player lives
  void loseLife();                // Handles life loss
  void updateSprite();            // Updates the player's sprite
  bool isAlive();                 // Checks if the player is still alive
  void setSpeed(float newSpeed);  // Sets player's speed
  float getTop();                 // Gets player's top position
  bool getShieldActive();         // Checks if shield is active
  bool getTripleActive();         // Checks if triple shot is active
  void shoot() override;          // Handles shooting
  void deleteBullet(int index);   // deletes out of bounds bullets
  void collision(Enemy &enemy, SpecialEnemy &specialenemy);   // bullet collision check
  void updateScore(int points);
  void hit(Enemy &enemy);
  sf::Vector2f getMiddleTop();
  void draw(sf::RenderWindow &window) override;
  bool getRapidActive();  // Checks if rapid fire is active
  void setShieldActive(); // Activates shield
  void setTripleActive(); // Activates triple shot
  void setRapidActive();  // Activates rapid fire
  sf::FloatRect getDimensions() { return sprite->getGlobalBounds(); }
};

#endif
