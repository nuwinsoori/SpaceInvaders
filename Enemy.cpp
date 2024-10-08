#include "./Headers/Enemy.h"
#include "Headers/Global.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

// constructor defines all varibles.
Enemy::Enemy(float PosX, float PosY, const sf::Texture &texture)
    : EnemySpeed(60.0f), descendAmount(50.0f), pointValue(10), directon(1) {

  setPosition(PosX, PosY);
  sprite.setTexture(texture);
  sprite.scale(0.25f, 0.25f);
}

// function that make enemies move
void Enemy::move(sf::Time deltaTime) {
  // moves enemy
  sprite.move(EnemySpeed * directon * deltaTime.asSeconds(), 0);

  //moves enemy across screen or down
  for (auto &enemy : enemies) {
    if (enemy.getGlobalBounds().width >= SCREEN_WIDTH || enemy.getGlobalBounds() < 0) {
      for (auto &enemy : enemies) {
        enemy.move(0, descendAmount);
        directon = -1;
      }
    }

  //if enemy reaches certian place, game over
    if (sprite.getPosition().x == ENEMY_LIMIT){
      gameover();
    }
}

// function that makes enemies go down once move all way left or right.
void Enemy::descent() {
  sprite.move(0, descendAmount);
}

// function that makes the enemies change direction.
void Enemy::changeDirection() {
  direction = -directon; 
}

// function that checks if enemies have reached end of screen.
bool Enemy::reachedEndOfScreen() {

}
