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

    //Select a random room out of m_Rooms
    Room SelectRandomRoom();

    //Get a randomly sized area out of on existing room
    Room SelectRandomSubRoom(const Room& a_Room);

    //Is the room bit enough to be divided?
    bool Allowed(std::vector<ETILE_TYPE>& a_Tiles, const Room& a_Rect);


    std::vector<Room> m_Rooms;
};

