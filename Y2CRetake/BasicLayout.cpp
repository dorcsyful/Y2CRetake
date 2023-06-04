#include "BasicLayout.h"

#include "BSPDungeon.h"
#include "CellularAutomata.h"
#include "Maze.h"
void BasicLayout::Build(int a_Seed)
{

    Maze maze;
    maze.GenerateMaze(m_Tiles, WIDTH, HEIGHT, a_Seed);

	CellularAutomata ca;
    ca.CAInterior(m_Tiles);

	BSPDungeon dungeon;
    dungeon.GenerateBSP(m_Tiles, a_Seed);
    dungeon.GenerateBSP(m_Tiles, a_Seed);

    //Creating a frame around it
    for (int i = 0; i < WIDTH; i++) { m_Tiles[i] = ETILE_TYPE::TILE_WALL; }
    for (int i = 0; i < WIDTH; i++) { m_Tiles[i * WIDTH] = ETILE_TYPE::TILE_WALL; }
    for (int i = 0; i < WIDTH; i++) { m_Tiles[WIDTH - 1 + i * WIDTH] = ETILE_TYPE::TILE_WALL; }
    for (int i = 0; i < WIDTH; i++) { m_Tiles[(WIDTH - 1) * HEIGHT + i] = ETILE_TYPE::TILE_WALL; }
}




