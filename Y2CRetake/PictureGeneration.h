// ReSharper disable CppClangTidyBugproneImplicitWideningOfMultiplicationResult
#pragma once
#include <fstream>
#include <iostream>
#include <vector>

#include "GeneratorProperties.h"

class Color
{
public:
	float m_R, m_G, m_B;

	Color() : m_R(0), m_G(0), m_B(0) {}
	Color(float a_R, float a_G, float a_B) : m_R(a_R), m_G(a_G), m_B(a_B) {}
};

class Image
{
public:
	Image(int a_Width, int a_Height) : m_Width(a_Width), m_Height(a_Height), m_Pixel(std::vector<Color>(a_Width * a_Height)) {}

	Color GetColor(int a_X, int a_Y) const { return m_Pixel[a_Y * m_Width + a_X]; }
    bool SetColor(const Color& a_Color, int a_X, int a_Y);
	bool CreateFile(const char* a_Name);
	void Generate(const std::vector<ETILE_TYPE>& a_Tiles, int a_Seed, int a_Scale = 4);


private:
	int m_Width;
	int m_Height;
	std::vector<Color> m_Pixel;
};

