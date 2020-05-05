#pragma once
#include <list>
#include "common.h"
#include "2display.h"



void set_snake_direction(snake_dir);
void init_snake(HWND* hWnd, int height, int width);
int snake_step(); // returns -1 if the snake crashes, returns 1 otherwise