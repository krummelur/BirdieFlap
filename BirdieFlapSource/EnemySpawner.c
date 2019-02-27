#include "EnemySpawner.h"
#include <pic32mx.h>
#include "mipslab.h"

const uint8_t const * enemySprites[] = {enemy1, enemy2, enemy3, enemy4};

int previousTime = 0;
int spawnTime = 1000;
void spawnEnemy(struct bird * enemies) {
	if((currentTimeMillis() - previousTime) > spawnTime) {
	previousTime = currentTimeMillis();
	spawnTime = (TMR2 % 1) + 400;
	int i;
	int foundEnemy = -1;
	for(i = 0; i < MAX_ENEMY_AMOUNT; i++) {
		if (!enemies[i].isActive) {
			foundEnemy = i;
			break;
		}
	}
	if(foundEnemy == -1)
		return;

	struct bird enemy = {
		1,
		((float)(TMR2 % 1000))/4000.0 + 0.06,
		0.0,
		{128, -3 + (TMR2 % 32)},
		enemySprites[(TMR2 % 4)]
	};
		enemies[i] = enemy;
}
}
