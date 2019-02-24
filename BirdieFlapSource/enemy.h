#ifndef ENEMY
#define ENEMY
#include <stdint.h> 


struct vector2{
   float x;
   float y;
};
struct enemy_bird {
   char isActive;
   float horizontalSpeed;
   struct vector2 position;
   uint8_t enemySprite;
};

void enemy_bird_update(struct enemy_bird * enemy);
#endif