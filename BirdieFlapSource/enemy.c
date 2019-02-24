#include "enemy.h"
#include "constants.h"
struct enemy_bird;  
struct vector2;
void enemy_bird_update(struct enemy_bird * enemy) {
	enemy->position.x -= enemy->horizontalSpeed;
	
	if(enemy->position.x < 0) {
		enemy->isActive = 0;
	}
	
}

