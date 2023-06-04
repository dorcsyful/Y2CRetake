#pragma once
#include <cassert>
#include <vector>

#include "GeneratorProperties.h"


//The basic layout with a BSP tree
class BasicLayout
{
public:
	BasicLayout() : m_Tiles(std::vector<ETILE_TYPE>(WIDTH * HEIGHT, ETILE_TYPE::TILE_FLOOR)) {}

	void Build(int a_Seed);

	std::vector<ETILE_TYPE> m_Tiles;

};

