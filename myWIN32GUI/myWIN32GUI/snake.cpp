using namespace pmr;
#include "snake.h"

static struct bordersRect {
	int upper, lower, left, right;
} snakeMap;

static struct point
{
	int x, y;
} head, apple;

void set_struct(int upper, int lower, int left, int right) {
	snakeMap.upper = upper;
	snakeMap.lower = lower;
	snakeMap.left = left;
	snakeMap.right = right;
}

static vector tail;

void move_snake() {
	switch (direction)
	{
	case DOWN:
		head.y += 1;
		break;
	case UP:
		head.y -= 1:
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
	if (head == apple)
	{
		replace_apple();
		length += 1;
		tail.push_back();
	}
	else
	{
		
	}
	for (int i = 0; i < length; i++)
	{
		if (head == *(head + i)) {
			length = 0;
			direction = RIGHT;
			head = { (snakeMap.right - snakeMap.left)/ 2, (snakeMake.lower - snakeMap.upper / 2 };
			break;
		}
	}
}