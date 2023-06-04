#pragma once
#include <map>

#include "BasicLayout.h"
#include "GeneratorProperties.h"

class CellularAutomata
{
public:
    CellularAutomata(int a_Width, int a_Height) : m_Width(a_Width), m_Height(a_Height) {}

    void CAInterior(std::vector<ETILE_TYPE>& a_Tiles);


    int CountNeighbour(std::vector<ETILE_TYPE>& a_Tiles, int a_X, int a_Y);

    int m_Width;
    int m_Height;
};

