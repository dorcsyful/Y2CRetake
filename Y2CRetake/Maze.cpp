#include "Maze.h"

void Maze::GenerateMaze(std::vector<ETILE_TYPE>& a_Tiles, int a_Width, int a_Height, int a_Seed)
{
	// Starting point and top-level control.
	srand(a_Seed);
	m_Width = a_Width;
	m_Height = a_Height;
	m_Grid = std::vector<int>(m_Width * m_Height);
	Visit(1, 1);


	//Add generated maze to map
	for (int y = 1; y < a_Height - 1; y++)
	{
		for (int x = 1; x < a_Width - 1; x++)
		{
			if (a_Tiles[XYToIndex(y,x)] != ETILE_TYPE::TILE_WALL && a_Tiles[XYToIndex(y, x)] != ETILE_TYPE::TILE_DOOR)
			{
				if (m_Grid[XYToIndex(y, x)] == 0)
				{

					a_Tiles[XYToIndex(y, x)] = ETILE_TYPE::TILE_INTERNAL_WALL;
				}
				else { a_Tiles[XYToIndex(y, x)] = ETILE_TYPE::TILE_FLOOR; }
			}
		}
	}


	for (int y = 1; y < m_Height - 1; y += 1) {
		for (int x = 1; x < m_Width - 1; x += 1) {
			if (a_Tiles[y * m_Width + x - 1] != ETILE_TYPE::TILE_FLOOR) { continue; }
			if (a_Tiles[y * m_Width + x + 1] != ETILE_TYPE::TILE_FLOOR) { continue; }
			if (a_Tiles[y * m_Width + x - m_Width] != ETILE_TYPE::TILE_INTERNAL_WALL) { continue; }
			if (a_Tiles[y * m_Width + x + m_Width] != ETILE_TYPE::TILE_INTERNAL_WALL) { continue; }
			if (a_Tiles[y * m_Width + x - m_Width - 1] != ETILE_TYPE::TILE_INTERNAL_WALL) { continue; }
			if (a_Tiles[y * m_Width + x - m_Width + 1] != ETILE_TYPE::TILE_INTERNAL_WALL) { continue; }
			if (a_Tiles[y * m_Width + x + m_Width - 1] != ETILE_TYPE::TILE_INTERNAL_WALL) { continue; }
			if (a_Tiles[y * m_Width + x + m_Width + 1] != ETILE_TYPE::TILE_INTERNAL_WALL) { continue; }
			a_Tiles[y * m_Width + x] = ETILE_TYPE::TILE_FLOOR;
			a_Tiles[y * m_Width + x - 1] = ETILE_TYPE::TILE_FLOOR;
			a_Tiles[y * m_Width + x + 1] = ETILE_TYPE::TILE_FLOOR;
			a_Tiles[y * m_Width + x - m_Width] = ETILE_TYPE::TILE_FLOOR;
			a_Tiles[y * m_Width + x + m_Width] = ETILE_TYPE::TILE_FLOOR;
			a_Tiles[y * m_Width + x - m_Width - 1] = ETILE_TYPE::TILE_FLOOR;
			a_Tiles[y * m_Width + x - m_Width + 1] = ETILE_TYPE::TILE_FLOOR;
			a_Tiles[y * m_Width + x + m_Width - 1] = ETILE_TYPE::TILE_FLOOR;
			a_Tiles[y * m_Width + x + m_Width + 1] = ETILE_TYPE::TILE_FLOOR;
		}
	}

	for (int y = 1; y < m_Height - 1; y += 1) {
		for (int x = 1; x < m_Width - 1; x += 1) {
			if (a_Tiles[y * m_Width + x - 1] != ETILE_TYPE::TILE_INTERNAL_WALL) { continue; }
			if (a_Tiles[y * m_Width + x + 1] != ETILE_TYPE::TILE_INTERNAL_WALL) { continue; }
			if (a_Tiles[y * m_Width + x - m_Width] != ETILE_TYPE::TILE_FLOOR) { continue; }
			if (a_Tiles[y * m_Width + x + m_Width] != ETILE_TYPE::TILE_FLOOR) { continue; }
			if (a_Tiles[y * m_Width + x - m_Width - 1] != ETILE_TYPE::TILE_INTERNAL_WALL) { continue; }
			if (a_Tiles[y * m_Width + x - m_Width + 1] != ETILE_TYPE::TILE_INTERNAL_WALL) { continue; }
			if (a_Tiles[y * m_Width + x + m_Width - 1] != ETILE_TYPE::TILE_INTERNAL_WALL) { continue; }
			if (a_Tiles[y * m_Width + x + m_Width + 1] != ETILE_TYPE::TILE_INTERNAL_WALL) { continue; }
			a_Tiles[y * m_Width + x] = ETILE_TYPE::TILE_FLOOR;
			a_Tiles[y * m_Width + x - 1] = ETILE_TYPE::TILE_FLOOR;
			a_Tiles[y * m_Width + x + 1] = ETILE_TYPE::TILE_FLOOR;
			a_Tiles[y * m_Width + x - m_Width] = ETILE_TYPE::TILE_FLOOR;
			a_Tiles[y * m_Width + x + m_Width] = ETILE_TYPE::TILE_FLOOR;
			a_Tiles[y * m_Width + x - m_Width - 1] = ETILE_TYPE::TILE_FLOOR;
			a_Tiles[y * m_Width + x - m_Width + 1] = ETILE_TYPE::TILE_FLOOR;
			a_Tiles[y * m_Width + x + m_Width - 1] = ETILE_TYPE::TILE_FLOOR;
			a_Tiles[y * m_Width + x + m_Width + 1] = ETILE_TYPE::TILE_FLOOR;
		}
	}
	//Add wide openings
	for (int x = 0; x < m_Width; x++) {
		a_Tiles[x] = ETILE_TYPE::TILE_FLOOR;
		a_Tiles[(m_Width - 1) * m_Width + x] = ETILE_TYPE::TILE_FLOOR;
	}
	for (int y = 0; y < m_Height; y++) {
		a_Tiles[y * m_Width] = ETILE_TYPE::TILE_FLOOR;
		a_Tiles[(y + 1) * m_Width - 1] = ETILE_TYPE::TILE_FLOOR;
	}

	// Convert some dead ends to walls
	for (int y = 1; y < m_Height - 1; y++)
	{
		for (int x = 1; x < m_Width - 1; x++)
		{
			if (a_Tiles[y * m_Width + x] == ETILE_TYPE::TILE_FLOOR)
			{
				int walls = 0;
				if (a_Tiles[(y - 1) * m_Width + x] == ETILE_TYPE::TILE_INTERNAL_WALL) walls++;
				if (a_Tiles[(y + 1) * m_Width + x] == ETILE_TYPE::TILE_INTERNAL_WALL) walls++;
				if (a_Tiles[y * m_Width + x - 1] == ETILE_TYPE::TILE_INTERNAL_WALL) walls++;
				if (a_Tiles[y * m_Width + x + 1] == ETILE_TYPE::TILE_INTERNAL_WALL) walls++;
				if (walls == 3)
				{
					// 50% chance to convert dead end to a wall
					if (rand() % 1 == 0)
					{
						a_Tiles[y * m_Width + x] = ETILE_TYPE::TILE_INTERNAL_WALL;
					}
				}
			}
		}
	}

	//Put a frame around the level
	for (int i = 0; i < a_Width; i++) { a_Tiles[i] = ETILE_TYPE::TILE_WALL; }
	for (int i = 0; i < a_Height; i++) { a_Tiles[i * a_Width] = ETILE_TYPE::TILE_WALL; }
	for (int i = 0; i < a_Height; i++) { a_Tiles[a_Width - 1 + i * a_Width] = ETILE_TYPE::TILE_WALL; }
	for (int i = 0; i < a_Width; i++) { a_Tiles[(a_Width - 1) * m_Height + i] = ETILE_TYPE::TILE_WALL; }
}

void Maze::Visit(int a_X, int a_Y)
{

	m_Grid[XYToIndex(a_X, a_Y)] = 1;


	EMAZE_DIRECTION dirs[4];
	dirs[0] = EMAZE_DIRECTION::DIRECTION_NORTH;
	dirs[1] = EMAZE_DIRECTION::DIRECTION_EAST;
	dirs[2] = EMAZE_DIRECTION::DIRECTION_SOUTH;
	dirs[3] = EMAZE_DIRECTION::DIRECTION_WEST;
	for (int i = 0; i < 4; ++i)
	{
		int r = rand() & 3;
		EMAZE_DIRECTION temp = dirs[r];
		dirs[r] = dirs[i];
		dirs[i] = temp;
	}

	for (int i = 0; i < 4; ++i)
	{

		int dx = 0, dy = 0;
		switch (dirs[i])
		{
		case EMAZE_DIRECTION::DIRECTION_NORTH: dy = -1; break;
		case EMAZE_DIRECTION::DIRECTION_SOUTH: dy = 1; break;
		case EMAZE_DIRECTION::DIRECTION_EAST: dx = 1; break;
		case EMAZE_DIRECTION::DIRECTION_WEST: dx = -1; break;
		}


		int x2 = a_X + (dx << 1);
		int y2 = a_Y + (dy << 1);
		if (IsInBounds(x2, y2))
		{
			if (m_Grid[XYToIndex(x2, y2)] == 0)
			{

				m_Grid[(x2 - dx) * m_Width + y2 - dy] = 1;

				Visit(x2, y2);
			}
		}
	}
}
