#include "BackgroundSpawner.h"
#include <pic32mx.h>
#include "mipslab.h"

const uint8_t const *  backgroundSprites[] = {cloud1, cloud2};

int cloudPreviousTime = 0;
int cloudSpawnTime = 1000;
void spawnCloud(struct cloud * clouds) {
	if((currentTimeMillis() - cloudPreviousTime) > cloudSpawnTime) {
	cloudPreviousTime = currentTimeMillis();
	cloudSpawnTime = (TMR2 % 4000) + 3000;
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
		((float)(TMR2 % 50))/1000.0 + 0.03,
		0.035,//((float)((TMR2 % 10))/50.0),
		{128, -10 + (int)(TMR2 % 25)},
		backgroundSprites[(TMR2 % 2)]
	};
		clouds[i] = cloud_;
}
}
