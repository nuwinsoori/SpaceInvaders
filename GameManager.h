#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include<vector> 
#include<iostream> 
using namespace std;

#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"

class GameManager {
    protected:
        vector<Enemy> enemies; 
        vector<Bullet> bullets; 
        Player player; 
    public:
        void newLevel();
        void checkCollisions();
        void gameOver();


};


#endif