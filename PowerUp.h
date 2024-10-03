#ifndef POWERUP_H 
#define POWERUP_H

class PowerUp {
    public:
        enum class PowerUpType {
            TRIPLE_SHOOT,
            SHIELD,
            RAPID_FIRE
        };
    protected:
        PowerUpType type;
        float duration; 
        bool active; 
    public:
        void active();
        void deactive(); 
};


#endif