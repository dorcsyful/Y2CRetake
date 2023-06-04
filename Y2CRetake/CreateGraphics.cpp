#include "CreateGraphics.h"

#include "GeneratorProperties.h"
#include "BasicLayout.h"
void CreateGraphics::CreateWindow()
{

    m_Background.setFillColor(sf::Color(218, 218, 218));
    m_Background.setSize(sf::Vector2<float>(WIDTH * m_SpriteSize + 200, HEIGHT * m_SpriteSize));
    m_Window = std::make_shared<sf::RenderWindow>(sf::VideoMode(WIDTH * m_SpriteSize + 200, HEIGHT * m_SpriteSize), "Warfair level generator");
    LoadText();
    LoadTextures();
    CreateRegerateButton();
    CreateImageGenerateButton();
}

void CreateGraphics::UpdateSprites(const BasicLayout& a_Layout)
{
    m_Sprites.clear();
    int x = 200;
    int y = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            sf::RectangleShape temp;
            temp.setSize(sf::Vector2<float>(m_SpriteSize, m_SpriteSize));
            temp.setPosition(sf::Vector2<float>(x, y));
            if (a_Layout.m_Tiles[i * WIDTH + j] == ETILE_TYPE::TILE_FLOOR) { temp.setTexture(&m_Textures["Floor"]); }
            else if (a_Layout.m_Tiles[i * WIDTH + j] == ETILE_TYPE::TILE_WALL) { temp.setFillColor(sf::Color(0, 0, 0)); }
            else if (a_Layout.m_Tiles[i * WIDTH + j] == ETILE_TYPE::TILE_INTERNAL_WALL) { temp.setTexture(&m_Textures["Wall"]); }
            else if (a_Layout.m_Tiles[i * WIDTH + j] == ETILE_TYPE::TILE_HALF_WALL) { temp.setTexture(&m_Textures["Brick"]); }
            x += m_SpriteSize;
            m_Sprites.push_back(temp);
        }
        x = 200;
        y += m_SpriteSize;
    }
}

void CreateGraphics::CreateRegerateButton()
{
    m_RegenerateButtonBox.setPosition(sf::Vector2<float>(0, 200));
    m_RegenerateButtonBox.setFillColor(sf::Color::Yellow);
    m_RegenerateButtonBox.setSize(sf::Vector2<float>(200, 50));


    m_RegenerateButtonText.setFont(m_Font);
    m_RegenerateButtonText.setCharacterSize(20);
    m_RegenerateButtonText.setFillColor(sf::Color::Blue);
    m_RegenerateButtonText.setStyle(sf::Text::Bold);
    m_RegenerateButtonText.setString("Regenerate With \n New Seed");
    m_RegenerateButtonText.setPosition(0, 200);
}

void CreateGraphics::CreateImageGenerateButton()
{
    m_GenerateImageBox.setPosition(sf::Vector2<float>(0, 300));
    m_GenerateImageBox.setFillColor(sf::Color::Black);
    m_GenerateImageBox.setSize(sf::Vector2<float>(200, 50));


    m_GenerateImageText.setFont(m_Font);
    m_GenerateImageText.setCharacterSize(20);
    m_GenerateImageText.setFillColor(sf::Color::White);
    m_GenerateImageText.setStyle(sf::Text::Bold);
    m_GenerateImageText.setString("Generate image");
    m_GenerateImageText.setPosition(0, 300);
}

void CreateGraphics::LoadTextures()
{
    sf::Texture brick;
    sf::Texture wall;
    sf::Texture floor;
    brick.loadFromFile("../Dependencies/Brick.png");
    wall.loadFromFile("../Dependencies/Wall.png");
    floor.loadFromFile("../Dependencies/Floor.png");
    m_Textures.insert(std::pair<std::string, sf::Texture>("Brick", brick));
    m_Textures.insert(std::pair<std::string, sf::Texture>("Wall", wall));
    m_Textures.insert(std::pair<std::string, sf::Texture>("Floor", floor));
}

void CreateGraphics::LoadText()
{
    m_Font.loadFromFile("../Dependencies/arial.ttf");
    m_Text.setFont(m_Font);
    m_Text.setCharacterSize(20);
    m_Text.setFillColor(sf::Color::Red);
    m_Text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	m_Text.setString("Current seed used: \n 0");
}
