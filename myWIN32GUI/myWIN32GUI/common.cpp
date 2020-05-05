#include "common.h"

static int map_height, map_width;
static snake_dir snake_direction;

void set_snake_direction(snake_dir dir) {
	snake_direction = dir;
}
void set_map_dims(int height, int width) {
	map_height = height;
	map_width = width;
	fprintf(stdout, "Setting map dims: map_height = %d	map_width = %d\n", map_height, map_width);
}
snake_dir get_snake_direction() {
	return snake_direction;
}

int get_map_height() {
	return map_height;
}

int get_map_width() {
	return map_width;
}