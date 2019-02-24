#include "BackgroundSpawner.h"
#include <pic32mx.h>
#include "mipslab.h"

uint8_t *backgroundSprites[] = {&cloud1};

int cloudPreviousTime = 0;
int cloudSpawnTime = 1000;
void spawnCloud(struct cloud * clouds) {
	if((currentTimeMillis() - cloudPreviousTime) > cloudSpawnTime) {
	cloudPreviousTime = currentTimeMillis();
	cloudSpawnTime = (TMR2 % 2000) + 700;
	int i;
	int foundCloud = -1;
	for(i = 0; i < MAX_CLOUD_AMOUNT; i++) {
		if (!clouds[i].isActive) {
			foundCloud  = i;
			break;
		}
	}
	if(foundCloud == -1)
		return;
	
	struct cloud cloud_ = 
	{
		1,
		((float)(TMR2 % 1000))/4000.0 + 0.06,
		0.0,
		{128-32, 0},
		backgroundSprites[(TMR2 % 1)]
	};
		clouds[i] = cloud_;	
}
}