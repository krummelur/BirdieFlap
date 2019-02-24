#include <stdint.h> 

uint8_t megabuffer[128*32]; 
uint8_t displaybuffer[128*4];


void clear() {
	int r;
	for(r = 0; r < 128*32; r++)
		megabuffer[r] = 0;
}

void buffer_make(int x, int y, uint8_t *sprite){
	int width = 7;
	int height = 6;

	int sy;
	int sx;
	for(sy = 0; sy < height; sy++ ){		
		for(sx = 0; sx < width; sx++){
		 megabuffer[(sy+y)*128 + x+sx] = *(sprite+(sy*width + sx));
		}
	}
}

uint8_t * toscreenbuffer(){
	int index = 0;
	int y;
	int x;
	int j;
for (y = 0; y < 4; y++) {
		for(x = 0; x < 128; x++) {
			uint8_t sum = 0;
			for(j = 0; j < 8; j++) {
				sum += ((uint8_t)megabuffer[((y*8) + j)*128 + x] << j);				  
			}	
		displaybuffer[index] = sum;
		index++;
		}
	}
	return &displaybuffer;
}



