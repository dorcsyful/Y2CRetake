#include "CellularAutomata.h"

void CellularAutomata::CAInterior(std::vector<ETILE_TYPE>& a_Tiles)
{
    //Widen corridors
    //1 1 1        0 0 0      1 0 1        0 0 0
    //0 0 0   ->   0 0 0  and 1 0 1   ->   0 0 0
    //1 1 1        0 0 0      1 0 1        0 0 0
    for (int y = 1; y < HEIGHT - 1; y += 1) {
        for (int x = 1; x < WIDTH - 1; x += 1) {
            if ((  a_Tiles[y * WIDTH + x - 1] == ETILE_TYPE::TILE_FLOOR 
                && a_Tiles[y * WIDTH + x + 1] == ETILE_TYPE::TILE_FLOOR 
                && a_Tiles[y * WIDTH + x - WIDTH] == ETILE_TYPE::TILE_MAZE_WALL
                && a_Tiles[y * WIDTH + x + WIDTH] == ETILE_TYPE::TILE_MAZE_WALL 
                && a_Tiles[y * WIDTH + x - WIDTH - 1] == ETILE_TYPE::TILE_MAZE_WALL
                && a_Tiles[y * WIDTH + x - WIDTH + 1] == ETILE_TYPE::TILE_MAZE_WALL 
                && a_Tiles[y * WIDTH + x + WIDTH - 1] == ETILE_TYPE::TILE_MAZE_WALL 
                && a_Tiles[y * WIDTH + x + WIDTH + 1] == ETILE_TYPE::TILE_MAZE_WALL)
                ||
                (  a_Tiles[y * WIDTH + x - 1] == ETILE_TYPE::TILE_MAZE_WALL
                && a_Tiles[y * WIDTH + x + 1] == ETILE_TYPE::TILE_MAZE_WALL
                && a_Tiles[y * WIDTH + x - WIDTH] == ETILE_TYPE::TILE_FLOOR
                && a_Tiles[y * WIDTH + x + WIDTH] == ETILE_TYPE::TILE_FLOOR
                && a_Tiles[y * WIDTH + x - WIDTH - 1] == ETILE_TYPE::TILE_MAZE_WALL
                && a_Tiles[y * WIDTH + x - WIDTH + 1] == ETILE_TYPE::TILE_MAZE_WALL
                && a_Tiles[y * WIDTH + x + WIDTH - 1] == ETILE_TYPE::TILE_MAZE_WALL
                && a_Tiles[y * WIDTH + x + WIDTH + 1] == ETILE_TYPE::TILE_MAZE_WALL))
            {
            a_Tiles[y * WIDTH + x] = ETILE_TYPE::TILE_FLOOR;
            a_Tiles[y * WIDTH + x - 1] = ETILE_TYPE::TILE_FLOOR;
            a_Tiles[y * WIDTH + x + 1] = ETILE_TYPE::TILE_FLOOR;
            a_Tiles[y * WIDTH + x - WIDTH] = ETILE_TYPE::TILE_FLOOR;
            a_Tiles[y * WIDTH + x + WIDTH] = ETILE_TYPE::TILE_FLOOR;
            a_Tiles[y * WIDTH + x - WIDTH - 1] = ETILE_TYPE::TILE_FLOOR;
            a_Tiles[y * WIDTH + x - WIDTH + 1] = ETILE_TYPE::TILE_FLOOR;
            a_Tiles[y * WIDTH + x + WIDTH - 1] = ETILE_TYPE::TILE_FLOOR;
            a_Tiles[y * WIDTH + x + WIDTH + 1] = ETILE_TYPE::TILE_FLOOR;	            
            }

        }
    }


    // Convert some dead ends to walls
    for (int y = 1; y < HEIGHT - 1; y++)
    {
        for (int x = 1; x < WIDTH - 1; x++)
        {
            if (a_Tiles[y * WIDTH + x] == ETILE_TYPE::TILE_FLOOR)
            {
                int walls = 0;
                if (a_Tiles[(y - 1) * WIDTH + x] == ETILE_TYPE::TILE_MAZE_WALL) walls++;
                if (a_Tiles[(y + 1) * WIDTH + x] == ETILE_TYPE::TILE_MAZE_WALL) walls++;
                if (a_Tiles[y * WIDTH + x - 1] == ETILE_TYPE::TILE_MAZE_WALL) walls++;
                if (a_Tiles[y * WIDTH + x + 1] == ETILE_TYPE::TILE_MAZE_WALL) walls++;
                if (walls == 3)
                {
                    // 50% chance to convert dead end to a wall
                    if (rand() % 1 == 0)
                    {
                        a_Tiles[y * WIDTH + x] = ETILE_TYPE::TILE_MAZE_WALL;
                    }
                }
            }
        }
    }

    //CA to clean up some tiles I don't like
    for (int i = 0; i < 1; i++) {
        auto newtiles = a_Tiles;

        // Loop through each cell in the level
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                int live_neighbours = CountNeighbour(a_Tiles, x, y);
                // If the cell has no live neighbours, mark it as dead
                if (live_neighbours == 0) {
                    newtiles[y * WIDTH + x] = ETILE_TYPE::TILE_FLOOR;
                }
            }
        }

        // Update the original level with the changes
        a_Tiles = newtiles;

    }
}

int CellularAutomata::CountNeighbour(std::vector<ETILE_TYPE>& a_Tiles, int a_X, int a_Y)
{
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            // Skip counting the current cell
            if (i == 0 && j == 0) {
                continue;
            }
            int neighbour_x = a_X + i;
            int neighbour_y = a_Y + j;
            // Check if the neighbour is in bounds
            if (neighbour_x >= 0 && neighbour_x < WIDTH && neighbour_y >= 0 && neighbour_y < HEIGHT) {
                // Count the neighbour if it's active
                if (a_Tiles[neighbour_y * WIDTH + neighbour_x] == ETILE_TYPE::TILE_MAZE_WALL) {
                    count++;
                }
            }
        }
    }
    return count;
}
