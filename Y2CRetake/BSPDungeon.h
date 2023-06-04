#pragma once
#include <algorithm>
#include <utility>
#include <vector>

#include "BasicLayout.h"
#include "Room.h"


class BSPDungeon
{
public:

    BSPDungeon() = default;

    void GenerateBSP(std::vector<ETILE_TYPE>& a_Tiles, int a_Seed);

    //Apply created rooms to map
    void AddToMap(std::vector<ETILE_TYPE>& a_Tiles, const Room& a_Room);

    //Divide room into 4
    void DivideRoom(const Room& a_Room);

    Room SelectRandomRoom();

    Room SelectRandomSubRoom(const Room& a_Room);

    bool Allowed(std::vector<ETILE_TYPE>& a_Tiles, Room a_Rect);

    void AddRoom(Room& a_Room, int a_Random);

    std::vector<Room> m_Rooms;
};

