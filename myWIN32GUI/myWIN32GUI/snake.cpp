#include "snake.h"
#include <list>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

static struct tile
{
	int y, x;
} head, apple;

bool operator==(tile &left, tile &right) {
	if (left.x != right.x || left.y != right.y)
		return false;
	return true;
}

static int map_height, map_width;
static tile* open_tiles;

static void init_map() {
	open_tiles = new tile[map_height*map_width];
}
static void reset_map() {
	delete[] open_tiles;
	open_tiles = new tile[map_height*map_width];
}


static std::list<tile> tail;

static int tail_length = 0;

static void replace_apple() {
	int open_tile_index = rand() % (map_height*map_width - tail_length);
	apple = open_tiles[open_tile_index];
}


void init_snake() {
	srand(time(NULL));
	init_map();
}

static void add_open_tile(tile addingTile){
	open_tiles[tail_length] = addingTile;
	tail_length++;
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
}

static void reset_game() {
	tail.erase(tail.begin(), tail.end());
	direction = NODIR;
	head = {  map_height/2, map_width/2 };
	tail_length = 0;
}

void snake_step() {
	switch (direction)
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
	if ((head.y < 0) || (head.y >= map_height) || (head.x < 0) || (head.x >= map_width)) {
		reset_game();
		return;
	}
	//check if head crash with tail
	for (std::list<tile>::iterator it = tail.begin(); it != tail.end(); ++it)
	{
		if (head == *it) {
			reset_game();
			return;
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
		add_open_tile(tail.back());
		tail.pop_back();
		remove_open_tile(head);
		tail.push_front(head);
	}
}


