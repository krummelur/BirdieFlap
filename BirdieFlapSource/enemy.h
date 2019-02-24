struct vector2{
   float x;
   float y;
};
struct enemy_bird {
   float horizontalSpeed;
   struct vector2 position;
};

void enemy_bird_update(struct enemy_bird * enemy);
