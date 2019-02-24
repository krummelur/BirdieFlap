const int gravity = -0.1;

update_main_character(struct bird * mainCharacter) {
	//apply gravity
	mainCharacter->verticalSpeed += gravity;
	mainCharacter->position.x += verticalSpeed;
}