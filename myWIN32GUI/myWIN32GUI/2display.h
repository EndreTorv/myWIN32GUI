#pragma once
#include "common.h"



void set_hwnd(HWND* hWnd);
void set_template_tile_rect();
void paint(tile t, tile_color tc);
void paint_map(tile open_tiles[], int tail_length, std::list<tile> snake, tile apple);
