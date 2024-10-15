#include "test.h"
#include "entity.h"
#include "bullet.h"
#include "Enemy.h"
#include "Global.h"
#include "Menu.h"
#include "Player.h"
#include "PowerUp.h"
#include "SpecialEnemy.h"
#include <SFML/Graphics/Rect.hpp>

#include"iostream" 

using namespace std; 

int main() {
    int numPlayerPass = playerTests();
    int numEnemyPass = enemyTests();
    
    if(numPlayerPass == 3) {
        cout << "SUCCESS: all player tests passed." << endl;   
    } else {
        cout << numPlayerPass << "out of 3 player tests have passed." << endl;
    }

    if(numEnemyPass == 3) {
        cout << "SUCCESS: all enemy tests passed."; 
    } else {
        cout << numEnemyPass << "out of 3 enemy tests have passed." << endl;
    }

    return 0;
}

int playerTests() {
    int Ppassed = 0;

    //testing player initalisation
    //lives: 3, fireRate: 0.75, Shooting Style: Normalshooting
    Player *player = new Player(3, 0.75, 1);
    if(player->getPlayerLives() == 3 && player->getFireRate() == 0.75 && player->getsShootingStyle() == NORMAL_SHOOTING) {
        cout << "PASSED: player intialisation test" << endl; 
        Ppassed++;
    } else {
        cout << "FAILED: player intialisation test" << endl; 
    }

    //testing player movement 
    player->setPlayerPos(STARTING_X, STARTING_Y);
    player->move(sf::seconds(1.0f)); 
    if(player->getPlayerPos().x != STARTING_X) {
        cout << "PASSED: player movement test" << endl;
        Ppassed++;
    } else {
        cout << "FAILED: player movement test" << endl;
    }

    //testing player shooting 
    size_t initialBulletSize = player->getBulletCount();
    player->shoot();
    if(player->getBulletCount() > initialBulletSize) {
        cout << "PASSED: player shooting test" << endl;
        Ppassed++;
    } else {
        cout << "FAILED: player shooting test" << endl;
    }

    delete player; 

    return Ppassed; 

    }

    int enemyTests() {
        int Epassed = 0; 

        //create getEnemyPosition
        //enemy initialisation test
        Enemy *enemy = new Enemy(ENEMYSTARTX, ENEMYSTARTY, 1);
        if (enemy->getEnemyPos().x == ENEMYSTARTX && enemy->getEnemyPos().y == ENEMYSTARTY && enemy->getPoints() == 40) {
            cout << "PASSED: enemy initialisation test" << endl;
            Epassed++;
        } else {
            cout << "FAILED: enemy initialisation test" << endl;
        }

        //enemy movement test
        sf::Time deltaTime = sf::seconds(1.0f);
        sf::Vector2f initialPos = enemy->getEnemyPos();
        enemy->move(deltaTime, enemy);
        if(initialPos != enemy->getEnemyPos()) {
            cout << "PASSED: enemy movement test" <<endl;
            Epassed++;
        } else {
            cout << "FAILED: enemy movement test" << endl;
        }

        //inilising another enemy, calling constructor that calls inilise enemies
        Enemy *enemy1 = new Enemy();
        enemy1->clearEnemies();
        enemy1->move(sf::seconds(1.0f), enemy); 
        if (enemy1->getEnemyCount() > 0) {
            cout << "PASSED: enemy respawn test" << endl; 
            Epassed++;
        } else {
            cout << "FAILED: enemy respawn test" << endl;
        }


        delete enemy;
        delete enemy1;

        return Epassed;

    }

