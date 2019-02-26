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

struct bird enemies[MAX_ENEMY_AMOUNT];
struct cloud clouds[MAX_CLOUD_AMOUNT];
struct bird player;

int mytime = 0x5957;
int loops = 0;
char textstring[] = "text, more text, and even more text!";
int gameOver;

/* Interrupt Service Routine */
void user_isr(void) {
	IFS(0) = 0;
	if (1)
	{
		milli_increment();
	}
	return;
}

int getbtns() {
		return (*(volatile int*)PORTD & 0x00000e0) >> 5;
}

void button_update(void){

	int btns = getbtns();

	if(btns){

		if(btns & 0x1)
			labinit();

		if(btns & 0x2)
			player.verticalSpeed += 0.015;

		if(btns & 0x4)
			player.verticalSpeed -= 0.015;
		}

		if(!(btns))
			player.verticalSpeed = player.verticalSpeed/6;

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
	enemies[0] = inactiveEnemy;
	enemies[1] = inactiveEnemy;
	enemies[2] = inactiveEnemy;
	enemies[3] = inactiveEnemy;
	enemies[4] = inactiveEnemy;


	player = (struct bird)
	{
		1, 0, 0,
		{ 32, 16 }, maincharacter,
	};

	gameOver = 0;
	return;
}

float distanceSquared(const struct vector2 *object, const struct vector2 *other) {
	// Pythagoras
	return (object->x - other->x) *(object->x - other->x) +
		(object->y - other->y) *(object->y - other->y);
}

void labwork(void) {
	// Clear screen buffer
	clear();

	button_update();

	// Show game over screen
	if (gameOver) {
		buffer_make(0, 0, &gameover);
		display_image_128(0, toscreenbuffer());
		return;
	}

	// Update background
	int i;
	for (i = 0; i < MAX_CLOUD_AMOUNT; i++) {
		if (clouds[i].isActive)
			cloud_update(&clouds[i]);
	}

	update_main_character(&player);
	// update enemies
	for (i = 0; i < MAX_ENEMY_AMOUNT; i++) {
		if (enemies[i].isActive)
			enemy_bird_update(&enemies[i]);
	}

	// check collision
	for (i = 0; i < MAX_ENEMY_AMOUNT; i++) {
		if (enemies[i].isActive) {
			if (distanceSquared(&enemies[i].position, &player.position) < 7)
				gameOver = 0;
		}
	}

	// Spawn new enemies and backgrounds
	spawnEnemy(enemies);
	spawnCloud(clouds);

	// Draw enemies
	for (i = 0; i < MAX_ENEMY_AMOUNT; i++) {
		if (enemies[i].isActive) {
			buffer_make((int)(enemies[i].position.x), (int)(enemies[i].position.y),
				enemies[i].sprite);
		}
	}

	// Draw clouds
	for (i = 0; i < MAX_CLOUD_AMOUNT; i++) {
		if (clouds[i].isActive) {
			buffer_make((int)(clouds[i].position.x), (int)(clouds[i].position.y),
				clouds[i].sprite);
		}
	}

	//Convert to IOShield data format
	buffer_make((int) player.position.x, (int) player.position.y, player.sprite);
	display_image_128(0, toscreenbuffer());
}
