#ifndef ENEMY
#define ENEMY
#include "bird.h"
void update_main_character(struct bird * mainCharacter, int deltaTime);
void enemy_bird_update(struct bird * enemy, int deltaTime);
#endif
