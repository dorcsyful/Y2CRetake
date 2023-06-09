// Y2CRetake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <string>

#include "PictureGeneration.h"
#include "BasicLayout.h"

#include <SFML/Graphics.hpp>

#include "CreateGraphics.h"
#include "TileMap.h"

int main()
{
	BasicLayout layout;
    int seed = 0;
	layout.Build(seed);

    std::unique_ptr<CreateGraphics> window = std::make_unique<CreateGraphics>();
    window->CreateWindow();
    // create the tilemap from the level definition
    TileMap map;

    map.m_Tiles = layout.m_Tiles;
    if (!map.Load("../Dependencies/tileset.png", sf::Vector2u(32, 32)))
        return -1;

    while (window->m_Window->isOpen())
    {
        sf::Event event;
        while (window->m_Window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->m_Window->close();
            if(event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(*window->m_Window);
                if(localPosition.x >= 0 && localPosition.x <= 200 && localPosition.y >= 200 && localPosition.y <= 250)
                {
                    seed++;
                    layout.Build(seed);
                    window->m_Text.setString("Current seed used: \n" + std::to_string(seed));

                    map.m_Tiles = layout.m_Tiles;
                    if (!map.Load("../Dependencies/tileset.png", sf::Vector2u(32, 32)))
                        return -1;
                }

                if (localPosition.x >= 0 && localPosition.x <= 200 && localPosition.y >= 300 && localPosition.y <= 350)
                {
                    int scale = 10;
                    Image image = Image(WIDTH * scale, HEIGHT * scale);
                    image.Generate(layout.m_Tiles, seed, scale);
                }
                if (localPosition.x >= 0 && localPosition.x <= 200 && localPosition.y >= 600 && localPosition.y <= 650)
                {
                    std::vector<BasicLayout> layouts(1000);
                    std::clock_t begin_time = std::clock();
                    for(int i = 0; i < 1000; i++)
                    {
                        layouts[i].Build(i);
                    }
                    std::clock_t end_time = std::clock();
                    double execution_time = (double)(end_time - begin_time) / CLOCKS_PER_SEC;
                    std::cout << "Execution time for 1000 maps: " << std::to_string(execution_time) << std::endl;
                    
                }
            }
        }
        window->m_Window->clear();
        window->m_Window->draw(window->m_Background);

        window->m_Window->draw(window->m_Text);
        window->m_Window->draw(window->m_RegenerateButtonBox);
        window->m_Window->draw(window->m_RegenerateButtonText);
        window->m_Window->draw(window->m_GenerateImageBox);
        window->m_Window->draw(window->m_GenerateImageText);
        window->m_Window->draw(window->m_BenchmarkBox);
        window->m_Window->draw(window->m_BenchmarkText);
        window->m_Window->draw(map);

        window->m_Window->display();
    }
    return 0;
}
