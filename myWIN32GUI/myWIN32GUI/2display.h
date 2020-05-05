#pragma once
#include "common.h"


#define Y_METRIC 100
#define X_METRIC 100




void set_hwnd(HWND* hWnd);
void set_template_tile_rect();
void paint(tile t, tile_color tc);
void paint_canvas();
