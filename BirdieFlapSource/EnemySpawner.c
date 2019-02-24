#include "EnemySpawner.h"
int previousTime = 0;
void spawnEnemy(struct enemy_bird * enemies) {
	int spawntime = 1000;
	if(currentTimeMillis() - previousTime > 500) {
	previousTime = currentTimeMillis();
	
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
	
	struct enemy_bird enemy;
	enemy.position.x = 128-16;
	enemy.position.y = 16;
	enemy.horizontalSpeed = 0.5;
	enemies[i] = enemy;
	}
}
