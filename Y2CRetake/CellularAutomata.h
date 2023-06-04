#pragma once
#include <map>

#include "BasicLayout.h"
#include "GeneratorProperties.h"

class CellularAutomata
{
public:
    CellularAutomata() = default;

    void CAInterior(std::vector<ETILE_TYPE>& a_Tiles);


    int CountNeighbour(std::vector<ETILE_TYPE>& a_Tiles, int a_X, int a_Y);

};

