#ifndef BIRD
#define BIRD
#include <stdint.h>

struct vector2 {
	float x;
	float y;
};

struct bird {
	char isActive;
	float horizontalSpeed;
	float verticalSpeed;
	struct vector2 position; const uint8_t *sprite;
};

struct cloud {
	char isActive;
	float horizontalSpeed;
	float verticalSpeed;
	struct vector2 position; const uint8_t *sprite;
};

#endif