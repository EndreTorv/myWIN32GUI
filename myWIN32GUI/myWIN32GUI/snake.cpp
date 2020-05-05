#include "snake.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


bool operator==(tile &left, tile &right) {
	if (left.x != right.x || left.y != right.y)
		return false;
	return true;
}

static tile* open_tiles;
static tile head, apple;

static void reset_tiles() {
	for (int h = 0; h < get_map_height(); h++)
	{
		for (int w = 0; w < get_map_width(); w++)
		{
			open_tiles[h*w] = tile(h, w);
			paint(open_tiles[h*w], WHITE);
		}
	}
}
static void init_map() {
	fprintf(stdout, "initing map..\n");
	open_tiles = new tile[get_map_height()*get_map_width()];
	reset_tiles();
}

static std::list<tile> tail;
static int tail_length = 1;

static void replace_apple() {
	int open_tile_index = rand() % (get_map_height()*get_map_width() - tail_length);
	apple = open_tiles[open_tile_index];
	paint(apple, RED);
}

void init_snake(HWND* hWnd, int height, int width) {
	fprintf(stdout, "initing snake..\n");
	srand((unsigned int)time(NULL));
	set_map_dims(height, width);
	set_hwnd(hWnd);
	set_template_tile_rect();
	//init_map();
}

static void add_open_tile(tile addingTile){
	open_tiles[tail_length] = addingTile;
	tail_length++;
	paint(addingTile, WHITE);
}
static void remove_open_tile(tile removingTile){
	//Search tile
	int removingTile_index;
	for (int i = 0; i < tail_length; i++)
	{
		if (open_tiles[i] == removingTile)
		{
			removingTile_index = i;
			break;
		}
	}
	//shrink open_tiles
	open_tiles[removingTile_index] = open_tiles[tail_length];
	tail_length--;
	paint(removingTile, BLACK);
}

static void reset_game() {
	fprintf(stdout, "tail.erase() \n");
	//tail.erase(tail.begin(), tail.end());
	for (std::list<tile>::reverse_iterator it = tail.rbegin(); it != tail.rend(); ++it)
	{
		tail.pop_back();
	}
	set_snake_direction(NODIR);
	head = {  get_map_height()/2, get_map_width()/2 };
	tail_length = 1;
	paint_canvas();
}

int snake_step() {
	switch (get_snake_direction())
	{
	case DOWN:
		head.y += 1;
		break;
	case UP:
		head.y -= 1;
		break;
	case LEFT:
		head.x -= 1;
		break;
	case RIGHT:
		head.x += 1;
		break;
	default:
		break;
	}
	
	//Check within borders
	if ((head.y < 0) || (head.y >= get_map_height()) || (head.x < 0) || (head.x >= get_map_width())) {
		reset_game();
		return -1;
	}
	//check if head crash with tail
	fprintf(stdout, "for loop tail \n");
	fprintf(stdout, "tail.begin() \n");
	tail.begin();
	fprintf(stdout, "for loop tail \n");
	for (std::list<tile>::iterator it = tail.begin(); it != tail.end(); it++)
	{
		fprintf(stdout, "for loop tail \n");
		if (head == *it) {
			reset_game();
			return -1;
		}
	}
	
	//Progress game
	if (head == apple)
	{
		replace_apple();
		remove_open_tile(head);
		tail.push_back(head);
	}
	else
	{
		add_open_tile(tail.back());		// HER
		tail.pop_back();
		remove_open_tile(head);
		tail.push_front(head);
	}
	return 1;
}


