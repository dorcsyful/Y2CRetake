#pragma once
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

class BasicLayout;

class CreateGraphics
{
public:
	CreateGraphics() = default;
	~CreateGraphics() = default;

	void CreateWindow();
	void UpdateSprites(const BasicLayout& a_Layout);

	void CreateRegerateButton();
	void CreateImageGenerateButton();
	int m_SpriteSize = 32;
	std::shared_ptr<sf::RenderWindow> m_Window;
	std::vector<sf::RectangleShape> m_Sprites;
	sf::Text m_Text;
	sf::Text m_RegenerateButtonText;
	sf::RectangleShape m_RegenerateButtonBox;
	sf::RectangleShape m_Background;

	sf::Text m_GenerateImageText;
	sf::RectangleShape m_GenerateImageBox;

private:
	void LoadTextures();
	void LoadText();


	std::map<std::string, sf::Texture> m_Textures;
	sf::Font m_Font;
};

