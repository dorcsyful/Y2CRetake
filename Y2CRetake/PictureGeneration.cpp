// ReSharper disable CppClangTidyBugproneImplicitWideningOfMultiplicationResult
#pragma once
#include "PictureGeneration.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool Image::SetColor(const Color& a_Color, int a_X, int a_Y)
{
	if (a_X < m_Width && a_Y < m_Height) { m_Pixel[a_Y * m_Width + a_X] = a_Color; return true; }
	return false;
}
bool Image::CreateFile(const char* a_Name)
{
    std::ofstream file;
    file.open(a_Name, std::ios::out | std::ios::binary);

    if (!file.is_open()) { return false; }

    unsigned char bmp_pad[3] = { 0,0,0 };
    int paddingAmount = ((4 - (m_Width * 3) % 4) % 4);

    const int file_header_size = 14;
    const int information_header_size = 40;
    const int file_size = file_header_size + information_header_size + m_Width * m_Height * 3 + paddingAmount * m_Height;

    unsigned char file_header[file_header_size];

    file_header[0] = 'B';
    file_header[1] = 'M';
    file_header[2] = file_size;
    file_header[3] = file_size >> 8;
    file_header[4] = file_size >> 16;
    file_header[5] = file_size >> 24;
    file_header[6] = 0;
    file_header[7] = 0;
    file_header[8] = 0;
    file_header[9] = 0;
    file_header[10] = file_header_size + information_header_size;
    file_header[11] = 0;
    file_header[12] = 0;
    file_header[13] = 0;

    unsigned char information_header[information_header_size];

    information_header[0] = information_header_size;
    information_header[1] = 0;
    information_header[2] = 0;
    information_header[3] = 0;
    information_header[4] = m_Width;
    information_header[5] = m_Width >> 8;
    information_header[6] = m_Width >> 16;
    information_header[7] = m_Width >> 24;
    information_header[8] = m_Height;
    information_header[9] = m_Height >> 8;
    information_header[10] = m_Height >> 16;
    information_header[11] = m_Height >> 24;
    information_header[12] = 1;
    information_header[13] = 0;
    information_header[14] = 24;
    information_header[15] = 0;
    information_header[16] = 0;
    information_header[17] = 0;
    information_header[18] = 0;
    information_header[19] = 0;
    information_header[20] = 0;
    information_header[21] = 0;
    information_header[22] = 0;
    information_header[23] = 0;
    information_header[24] = 0;
    information_header[25] = 0;
    information_header[26] = 0;
    information_header[27] = 0;
    information_header[28] = 0;
    information_header[29] = 0;
    information_header[30] = 0;
    information_header[31] = 0;
    information_header[32] = 0;
    information_header[33] = 0;
    information_header[34] = 0;
    information_header[35] = 0;
    information_header[36] = 0;
    information_header[37] = 0;
    information_header[38] = 0;
    information_header[39] = 0;

    file.write(reinterpret_cast<char*>(file_header), file_header_size);
    file.write(reinterpret_cast<char*>(information_header), information_header_size);

    for (int y = m_Height - 1; y >= 0; y--)
    {
        for (int x = 0; x < m_Width; x++)
        {
            unsigned char red = static_cast<unsigned char>(GetColor(x, y).m_R * 255.f);
            unsigned char green = static_cast<unsigned char>(GetColor(x, y).m_G * 255.f);
            unsigned char blue = static_cast<unsigned char>(GetColor(x, y).m_B * 255.f);

            unsigned char color[] = { blue,green,red };
            file.write(reinterpret_cast<char*>(color), 3);
        }
        file.write(reinterpret_cast<char*>(bmp_pad), paddingAmount);
    }
    file.close();
    return true;
}

void Image::Generate(const std::vector<ETILE_TYPE>& a_Tiles, int a_Seed, int a_Scale)
{

    for (int y = HEIGHT - 1; y >= 0; y--)
		{
			for (int x = 0; x < WIDTH; x++)
			{
				Color color;
				if (a_Tiles[y * WIDTH + x] == ETILE_TYPE::TILE_FLOOR) { color = Color(1.f, 1.f, 1.f); }
				else if (a_Tiles[y * WIDTH + x] == ETILE_TYPE::TILE_MAZE_WALL) { color = Color(0.f, 1.f, 0.f); }
				else if (a_Tiles[y * WIDTH + x] == ETILE_TYPE::TILE_BSP_WALL) { color = Color(0.f, 0.f, 1.f); }
				else { color = Color(0.f, 0.f, 0.f); }

				int img_x = x * a_Scale;
				int img_y = y * a_Scale;

				for (int i = 0; i < a_Scale; i++)
				{
					for (int j = 0; j < a_Scale; j++)
					{
						SetColor(color, img_x + i, img_y + j);
					}
				}
			}
		}
		std::string filename = "image";
		filename.append(std::to_string(a_Seed));
		filename.append(".bmp");
		if (CreateFile(filename.c_str())) { std::cout << "Image generated"; }
		else { std::cout << "Image generation failed :("; }
}
