#include "CellularAutomata.h"

void CellularAutomata::CAInterior(std::vector<ETILE_TYPE>& a_Tiles)
{
    //CA to clean up some tiles I don't like
    for (int i = 0; i < 1; i++) {
        auto newtiles = a_Tiles;

        // Loop through each cell in the level
        for (int y = 0; y < m_Height; y++) {
            for (int x = 0; x < m_Width; x++) {
                int live_neighbours = CountNeighbour(a_Tiles, x, y);
                // If the cell has no live neighbours, mark it as dead
                if (live_neighbours == 0) {
                    newtiles[y * m_Width + x] = ETILE_TYPE::TILE_FLOOR;
                }
            }
        }

        // Update the original level with the changes
        for (int y = 0; y < m_Height; y++) {
            for (int x = 0; x < m_Width; x++) {
                a_Tiles[y * m_Width + x] = a_Tiles[y * m_Width + x];
            }
        }
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
            if (neighbour_x >= 0 && neighbour_x < m_Width && neighbour_y >= 0 && neighbour_y < m_Height) {
                // Count the neighbour if it's live
                if (a_Tiles[neighbour_y * m_Width + neighbour_x] == ETILE_TYPE::TILE_INTERNAL_WALL) {
                    count++;
                }
            }
        }
    }
    return count;
}
