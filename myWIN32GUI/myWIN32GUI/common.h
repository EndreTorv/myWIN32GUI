#pragma once

#include "stdafx.h"
#include "myWIN32GUI.h"
#include <Windows.h>
#include "guicon.h"
#include <stdio.h>

enum snake_dir
{
	DOWN, UP, LEFT, RIGHT, NODIR
};

struct tile
{
	int y, x;
	tile() : y(0), x(0) {};
	tile(int y, int x) : y(y), x(x) {};
};

enum tile_color
{
	BLACK, WHITE, RED
};


void set_map_dims(int height, int width);

void set_snake_direction(snake_dir dir);
snake_dir get_snake_direction();

int get_map_height();
int get_map_width();