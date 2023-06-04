#include "CreateGraphics.h"

#include "GeneratorProperties.h"
#include "BasicLayout.h"
void CreateGraphics::CreateWindow()
{

    m_Background.setFillColor(sf::Color(218, 218, 218));
    m_Background.setSize(sf::Vector2<float>(WIDTH * m_SpriteSize + 200, HEIGHT * m_SpriteSize));
    m_Window = std::make_shared<sf::RenderWindow>(sf::VideoMode(WIDTH * m_SpriteSize + 200, HEIGHT * m_SpriteSize), "Warfair level generator");
    LoadText();
    CreateRegerateButton();
    CreateImageGenerateButton();
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

void CreateGraphics::LoadText()
{
    m_Font.loadFromFile("../Dependencies/arial.ttf");
    m_Text.setFont(m_Font);
    m_Text.setCharacterSize(20);
    m_Text.setFillColor(sf::Color::Red);
    m_Text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	m_Text.setString("Current seed used: \n 0");
}
