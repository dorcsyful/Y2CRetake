#include "TileMap.h"

std::pair<int, int> TileMap::SelectCoord(int a_Num)
{
    int horizontal = (a_Num % 8) * 65;
    int vertical = (a_Num / 8) * 55;

    return { horizontal,vertical };
}
bool TileMap::Load(const std::string& a_Tileset, sf::Vector2u a_TileSize)
{
    // load the tileset texture
    if (!m_Tileset.loadFromFile(a_Tileset))
        return false;

    // resize the vertex array to fit the level size
    m_Vertices.setPrimitiveType(sf::Quads);
    m_Vertices.resize(WIDTH * HEIGHT * 4);

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 1; i < HEIGHT - 1; ++i)
        for (unsigned int j = 1; j < WIDTH - 1; ++j)
        {
            std::pair<int, int> coord;
            if (m_Tiles[i * WIDTH + j] == ETILE_TYPE::TILE_FLOOR) { coord = { 0, 0 }; }
            else if (m_Tiles[i * WIDTH + j] == ETILE_TYPE::TILE_WALL) { coord = { 0, 0 }; }
            else
            {

                bool north_tile = IsWall(j, i - 1);
                bool south_tile = IsWall(j, i + 1);
                bool west_tile = IsWall(j - 1, i);
                bool east_tile = IsWall(j + 1, i);
                bool north_west_tile = IsWall(j - 1, i - 1) && north_tile && west_tile;
                bool north_east_tile = IsWall(j + 1, i - 1) && north_tile && east_tile;
                bool south_west_tile = IsWall(j - 1, i + 1) && south_tile && west_tile;
                bool south_east_tile = IsWall(j + 1, i + 1) && south_tile && east_tile;
                unsigned char mask = north_west_tile + 2 * north_tile + 4 * north_east_tile + 8 * west_tile + 16 * east_tile + 32 * south_west_tile + 64 * south_tile + 128 * south_east_tile;
                switch (mask) {
                case 0: coord = SelectCoord(47); break;   // No neighbours
                case 2: coord = SelectCoord(1); break;
                case 8: coord = SelectCoord(2); break;
                case 10: coord = SelectCoord(3); break;
                case 11: coord = SelectCoord(4); break;
                case 16: coord = SelectCoord(5); break;
                case 18: coord = SelectCoord(6); break;
                case 22: coord = SelectCoord(7); break;
                case 24: coord = SelectCoord(8); break;
                case 26: coord = SelectCoord(9); break;
                case 27: coord = SelectCoord(10); break;
                case 30: coord = SelectCoord(11); break;
                case 31: coord = SelectCoord(12); break;
                case 64: coord = SelectCoord(13); break;
                case 66: coord = SelectCoord(14); break;
                case 72: coord = SelectCoord(15); break;
                case 74: coord = SelectCoord(16); break;
                case 75: coord = SelectCoord(17); break;
                case 80: coord = SelectCoord(18); break;
                case 82: coord = SelectCoord(19); break;
                case 86: coord = SelectCoord(20); break;
                case 88: coord = SelectCoord(21); break;
                case 90: coord = SelectCoord(22); break;
                case 91: coord = SelectCoord(23); break;
                case 94: coord = SelectCoord(24); break;
                case 95: coord = SelectCoord(25); break;
                case 104: coord = SelectCoord(26); break;
                case 106: coord = SelectCoord(27); break;
                case 107: coord = SelectCoord(28); break;
                case 120: coord = SelectCoord(29); break;
                case 122: coord = SelectCoord(30); break;
                case 123: coord = SelectCoord(31); break;
                case 126: coord = SelectCoord(32); break;
                case 127: coord = SelectCoord(33); break;
                case 208: coord = SelectCoord(34); break;
                case 210: coord = SelectCoord(35); break;
                case 214: coord = SelectCoord(36); break;
                case 216: coord = SelectCoord(37); break;
                case 218: coord = SelectCoord(38); break;
                case 219: coord = SelectCoord(39); break;
                case 222: coord = SelectCoord(40); break;
                case 223: coord = SelectCoord(41); break;
                case 248: coord = SelectCoord(42); break;
                case 250: coord = SelectCoord(43); break;
                case 251: coord = SelectCoord(44); break;
                case 254: coord = SelectCoord(45); break;
                case 255: coord = SelectCoord(46); break;
                default: coord = SelectCoord(47); break;

                }
            }
            // find its position in the tileset texture
            float tu = coord.first;
            float tv = coord.second;

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &m_Vertices[(i * WIDTH + j) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(200 + j * a_TileSize.x, i * a_TileSize.y);
            quad[1].position = sf::Vector2f(200 + (j + 1) * a_TileSize.x, i * a_TileSize.y);
            quad[2].position = sf::Vector2f(200 + (j + 1) * a_TileSize.x, (i + 1) * a_TileSize.y);
            quad[3].position = sf::Vector2f(200 + j * a_TileSize.x, (i + 1) * a_TileSize.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu, tv);
            quad[1].texCoords = sf::Vector2f(tu + 32.f, tv);
            quad[2].texCoords = sf::Vector2f(tu + 32.f, tv + 32.f);
            quad[3].texCoords = sf::Vector2f(tu, tv + 32.f);
        }

    return true;
}

void TileMap::draw(sf::RenderTarget& a_Target, sf::RenderStates a_States) const
{
    // apply the transform
    a_States.transform *= getTransform();

    // apply the tileset texture
    a_States.texture = &m_Tileset;

    // draw the vertex array
    a_Target.draw(m_Vertices, a_States);
}
bool TileMap::IsWall(int a_X, int a_Y)
{
    return m_Tiles[a_Y * WIDTH + a_X] == ETILE_TYPE::TILE_MAZE_WALL || m_Tiles[a_Y * WIDTH + a_X] == ETILE_TYPE::TILE_BSP_WALL;
}