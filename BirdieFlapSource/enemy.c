#include "enemy.h"
#include "constants.h"
struct enemy_bird;
struct vector2;
void enemy_bird_update(struct bird * enemy) {
	enemy->position.x -= enemy->horizontalSpeed;

	if(enemy->position.x < 0) {
		enemy->isActive = 0;
	}
}

void cloud_update(struct cloud * cloud_) {
	cloud_->position.x -= cloud_->horizontalSpeed;

	if(cloud_->position.x < 0) {
		cloud_->isActive = 0;
	}
}

update_main_character(struct bird * mainCharacter) {
	//apply gravity
	mainCharacter->position.y += mainCharacter->verticalSpeed;
	mainCharacter->position.x += mainCharacter->horizontalSpeed;
}
