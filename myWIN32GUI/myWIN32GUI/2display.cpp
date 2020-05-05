#include "2display.h"

static HWND* local_hWnd;
static RECT template_tile_rect;// = { 0, 0, 100, 100 };

void set_hwnd(HWND* hWnd) {
	fprintf(stdout, "Setting hwnd.. \n");
	local_hWnd = hWnd;
}
void set_template_tile_rect() {
	fprintf(stdout, "setting tile template dims	");
	template_tile_rect = { 0, 0, X_METRIC / (get_map_width()), Y_METRIC / (get_map_height()) };
	fprintf(stdout, "template.x = %d	template.y = %d	\n\n", template_tile_rect.right, template_tile_rect.bottom);
}

void paint(tile t, tile_color tc) {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(*local_hWnd, &ps);
	RECT* rect_canvas = new RECT;
	RECT* tile_rect = new RECT;
	tile_rect->left = template_tile_rect.left + t.x;
	tile_rect->top = template_tile_rect.top + t.y;
	tile_rect->right = template_tile_rect.right + t.x;
	tile_rect->bottom = template_tile_rect.bottom + t.y;
	fprintf(stdout, "painting rectangle.. \n");
	fprintf(stdout, "	..top:	%d	right:	%d\n", tile_rect->top, tile_rect->right);
	fprintf(stdout, "	..left:	%d	button:	%d\n", tile_rect->left, tile_rect->bottom);

	GetClientRect(*local_hWnd, rect_canvas);
	SetMapMode(hdc, MM_ANISOTROPIC);
	SetWindowExtEx(hdc, Y_METRIC, X_METRIC, NULL);
	SetViewportExtEx(hdc, rect_canvas->right, rect_canvas->bottom, NULL);
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
	EndPaint(*local_hWnd, &ps);

}

void paint_canvas() {
	for (int h = 0; h < get_map_height(); h++)
	{
		for (int w = 0; w < get_map_width(); w++)
		{
			paint(tile(h,w), WHITE);
		}
	}
}