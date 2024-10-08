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

  // moves enemy across screen or down
  if (sprite.getPosition().x + sprite.getGlobalBounds().width >= SCREEN_WIDTH) {
    sprite.move(0, descendAmount);
    directon = -1;

  } else if (sprite.getPosition().x <= 0) {
    sprite.move(0, descendAmount);
    directon = 1;
    
  }

  // if enemy reaches certian place, game over
  //   if (sprite.getPosition().x == ENEMY_LIMIT){
  //     gameover();
  //   }
}

// function that makes enemies go down once move all way left or right.
void Enemy::descent() {}

// function that makes the enemies change direction.
void Enemy::changeDirection() {}

// function that checks if enemies have reached end of screen.
bool Enemy::reachedEndOfScreen() {}
