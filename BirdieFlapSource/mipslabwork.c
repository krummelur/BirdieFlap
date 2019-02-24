/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
#include "enemy.h"  /* Declatations for these labs */
#include "timeKeeper.h"  /* Declatations for these labs */
#include "Constants.h"	/*	CONSTANTS */
#include "EnemySpawner.h"	/*	CONSTANTS */

struct enemy_bird enemies[MAX_ENEMY_AMOUNT];

int mytime = 0x5957;
int loops =0;
char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  IFS(0) = 0;
	if(1) {
		milli_increment();
	}
  return;
}

void init_interrupts(void) {
	
	T2CON = 0x10;
	PR2 = 40000;
	TMR2=0;
	T2CON = T2CON | 0x8000;
	IPC(2) = 0x10;
	IEC(0)= IEC(0) | 0x100;
	enable_interrupts();
}


/* Lab-specific initialization goes here */
void labinit( void )
{
	init_interrupts();
	
	/*
	struct enemy_bird enemy1;
	struct vector2 enemy1Position;
	enemy1.isActive = 1;
	enemy1Position.x = 96.0;
	enemy1Position.y = 16.0;
	enemy1.position = enemy1Position;
	enemy1.horizontalSpeed = 0.1;
	enemies[0] = enemy1;
	*/
	struct enemy_bird inactiveEnemy5;
	inactiveEnemy5.isActive = 0;
	struct enemy_bird inactiveEnemy1;
	inactiveEnemy1.isActive = 0;
	struct enemy_bird inactiveEnemy2;
	inactiveEnemy2.isActive = 0;
	struct enemy_bird inactiveEnemy3;
	inactiveEnemy3.isActive = 0;
	struct enemy_bird inactiveEnemy4;
	inactiveEnemy4.isActive = 0;
	enemies[1] = inactiveEnemy1; 
	enemies[2] = inactiveEnemy2; 
	enemies[3] = inactiveEnemy3; 
	enemies[4] = inactiveEnemy4; 
	enemies[5] = inactiveEnemy5; 
  return;
}


/* This function is called repetitively from the main program */
/*
void labwork( void )
{
  loops++;
  tick(&mytime);
  time2string(textstring, mytime);
  display_string( 16, textstring );
  display_image(loops%2, white);
  delay(10);
  //display_update();
}
*/


//BORROWED FROM https://stackoverflow.com/questions/11819837/converting-integer-to-string-in-c-without-sprintf
int integer_to_string(char *buf, int bufsize, int n)
{
   char *start;

   // Handle negative numbers.
   //
   if (n < 0)
   {
      if (!bufsize)
         return -1;

      *buf++ = '-';
      bufsize--;
   }

   // Remember the start of the string...  This will come into play
   // at the end.
   //
   start = buf;

   do
   {
      // Handle the current digit.
      //
      int digit;
      if (!bufsize)
         return -1;
      digit = n % 10;
      if (digit < 0)
         digit *= -1;
      *buf++ = digit + '0';
      bufsize--;
      n /= 10;
   } while (n);

   // Terminate the string.
   //
   if (!bufsize)
      return -1;
   *buf = 0;

   // We wrote the string backwards, i.e. with least significant digits first.
   // Now reverse the string.
   //
   --buf;
   while (start < buf)
   {
      char a = *start;
      *start = *buf;
      *buf = a;
      ++start;
      --buf;
   }

   return 0;
}

void labwork( void )
{
	char snum[32];

  //convert 123 to string [buf]
  clear();
	/*
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  display_image(loops%96, icon);
  */
  int i;
  for(i = 0; i < MAX_ENEMY_AMOUNT; i++ ) {
  if(enemies[i].isActive)
	enemy_bird_update(&enemies[i]);
  } 
  
  spawnEnemy(enemies);
  
  for(i = 0; i < MAX_ENEMY_AMOUNT; i++ ) {
  if(enemies[i].isActive)
  buffer_make((int)(enemies[i].position.x), (int)(enemies[i].position.y), &maincharacter);
  }
  
  
  buffer_make(32, 16, &maincharacter);
  display_image_128(0, toscreenbuffer());
  /*
  integer_to_string(&snum, 4, (int)(enemy1.position.y));
  display_string( 1, snum);
  display_update();
  */
  //loops++;
}
