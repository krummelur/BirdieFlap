#include "enemy.h"
#include "constants.h"
const float gravity = 0.004;
struct enemy_bird;
struct vector2;

void enemy_bird_update(struct bird * enemy, int deltaTime) {
	enemy->position.x -= enemy->horizontalSpeed * ((float)(deltaTime)/deltaTimeScale);

	if(enemy->position.x < -1*(enemy->sprite[0])) {
		enemy->isActive = 0;
	}
}

void cloud_update(struct cloud * cloud_, int deltaTime) {

	cloud_->position.x -= cloud_->horizontalSpeed;
	cloud_->position.y -= ((currentTimeMillis() / 3000) % 2 ) ? -1*cloud_->verticalSpeed : cloud_->verticalSpeed;

	if(cloud_->position.x < -1*(cloud_->sprite[0])) {
		cloud_->isActive = 0;
	}
}

void update_main_character(struct bird * mainCharacter, int deltaTime) {
	//apply gravity
	mainCharacter->verticalSpeed  += gravity * ((float)(deltaTime)/deltaTimeScale);
	mainCharacter->position.y += mainCharacter->verticalSpeed * ((float)(deltaTime)/deltaTimeScale);
	mainCharacter->position.x += mainCharacter->horizontalSpeed * ((float)(deltaTime)/deltaTimeScale);
}
