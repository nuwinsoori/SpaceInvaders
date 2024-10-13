#ifndef ENEMY_H
#define ENEMY_H
#include "bullet.h"
#include "entity.h"
#include <SFML/Graphics/Rect.hpp>

class Enemy : public Entity {
protected:
  unsigned int pointValue;
  float chanceToShoot;
  int direction;
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
  void move(sf::Time deltaTime);
  void switchFrame();
  void descent();
  void changeDirection();
  bool willReachEndOfScreen(sf::Time deltaTime);
  void update(sf::Time deltaTime);
  void initializeEnemies();
  void draw(sf::RenderWindow &window) override;
  void shoot() override; // Handles shooting
  void die();
  int getPoints();
  void deleteBullet(int index);
  void deleteOutOfBoundsBullets();
  int getEnemyCount();
  sf::FloatRect getDimensions();
};

#endif
