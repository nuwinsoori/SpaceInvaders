#ifndef PLAYER_H
#define PLAYER_H

#include "Global.h"
#include "bullet.h"
#include "entity.h"

class Player : public Entity {
protected:
  int lives;
  unsigned int playerSpeed;
  unsigned int score;
  float fireRate;
  bool shield;
  bool triple;
  bool rapid;
  std::vector<Bullet *> bullets;
  sf::Clock playerReloadTime;

public:
  Player();                       // Constructor
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
  sf::Vector2f getMiddleTop();
  void draw(sf::RenderWindow &window) override;
  bool getRapidActive();  // Checks if rapid fire is active
  void setShieldActive(); // Activates shield
  void setTripleActive(); // Activates triple shot
  void setRapidActive();  // Activates rapid fire
};

#endif
