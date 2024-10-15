#ifndef ENEMY_H
#define ENEMY_H
#include "bullet.h"
#include "entity.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Rect.hpp>

class Enemy : public Entity {
protected:
  unsigned int pointValue;
  float chanceToShoot;
  int direction;
  int respawnedCount; 
  sf::Clock enemyMoveTime;
  sf::IntRect frame1, frame2;
  bool isFrame1;

public:
  std::vector<Bullet *> bullets;
  std::vector<Enemy *> enemies;
  Enemy();
  ~Enemy();
  void drawAll(sf::RenderWindow &window);
  Enemy(float PosX, float PosY, int position);
  void move(sf::Time deltaTime, Enemy &enemy);
  void switchFrame();
  void descent();
  void changeDirection();
  bool willReachEndOfScreen(sf::Time deltaTime);
  void update(sf::Time deltaTime);
  void initializeEnemies();
  void draw(sf::RenderWindow &window) override;
  void shoot() override; // Handles shooting
  void die();
  void setRespawnedCounter();
  int getRespawnedCount();
  int getPoints();
  void deleteBullet(int index);
  void deleteOutOfBoundsBullets();
  int getEnemyCount();
  sf::FloatRect getDimensions();
};

#endif
