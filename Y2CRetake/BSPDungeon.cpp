#include "BSPDungeon.h"

void BSPDungeon::GenerateBSP(std::vector<ETILE_TYPE>& a_Tiles, int a_Seed)
{
    srand(a_Seed);

    m_Rooms.emplace_back(2, 2, WIDTH - 2, HEIGHT - 2); // Start with a single map-sized rectangle
    Room first_room = m_Rooms[0];
    this->DivideRoom(first_room); // Divide the first room

    // Up to 240 times, we get a random rectangle and divide it. If its possible to squeeze a
    // room in there, we place it and add it to the rooms list.
    int n_rooms = 0;
    while (n_rooms < 240) {
        Room room = SelectRandomRoom();
        Room candidate = SelectRandomSubRoom(room);

        if (Allowed(a_Tiles, candidate)) {
            AddToMap(a_Tiles, candidate);
            m_Rooms.push_back(candidate);
            DivideRoom(room);
        }

        n_rooms += 1;
    }
}

void BSPDungeon::AddToMap(std::vector<ETILE_TYPE>& a_Tiles, const Room& a_Room)
{
    for (int y = a_Room.m_Start[1] + 1; y <= a_Room.m_End[1]; ++y) {
        for (int x = a_Room.m_Start[0] + 1; x <= a_Room.m_End[0]; ++x) {
            a_Tiles[y * WIDTH + x] = ETILE_TYPE::TILE_BSP_WALL;
        }
    }
}

void BSPDungeon::DivideRoom(const Room& a_Room)
{
    int width = std::abs(a_Room.m_Start[0] - a_Room.m_End[0]);
    int height = std::abs(a_Room.m_Start[1] - a_Room.m_End[1]);
    int half_width = std::max(width / 2, MIN_ROOM_SIZE);
    int half_height = std::max(height / 2, MIN_ROOM_SIZE);

    m_Rooms.emplace_back(a_Room.m_Start[0], a_Room.m_Start[1], half_width, half_height);
    m_Rooms.emplace_back(a_Room.m_Start[0], a_Room.m_Start[1] + half_height, half_width, half_height);
    m_Rooms.emplace_back(a_Room.m_Start[0] + half_width, a_Room.m_Start[1], half_width, half_height);
    m_Rooms.emplace_back(a_Room.m_Start[0] + half_width, a_Room.m_Start[1] + half_height, half_width, half_height);
}

Room BSPDungeon::SelectRandomRoom()
{
    if (m_Rooms.size() == 1) { return m_Rooms[0]; }
    int idx = std::rand() % m_Rooms.size();
    return m_Rooms[idx];
}

Room BSPDungeon::SelectRandomSubRoom(const Room& a_Room)
{
    Room result = a_Room;
    int room_width = abs(a_Room.m_Start[0] - a_Room.m_End[0]);
    int room_height = abs(a_Room.m_Start[1] - a_Room.m_End[1]);

    int w = std::max(3, std::rand() % std::min(room_width, MIN_ROOM_SIZE));
    int h = std::max(3, std::rand() % std::min(room_height, MIN_ROOM_SIZE));

    result.m_Start[0] += std::rand() % 6;
    result.m_Start[1] += std::rand() % 6;
    result.m_End[0] = result.m_Start[0] + w;
    result.m_End[1] = result.m_Start[1] + h;

    return result;
}

bool BSPDungeon::Allowed(std::vector<ETILE_TYPE>& a_Tiles, Room a_Rect)
{
    Room expanded = std::move(a_Rect);
    expanded.m_Start[0] -= 2;
    expanded.m_End[0] += 2;
    expanded.m_Start[1] -= 2;
    expanded.m_End[1] += 2;

    bool allowed = true;

    for (int y = expanded.m_Start[1]; y <= expanded.m_End[1]; ++y) {
        for (int x = expanded.m_Start[0]; x <= expanded.m_End[0]; ++x) {
            if (x > WIDTH - 4) { allowed = false; }
            if (y > HEIGHT - 4) { allowed = false; }
            if (x < 1) { allowed = false; }
            if (y < 1) { allowed = false; }
            if (allowed) {
                if (a_Tiles[y * WIDTH + x] == ETILE_TYPE::TILE_BSP_WALL) {
                    allowed = false;
                }
            }
        }
    }

    return allowed;
}

void BSPDungeon::AddRoom(Room& a_Room, int a_Random)
{
    if (!m_Rooms.empty()) { m_Rooms.erase(m_Rooms.end() - 1); }

    int width = a_Room.m_End[0] - a_Room.m_Start[0];
    int height = a_Room.m_End[1] - a_Room.m_Start[1];
    int half_width = width / 2;
    int half_height = height / 2;

    int split = 1 + std::rand() % 4;

    if (split <= 2)
    {
        Room horizontal_upper = Room(a_Room.m_Start[0], a_Room.m_Start[1], a_Room.m_Start[0] + half_width - 1, a_Room.m_End[1]);
        assert(horizontal_upper.m_Start[0] < horizontal_upper.m_End[0] && horizontal_upper.m_Start[1] < horizontal_upper.m_End[1]);
        m_Rooms.push_back(horizontal_upper);
        if (half_width > MIN_ROOM_SIZE) { AddRoom(horizontal_upper, a_Random); }

        Room horizontal_lower = Room(a_Room.m_Start[0] + half_width, a_Room.m_Start[1], a_Room.m_End[0], a_Room.m_End[1]);
        assert(horizontal_lower.m_Start[0] < horizontal_lower.m_End[0] && horizontal_lower.m_Start[1] < horizontal_lower.m_End[1]);
        m_Rooms.push_back(horizontal_lower);
        if (half_width > MIN_ROOM_SIZE) { AddRoom(horizontal_lower, a_Random); }


    }
    else
    {
        Room vertical_left = Room(a_Room.m_Start[0], a_Room.m_Start[1], a_Room.m_End[0], a_Room.m_Start[1] + half_height - 1);
        assert(vertical_left.m_Start[0] < vertical_left.m_End[0] && vertical_left.m_Start[1] < vertical_left.m_End[1]);
        m_Rooms.push_back(vertical_left);
        if (half_height > MIN_ROOM_SIZE) { AddRoom(vertical_left, a_Random); }

        Room vertical_right = Room(a_Room.m_Start[0], a_Room.m_Start[1] + half_height, a_Room.m_End[0], a_Room.m_End[1]);
        assert(vertical_right.m_Start[0] < vertical_right.m_End[0] && vertical_right.m_Start[1] < vertical_right.m_End[1]);
        m_Rooms.push_back(vertical_right);
        if (half_height > MIN_ROOM_SIZE) { AddRoom(vertical_right, a_Random); }


    }
}
