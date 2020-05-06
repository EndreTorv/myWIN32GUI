#include "2display.h"
#define TILE_SIZE 10

static HWND* local_hWnd;
static const RECT template_tile_rect = { 0, 0, TILE_SIZE, TILE_SIZE };

void set_hwnd(HWND* hWnd) {
	fprintf(stdout, "Setting hwnd.. \n");
	local_hWnd = hWnd;
}
void set_template_tile_rect() {
	fprintf(stdout, "setting tile template dims	");
	fprintf(stdout, "template.x = %d	template.y = %d	\n\n", template_tile_rect.right, template_tile_rect.bottom);
}

void paint(tile t, tile_color tc) {
	HDC hdc = GetDC(*local_hWnd);
	RECT* rect_canvas = new RECT;
	RECT* tile_rect = new RECT;
	tile_rect->left = template_tile_rect.left + t.x*TILE_SIZE;
	tile_rect->top = template_tile_rect.top + t.y*TILE_SIZE;
	tile_rect->right = template_tile_rect.right + t.x*TILE_SIZE;
	tile_rect->bottom = template_tile_rect.bottom + t.y*TILE_SIZE;

	GetClientRect(*local_hWnd, rect_canvas);
	HBRUSH brush; 
	switch (tc)
	{
	case BLACK:
		brush = CreateSolidBrush(RGB(0, 0, 0));
		break;
	case WHITE:
		brush = CreateSolidBrush(RGB(255, 255, 255));
		break;
	case RED:
		brush = CreateSolidBrush(RGB(255, 0, 0));

		break;
	default:
		brush = CreateSolidBrush(RGB(0, 0, 0));
		break;
	}
	FillRect(hdc, tile_rect, brush);

	// Free handles/resources
	DeleteObject(brush);
	delete tile_rect;
	ReleaseDC(*local_hWnd, hdc);

}

void paint_map(tile open_tiles[], int tail_length, std::list<tile> snake, tile apple) {
	for (int i = 0; i < (get_map_height()*get_map_width()-tail_length); i++)
	{
		paint(open_tiles[i], WHITE);
	}
	paint(apple, RED);
	for (std::list<tile>::reverse_iterator it = snake.rbegin(); it != snake.rend(); ++it)
	{
		paint(*it, BLACK);
	}
}