/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog

   For copyright and licensing, see file COPYING */
#include <stdint.h>       /* Declarations of uint_32 and the like */
#include <pic32mx.h>      /* Declarations of system-specific addresses etc */
#include "mipslab.h"      /* Declatations for these labs */
#include "enemy.h"        /* Declatations for these labs */
#include "bird.h"         /* Declatations for these labs */
#include "timeKeeper.h"   /* Declatations for these labs */
#include "Constants.h"    /*	CONSTANTS */
#include "EnemySpawner.h" /*	CONSTANTS */

const uint8_t * numberSprites[] = {num0, num1, num2, num3, num4, num5, num6, num7, num8, num9};
struct bird enemies[MAX_ENEMY_AMOUNT];
struct cloud clouds[MAX_CLOUD_AMOUNT];
struct bird player;
void labinit(void);
int score;
int startTime = 0;
int previousFrame = 0;

int mytime = 0x5957;
int loops = 0;
char textstring[] = "text, more text, and even more text!";
int gameOver;
float levelMultiplier = 1.0;

/* Interrupt Service Routine */
void user_isr(void) {
	IFS(0) = 0;
	if (1)
	{
		milli_increment();
	}
	return;
}

show_score() {
	int score_ = score;
	int posX = 128-4;
	int i;
	int num; 
		buffer_make(128-14, 1, numPlate, 1);
	for(i = 0; i < 3; i++) {
		buffer_make(posX, 1, numberSprites[score_%10], 0);
		score_ /= 10;
		posX -= 4;
	} 
}

int getbtns() {
		return (*(volatile int*)PORTD & 0x00000e0) >> 5;
}

void button_update(int deltaTime){
	int btns = getbtns();

	if(btns){

		if(btns & 0x1)
			labinit();

		if(btns & 0x2)
			player.verticalSpeed += 0.025 * ((float)(deltaTime)/deltaTimeScale);

		if(btns & 0x4)
			player.verticalSpeed -= 0.040 * ((float)(deltaTime)/deltaTimeScale);
		}

		if(!(btns) && player.verticalSpeed < 0) {
			player.verticalSpeed = player.verticalSpeed/1.1;
		}

	}




void init_interrupts(void) {

	T2CON = 0x10;
	PR2 = 40000;
	TMR2 = 0;
	T2CON = T2CON | 0x8000;
	IPC(2) = 0x10;
	IEC(0) = IEC(0) | 0x100;
	enable_interrupts();
}

/* Lab-specific initialization goes here */
void labinit(void) {
	init_interrupts();

	*(volatile int*)TRISD = *(int*)TRISD | 0xf0;

	struct bird inactiveEnemy;
	inactiveEnemy.isActive = 0;
	int i;
	for(i = 0; i < MAX_ENEMY_AMOUNT; i++)
		enemies[i] = inactiveEnemy;
	
	struct cloud inactiveCloud;
	inactiveCloud.isActive = 0;
	
	for(i = 0; i < MAX_CLOUD_AMOUNT; i++)
		clouds[i] = inactiveCloud;
	

	player = (struct bird)
	{
		1, 0, 0,
		{ 32, 16 }, maincharacter,
	};

	startTime = currentTimeMillis();
	gameOver = 0;
	return;
}

float distanceSquared(const struct vector2 *object, const struct vector2 *other, int * objectOffset, int * otherOffset) {
	// Pythagoras
  int otherXcenter = other->x+(otherOffset[0]/2);
  int otherYcenter = other->y+(otherOffset[1]/2);
  int objectXcenter = object->x+(otherOffset[0]/2);
  int objectYcenter = object->y+(otherOffset[1]/2);
	return (objectXcenter - otherXcenter) *(objectXcenter - otherXcenter) +
		(objectYcenter - otherYcenter) *(objectYcenter - otherYcenter);
}

int checkCollision(const struct vector2 *object, const struct vector2 *other, int * objectdimensions, int * otherDimensions) {
  int deltaX = object->x - other->x;
  int deltaY = object->y - other->y;
  deltaX = (deltaX >= 0) ? deltaX : -1* deltaX;
  deltaY = (deltaY >= 0) ? deltaY : -1* deltaY;
  if ((deltaX) < (objectdimensions[0]/2)+(otherDimensions[0]/2) &&
      ((deltaY) < (objectdimensions[1]/2)+(otherDimensions[1]/2))) {
        return 1;
      }
  return 0;
}

void labwork(void) {
	int deltaTime = currentTimeMillis() - previousFrame; 
	previousFrame = currentTimeMillis();
	//display_update();
	//return;
	// Clear screen buffer
	clear();

	//Make bird 
	button_update(deltaTime*(1+((levelMultiplier-1)*0.2)));

	// Show game over screen
	if (gameOver) {
		buffer_make(0, 0, &gameover, 0);
		show_score();
		display_image_128(0, toscreenbuffer());
		return;
	}

	// Update background
	int i;
	for (i = 0; i < MAX_CLOUD_AMOUNT; i++) {
		if (clouds[i].isActive)
			cloud_update(&clouds[i], deltaTime*levelMultiplier);
	}

	update_main_character(&player, deltaTime);
	// update enemies
	for (i = 0; i < MAX_ENEMY_AMOUNT; i++) {
		if (enemies[i].isActive)
			enemy_bird_update(&enemies[i], deltaTime*levelMultiplier);
	}

	// check collision
	for(i = 0; i < MAX_ENEMY_AMOUNT; i++) {
    int dim[] = {5,5};
    if (enemies[i].isActive) {
			if (checkCollision(&(enemies[i].position), &(player.position), dim, dim)) {
				gameOver = 0;
		}
	}
}

	//Check other gameover triggers
	if(player.position.y > 34 ||
		player.position.y < -8) {
			gameOver = 1;
		}

	// Spawn new enemies and backgrounds
	spawnEnemy(enemies);
	spawnCloud(clouds);

	// Draw enemies
	for (i = 0; i < MAX_ENEMY_AMOUNT; i++) {
		if (enemies[i].isActive) {
			buffer_make((int)(enemies[i].position.x), (int)(enemies[i].position.y),
				enemies[i].sprite), 0;
		}
	}

	// Draw clouds
	for (i = 0; i < MAX_CLOUD_AMOUNT; i++) {
		if (clouds[i].isActive) {
			buffer_make((int)(clouds[i].position.x), (int)(clouds[i].position.y),
				clouds[i].sprite, 0);
		}
	}

	//Convert to IOShield data format
	
	buffer_make((int) player.position.x, (int) player.position.y, player.sprite, 0);
	score = (currentTimeMillis()-startTime) / 1000 / 3;
	levelMultiplier =  1+ 0.1*score;
	show_score();
	display_image_128(0, toscreenbuffer());
	
}
