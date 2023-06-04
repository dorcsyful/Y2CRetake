// Y2CRetake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
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
    window->UpdateSprites(layout);
    // create the tilemap from the level definition
    TileMap map;
    map.m_Width = WIDTH;
    map.m_Height = HEIGHT;
    map.m_Tiles = layout.m_Tiles;
    if (!map.Load("../Dependencies/tileset.png", sf::Vector2u(32, 32), WIDTH, HEIGHT))
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
                    window->UpdateSprites(layout);
                    window->m_Text.setString("Current seed used: \n" + std::to_string(seed));
                    map.m_Width = WIDTH;
                    map.m_Height = HEIGHT;
                    map.m_Tiles = layout.m_Tiles;
                    if (!map.Load("../Dependencies/tileset.png", sf::Vector2u(32, 32), WIDTH, HEIGHT))
                        return -1;
                }

                if (localPosition.x >= 0 && localPosition.x <= 200 && localPosition.y >= 300 && localPosition.y <= 350)
                {
                    int scale = 10;
                    Image image = Image(WIDTH * scale, HEIGHT * scale);
                    image.Generate(layout.m_Tiles, seed, scale);
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
        window->m_Window->draw(map);

        window->m_Window->display();
    }

    return 0;
}


//int main()
//{
//	for (int i = 0; i < 1; i++)
//	{
//		const int width = 50;
//		const int height = 50;
//		BasicLayout layout = BasicLayout(width, height);
//		layout.Build(0);
//		int scale = 10;
//		Image image = Image(width * scale, height * scale);
//
//		for (int y = 0; y < height; y++)
//		{
//			for (int x = 0; x < width; x++)
//			{
//				Color color;
//				if (layout.m_Tiles[y * width + x] == ETILE_TYPE::TILE_FLOOR) { color = Color(1.f, 1.f, 1.f); }
//				else if (layout.m_Tiles[y * width + x] == ETILE_TYPE::TILE_DOOR) { color = Color(1.f, 0.f, 0.f); }
//				else if (layout.m_Tiles[y * width + x] == ETILE_TYPE::TILE_INTERNAL_WALL) { color = Color(0.f, 1.f, 0.f); }
//				else if (layout.m_Tiles[y * width + x] == ETILE_TYPE::TILE_HALF_WALL) { color = Color(0.f, 0.f, 1.f); }
//				else { color = Color(0.f, 0.f, 0.f); }
//
//				int img_x = x * scale;
//				int img_y = y * scale;
//
//				for (int i = 0; i < scale; i++)
//				{
//					for (int j = 0; j < scale; j++)
//					{
//						image.SetColor(color, img_x + i, img_y + j);
//					}
//				}
//			}
//		}
//		std::string filename = "image";
//		filename.append(std::to_string(i));
//		filename.append(".bmp");
//		if (image.Generate(filename.c_str())) { std::cout << "Image generated"; }
//		else { std::cout << "Image generation failed :("; }
//	}
//}
