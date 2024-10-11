#ifndef GLOBAL_H
#define GLOBAL_H
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

const int WINDOW_WIDTH = 1200;  // Width in pixels
const int WINDOW_HEIGHT = 800;   // Height in pixels

const int FRAME_RATE = 120;
const float STARTING_X = 600.0f;
const float STARTING_Y = 715.0f;
const float PLAYER_SPEED = 300.0f;
const float PLAYER_FIRE_RATE = 0.75;
const float BULLET_VELOCITY = -500.0f;
const float SCREEN_WIDTH = 1200.0f;
const float SCREEN_HEIGHT = 800.0f;
const float ENEMY_LIMIT = 500.0f;
const int ENEMYROW = 5;
const int ENEMYCOL = 11;
const float ENEMYSTARTX = 20.f;
const float ENEMYSTARTY = 20.f;
const float ENEMYSPACINGX = 50.0f;
const float ENEMYSPACINGY = 50.0f;
const float ENEMY_SPEED = 1500.0f;
const float ENEMY_DESEND_AMOUNT = 20.0f;
const float ENEMY_MOVE_TIME = 0.5f;
const float SE_SPEED = 6000.0f;

//SPECAIL ENEMY VARS
const float SE_STARTING_X = 50.0f;
const float SE_STARTING_Y = 50.0f;
const float SE_SCALE = 0.15;

#endif
