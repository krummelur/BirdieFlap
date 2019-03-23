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

struct highScore {
	char name[3];
	int score;
};
int waitingCooldown();

int hsEnterCooldown = 0;
int currentEnteringScore = 0;
int scoreStartX = 51;
int scoreStartY = 3;
int cursorPosition = 0;
char gameState;
struct highScore highScores[] = {(struct highScore){"MAG", 0},(struct highScore){"NUS", 0},(struct highScore){"GR8", 0},(struct highScore){"JOB", 0}};
const uint8_t * numberSprites[] = {num0, num1, num2, num3, num4, num5, num6, num7, num8, num9};
const uint8_t * charSprites[] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, };
struct bird enemies[MAX_ENEMY_AMOUNT];
struct cloud clouds[MAX_CLOUD_AMOUNT];
struct bird player;
void labinit(void);
int score = 0;
int startTime = 0;
int previousFrame = 0;

int mytime = 0x5957;
int loops = 0;
char textstring[] = "text, more text, and even more text!";
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

void setCooldown(int millis) {
	hsEnterCooldown = millis + currentTimeMillis();
}


void button_update(int deltaTime){
	int btns = getbtns();
	if(gameState == GAMESTATE_PLAYING) {
		if(btns & 0x2) {
			player.verticalSpeed += 0.025 * ((float)(deltaTime)/deltaTimeScale);
		} else if (btns & 0x4) {
			player.verticalSpeed -= 0.040 * ((float)(deltaTime)/deltaTimeScale);
		} else if (!btns && player.verticalSpeed < 0){
			player.verticalSpeed = player.verticalSpeed/1.1;
		}
	} else {
	if(btns && !waitingCooldown()){
		if(gameState == GAMESTATE_VIEW_SCORE) {
			setCooldown(200);
			gameState = GAMESTATE_GAMEOVER;
			return;
		}


	if(btns & 0x1) {
		if(gameState == GAMESTATE_GAMEOVER) {
			setCooldown(150);
			labinit();
			return;
		}
		if(GAMESTATE_ENTER_SCORE) {
			setCooldown(300);
			cursorPosition++;
			if(cursorPosition > 2) {
				gameState = GAMESTATE_VIEW_SCORE;
				return;
			}
		}
	}

		if(btns & 0x2) {
			if(gameState == GAMESTATE_ENTER_SCORE) {
				if(highScores[currentEnteringScore].name[cursorPosition] == 'Z') {
					highScores[currentEnteringScore].name[cursorPosition] = '0';
				}
				else if(highScores[currentEnteringScore].name[cursorPosition] == '9') {
					highScores[currentEnteringScore].name[cursorPosition] = 'A';
				}
				else {
					highScores[currentEnteringScore].name[cursorPosition] = highScores[currentEnteringScore].name[cursorPosition]+1;
				}
				setCooldown(160);
				return;
			}
		}

		if(btns & 0x4) {
			if(gameState == GAMESTATE_ENTER_SCORE) {
				if(highScores[currentEnteringScore].name[cursorPosition] == 'A') {
					highScores[currentEnteringScore].name[cursorPosition] = '9';
				}
				else if(highScores[currentEnteringScore].name[cursorPosition] == '0') {
					highScores[currentEnteringScore].name[cursorPosition] = 'Z';
				}
				else {
					highScores[currentEnteringScore].name[cursorPosition] = highScores[currentEnteringScore].name[cursorPosition]-1;
				}
				setCooldown(160);
				return;
		}
		if(gameState == GAMESTATE_GAMEOVER) {
			gameState = GAMESTATE_VIEW_SCORE;
			setCooldown(200);
			return;
			}
		}
	}
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
	gameState = GAMESTATE_PLAYING;
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



int waitingCooldown() {
	return !(currentTimeMillis() > hsEnterCooldown);
}

void getScoreSprites(struct highScore * curScore, uint8_t * scoreSprites[])
{
	int score_ = (*(curScore)).score;
	int j;
		for(j = 0; j < 3; j++) {
			//different drawing code depending on alphabetical  or numerical
			if((*curScore).name[j] < 65) { //numbers
				scoreSprites[j] = numberSprites[(*(curScore)).name[j] - 48];
			}
			else {
				scoreSprites[j] = charSprites[(*(curScore)).name[j] - 65];
			}

			scoreSprites[5-j] = numberSprites[score_%10];
			score_/=10;
		}
}

gameOver_Update(int deltaTime) {
	buffer_make(0, 0, &gameover, 0);
	show_score();
	return;
}

gameEnded_Update(int deltaTime) {
	int i;
			for(i = 0; i < NUM_HIGHSCORES; i++) {
				if(score > highScores[i].score) {

					//Patch the old scores
					int j;
					for (j = NUM_HIGHSCORES-1; j > i; j--) {
					highScores[j] = highScores[j-1];
					}

					highScores[i] = (struct highScore){"AAA", score};
					currentEnteringScore = i;
					gameState = GAMESTATE_ENTER_SCORE;
					cursorPosition = 0;
					setCooldown(2000);
					return;
				}
		}
		setCooldown(150);
	gameState = GAMESTATE_GAMEOVER;
}

void enterScore_update(int deltaTime) {

	//render out score like normally
	viewScore_update(deltaTime);
	//draw cursor
	buffer_make(scoreStartX+(cursorPosition*4)-1, scoreStartY+(currentEnteringScore*7)-1, &cursorSprite, 2);
}

gamePlaying_update(int deltaTime) {
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
		int dim[] = {4,4};
		if (enemies[i].isActive) {
			if (checkCollision(&(enemies[i].position), &(player.position), dim, dim)) {
				gameState = GAMESTATE_GAMEENDED;
			}
		}
	}

	//Check other gameover triggers
	if(player.position.y > 34 || player.position.y < -8) {
			gameState = GAMESTATE_GAMEENDED;
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
}

viewScore_update(int deltaTime) {
	buffer_make(0, 0, &viewHighScoreScreen, 0);

	//Construct spriteBuffer
	int i;
	for (i = 0; i < NUM_HIGHSCORES; i++  ){

		uint8_t * scoreSprites[6];
		getScoreSprites(&highScores[i], scoreSprites);
		buffer_make(scoreStartX-7, scoreStartY+(i*7), numberSprites[i+1]);
		int j;
		for(j= 0; j < 3; j++)
		buffer_make(scoreStartX+(j*4), scoreStartY+(i*7), scoreSprites[j], 0);

		for(j= 0; j < 3; j++)
		buffer_make(scoreStartX+16+(j*4), scoreStartY+(i*7), scoreSprites[j+3], 0);
	}
	return;
}



void labwork(void) {
	int deltaTime = currentTimeMillis() - previousFrame;
	previousFrame = currentTimeMillis();
	//display_update();
	//return;
	// Clear screen buffer
	clear();

	button_update(deltaTime*(1+((levelMultiplier-1)*0.2)));

	switch(gameState) {
	   case GAMESTATE_GAMEOVER  :
	      	gameOver_Update(deltaTime);
	      break;

		 case GAMESTATE_GAMEENDED  :
	      	gameEnded_Update(deltaTime);
	      break;
     case GAMESTATE_PLAYING  :
					gamePlaying_update(deltaTime);
		 break;

		 case GAMESTATE_ENTER_SCORE  :
	      	enterScore_update(deltaTime);
     break;

		 case GAMESTATE_VIEW_SCORE  :
	      viewScore_update(deltaTime);
     break;
	}
		display_image_128(0, toscreenbuffer());
}
