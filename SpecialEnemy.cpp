#include "SpecialEnemy.h"
#include "Enemy.h"
#include "entity.h"
#include "Global.h"

SpecialEnemy::SpecialEnemy() : SEdirection(1), pointVal(50) {
    texture = new sf::Texture;
    sprite = new sf::Sprite; 
    texture->loadFromFile("./Sprites/21-214046_space-invaders-ufo-shaped-sticker-space-invaders-sprites-png.png");
    sprite->setTexture(*texture);
    sprite->setPosition(SE_STARTING_X, SE_STARTING_Y);
    //-sprite.getGlobalBounds().width ----> replace x to have sprite off screen
    sprite->setScale(SE_SCALE, SE_SCALE);
}

bool SpecialEnemy::HasReachedTarget(sf::Vector2f target) {
    return (sprite->getPosition().x == target.x);
}


// , sf::RenderWindow &window
void SpecialEnemy::move(sf::Time deltaTime) {
    float lastMove = SEMoveTime.getElapsedTime().asSeconds();
    float chanceSEMoves = static_cast<float>(rand())/RAND_MAX;
    bool movingSE; 

    if (chanceSEMoves < 0.002) {
        movingSE = true; 
    } else if (WINDOW_WIDTH + sprite->getGlobalBounds().width ) {
        movingSE = false; 
    }

    // sf::Vector2f target; 
    // if (SEdirection == 1) {
    //     target.x = -sprite->getGlobalBounds().width;
    // } else if (SEdirection == -1) {
    //     target.x = window.getSize().x + sprite->getGlobalBounds().width;
    // }

      if(lastMove >= ENEMY_MOVE_TIME) {
        if (movingSE == true) {
        sprite->move(SE_SPEED * SEdirection * deltaTime.asSeconds(), 0.0f);
        SEMoveTime.restart();
        }
    } 
    // if(lastMove >= ENEMY_MOVE_TIME) {
    //     if (chanceSEMoves < 0.002 && !HasReachedTarget(target.x)) {
    //     sprite->move(SE_SPEED * SEdirection * deltaTime.asSeconds(), 0.0f);
    //     SEMoveTime.restart();
    //     }
    // } 
    
    // if (sprite->getGlobalBounds().left + sprite->getGlobalBounds().width < 0) {
    //     SEdirection = 1; 
    // } else if (sprite->getGlobalBounds().left > window.getSize().x) {
    //     SEdirection = -1; 
    // }

 
}

bool SpecialEnemy::checkIfOffScreen() {
    
}

// void Enemy::update(sf::Time deltaTime){

// }


void SpecialEnemy::draw(sf::RenderWindow &window) {
    window.draw(*sprite);
}


// void SpecialEnemy::DropPowerUp() {

// }

// void Enemy::die() {

// }
