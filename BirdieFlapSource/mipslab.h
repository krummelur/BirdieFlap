/* mipslab.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

/* Declare display-related functions from mipslabfunc.c */
void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);

/* Declare lab-related functions from mipslabfunc.c */
char * itoaconv( int num );
void labwork(void);
int nextprime( int inval );
void quicksleep(int cyc);
void tick( unsigned int * timep );

/* Declare display_debug - a function to help debugging.

   After calling display_debug,
   the two middle lines of the display show
   an address and its current contents.

   There's one parameter: the address to read and display.

   Note: When you use this function, you should comment out any
   repeated calls to display_image; display_image overwrites
   about half of the digits shown by display_debug.
*/
void display_debug( volatile int * const addr );

/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/* Declare bitmap array containing icon */
extern const uint8_t const icon[128];
extern const uint8_t const white[512];
extern const uint8_t const image[256];
extern const uint8_t const fullImage[128*4];
extern const uint8_t const maincharacter[7*5+2];
extern const uint8_t const gameover[128*32+2];
extern const uint8_t const enemy1[6*6+2];
extern const uint8_t const enemy2[5*6+2];
extern const uint8_t const enemy3[10*6+2];
extern const uint8_t const enemy4[5*5+2];
extern const uint8_t const cloud1[29*16+2];
extern const uint8_t const cloud2[24*14+2];
extern const uint8_t const num0[3*5+2];
extern const uint8_t const num1[3*5+2];
extern const uint8_t const num2[3*5+2];
extern const uint8_t const num3[3*5+2];
extern const uint8_t const num4[3*5+2];
extern const uint8_t const num5[3*5+2];
extern const uint8_t const num6[3*5+2];
extern const uint8_t const num7[3*5+2];
extern const uint8_t const num8[3*5+2];
extern const uint8_t const num9[3*5+2];
extern const uint8_t const numPlate[14*7+2];
extern const uint8_t const A[3*5+2];
extern const uint8_t const B[3*5+2];
extern const uint8_t const C[3*5+2];
extern const uint8_t const D[3*5+2];
extern const uint8_t const E[3*5+2];
extern const uint8_t const F[3*5+2];
extern const uint8_t const G[3*5+2];
extern const uint8_t const H[3*5+2];
extern const uint8_t const I[3*5+2];
extern const uint8_t const J[3*5+2];
extern const uint8_t const K[3*5+2];
extern const uint8_t const L[3*5+2];
extern const uint8_t const M[3*5+2];
extern const uint8_t const N[3*5+2];
extern const uint8_t const O[3*5+2];
extern const uint8_t const P[3*5+2];
extern const uint8_t const Q[3*5+2];
extern const uint8_t const R[3*5+2];
extern const uint8_t const S[3*5+2];
extern const uint8_t const T[3*5+2];
extern const uint8_t const U[3*5+2];
extern const uint8_t const V[3*5+2];
extern const uint8_t const W[3*5+2];
extern const uint8_t const X[3*5+2];
extern const uint8_t const Y[3*5+2];
extern const uint8_t const Z[3*5+2];
extern const uint8_t enterHighScoreScreen[1];
extern const uint8_t viewHighScoreScreen[128*32+2];
extern const uint8_t cursorSprite[5*7+2];
/* Declare text buffer for display output */
extern char textbuffer[4][16];

/* Declare functions written by students.
   Note: Since we declare these functions here,
   students must define their functions with the exact types
   specified in the laboratory instructions. */
/* Written as part of asm lab: delay, time2string */
void delay(int);
void time2string( char *, int );
/* Written as part of i/o lab: getbtns, getsw, enable_interrupt */
int getbtns(void);
int getsw(void);
void enable_interrupt(void);
