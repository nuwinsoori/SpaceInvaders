#ifndef GLOBAL_H
#define GLOBAL_H
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

//defines all out varibles 

const int WINDOW_WIDTH = 1200; // Width in pixels
const int WINDOW_HEIGHT = 800; // Height in pixels

const int FRAME_RATE = 120;
const float STARTING_X = 600.0f;
const float STARTING_Y = 715.0f;
const float PLAYER_SPEED = 300.0f;
const float PLAYER_FIRE_RATE = 0.05;
const float TRIPLE_FIRE_RATE = 0.9;
const float RAPID_FIRE_RATE = 0.2;
const float BULLET_VELOCITY = -500.0f;
const float SCREEN_WIDTH = 1200.0f;
const float SCREEN_HEIGHT = 800.0f;
const float ENEMY_LIMIT = 500.0f;
const int ENEMYROW = 5;
const int ENEMYCOL = 11;
const float ENEMYSTARTX = 20.f;
const float ENEMYSTARTY = 130.f;
const float ENEMYSPACINGX = 80.0f;
const float ENEMYSPACINGY = 50.0f;
const float ENEMY_SPEED = 1500.0f;
const float ENEMY_DESEND_AMOUNT = 20.0f;
const float ENEMY_MOVE_TIME = 0.5f;
const float ENEMY_STOP_DESCENT = 500.0f;

// SPECIAL ENEMY VARS
const float SE_SPEED = 200.0f;
const sf::Vector2f SE_STARTING_POS(-100.0f, 50.0f);
const float SE_SCALE = 0.12;
const float SE_SPAWN_CHANCE = 0.0005;
const float SE_SPAWN_HIGH = 0.002;

// POWERUPS VARIABLES
const float POWERUP_SPEED = 500.0f;
enum power { HEALTH, TRIPLE, RAPID };
enum shootingStyle { NORMAL_SHOOTING, TRIPLE_SHOOTING, RAPID_SHOOTING };
#endif
