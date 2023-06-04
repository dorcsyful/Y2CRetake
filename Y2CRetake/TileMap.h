#pragma once
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "GeneratorProperties.h"




class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    std::pair<int, int> SelectCoord(int a_Num);
    bool Load(const std::string& a_Tileset, sf::Vector2u a_TileSize);
    std::vector<ETILE_TYPE> m_Tiles;
private:
    void draw(sf::RenderTarget& a_Target, sf::RenderStates a_States) const override;
    bool IsWall(int a_X, int a_Y);

    sf::VertexArray m_Vertices;
    sf::Texture m_Tileset;
};