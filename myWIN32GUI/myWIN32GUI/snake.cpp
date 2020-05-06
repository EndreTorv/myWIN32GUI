#include "snake.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


bool operator==(tile &left, tile &right) {
	if (left.x != right.x || left.y != right.y)
		return false;
	return true;
}

static tile* open_tiles;
static int end_open_tiles;
static tile head, apple;

static void reset_tiles() {
	for (int h = 0; h < get_map_height(); h++)
	{
		for (int w = 0; w < get_map_width(); w++)
		{
			int index = h * get_map_width() + w;
			open_tiles[index] = tile(h, w);
			paint(open_tiles[index], WHITE);
		}
	}
	end_open_tiles = get_map_width() * get_map_height();
}

static void init_map() {
	fprintf(stdout, "initing map..\n");
	open_tiles = new tile[get_map_height()*get_map_width()];
	reset_tiles();
}

static std::list<tile> tail;
static int tail_length = 1;

static void replace_apple() {
	int open_tile_index = rand() % (end_open_tiles);
	apple = open_tiles[open_tile_index];
	paint(apple, RED);
}

void init_snake(HWND* hWnd, int height, int width) {
	fprintf(stdout, "initing snake..\n");
	srand((unsigned int)time(NULL));
	set_map_dims(height, width);
	set_hwnd(hWnd);
	set_template_tile_rect();
	init_map();
}

static void add_open_tile(tile addingTile){
	open_tiles[end_open_tiles] = addingTile;
	end_open_tiles++;
	tail_length--;
	paint(addingTile, WHITE);
}
static void remove_open_tile(tile removingTile){
	//Search tile
	int removingTile_index = -1;
	for (int i = 0; i < end_open_tiles; i++)
	{
		if (open_tiles[i] == removingTile)
		{
			removingTile_index = i;
			break;
		}
	}
	if (removingTile_index < 0)
	{
		fprintf(stdout, "tile to be removed does not exist ! tile y = %d	x = %d\n", removingTile.y, removingTile.x);
		while (1) {

		}
	}
	//shrink open_tiles
	open_tiles[removingTile_index] = open_tiles[end_open_tiles];
	end_open_tiles--;
	tail_length++;
	paint(removingTile, BLACK);
}

static void reset_game() {
	//tail.erase(tail.begin(), tail.end());
	for (std::list<tile>::reverse_iterator it = tail.rbegin(); it != tail.rend(); ++it)
	{
		tail.pop_back();
	}
	set_snake_direction(NODIR);
	head = {  get_map_height()/2, get_map_width()/2 };
	tail_length = 1;
	// PAINT BLANK MAP
	paint_map(open_tiles, tail_length, tail, apple);
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
		fprintf(stdout, "head out of bounds\n");
		reset_game();
		return -1;
	}
	//check if head crash with tail
	if (tail.begin() == tail.end())
		fprintf(stdout, "begin()==end()\n");

	for (std::list<tile>::iterator it = tail.begin(); it != tail.end(); it++)
	{
		fprintf(stdout, "tile	y= %d,	x=%d", it->y, it->x);
		if (head == *it) {
			fprintf(stdout, "head crash with tail\n");
			reset_game();
			return -1;
		}
	}
	
	//Progress game
	if ((head == apple) || (tail_length == 1))
	{

		fprintf(stdout, "eating..	");
		replace_apple();
		remove_open_tile(head);
		tail.push_back(head);
	}
	else
	{
		fprintf(stdout, "moving..	");
		remove_open_tile(head);
		tail.push_front(head);
		add_open_tile(tail.back());		// HER
		fprintf(stdout, "adding tile	y= %d,	x=%d", tail.back().y, tail.back().x);
		tail.pop_back();
		
	}

	fprintf(stdout, "head at:	y = %d, x = %d\n", head.y, head.x);
	return 1;
}


