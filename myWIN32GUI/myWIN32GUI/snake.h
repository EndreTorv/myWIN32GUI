#pragma once
static enum snake_dir
{
	DOWN,	UP,	LEFT,	RIGHT,	NODIR
} snake_direction;

void init_snake(int height, int width);
void snake_step();