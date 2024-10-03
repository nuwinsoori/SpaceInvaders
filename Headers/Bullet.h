#ifndef BULLET_H
#define BULLET_H

class Bullet {
    public:
        enum class Owner {
            PLAYER,
            ENEMY
        };
    protected:
        Owner owner; 
        int bulletDirecton; 
        int bulletSpeed; 
    public:
        void move();
};

#endif