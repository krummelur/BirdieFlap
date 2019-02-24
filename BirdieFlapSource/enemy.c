#include "enemy.h"
struct enemy_bird;  
struct vector2;
void enemy_bird_update(struct enemy_bird * enemy) {
	enemy->position.y -= enemy->horizontalSpeed;
}

