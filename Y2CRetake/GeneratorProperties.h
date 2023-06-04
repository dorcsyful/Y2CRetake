#pragma once
#define MIN_ROOM_SIZE 8
#define MAX_ROOM_SIZE
#define CA_GENERATIONS
#define WIDTH 30
#define HEIGHT 30

//Need to separate maze and bsp steps for
enum class ETILE_TYPE
{

	TILE_WALL,
	TILE_FLOOR,
	TILE_MAZE_WALL,
	TILE_BSP_WALL
};