#include <stdint.h>

uint8_t megabuffer[128 * 32];
uint8_t displaybuffer[128 * 4];

void clear()
{
	int r;
	for (r = 0; r < 128 * 32; r++)
		megabuffer[r] = 0;
}

void buffer_make(int x, int y, uint8_t *sprite, int mode)
{
	int width = (int) sprite[0];
	int height = (int) sprite[1];

	uint8_t sy;
	uint8_t sx;
	for (sy = 0; sy < height; sy++)
	{
		for (sx = 0; sx < width; sx++)
		{
			//Make sure not to draw outside the buffer
			if((x+sx < 128 && sy+y < 32) && (x+sx >=0 && sy+y >= 0)) {
				if (mode == 0)
					megabuffer[(sy + y) * 128 + x + sx] |= *(sprite + (sy *width + sx + 2));

				if (mode == 1)
					megabuffer[(sy + y) * 128 + x + sx] = *(sprite + (sy *width + sx + 2));
				if (mode == 2)
					megabuffer[(sy + y) * 128 + x + sx] = !(megabuffer[(sy + y) * 128 + x + sx]);
			}
		}
	}
}

uint8_t *toscreenbuffer()
{
	int index = 0;
	int y;
	int x;
	int j;
	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 128; x++)
		{
			uint8_t sum = 0;
			for (j = 0; j < 8; j++)
			{
				sum += ((uint8_t) megabuffer[((y * 8) + j) * 128 + x] << j);
			}
			displaybuffer[index] = sum;
			index++;
		}
	}
	return &displaybuffer;
}
