#pragma once
#include <cstdlib>
#include "BasicLayout.h"

enum class EMAZE_DIRECTION
{
	DIRECTION_NORTH,
	DIRECTION_EAST,
	DIRECTION_SOUTH,
	DIRECTION_WEST
};


class Maze {
public:
	int m_Width;
	int m_Height;
	std::vector<int> m_Grid;

	void GenerateMaze(std::vector<ETILE_TYPE>& a_Tiles, int a_Width, int a_Height, int a_Seed);

	int XYToIndex(int x, int y)
	{
		// Converts the two-dimensional index pair (x,y) into a
		// single-dimensional index. The result is y * WIDTH + x.
		return y * m_Width + x;
	}
	int IsInBounds(int a_X, int a_Y)
	{
		// Returns "true" if x and y are both in-bounds.
		if (a_X < 0 || a_X >= m_Width) return false;
		if (a_Y < 0 || a_Y >= m_Height) return false;
		return true;
	}
	// This is the recursive function we will code in the next project
	void Visit(int a_X, int a_Y);
};