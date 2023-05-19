#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum class menu_state { NONE, EASY, MEDIUM, HARD };

class Menu
{
public:
	Menu(int h,int w);
	~Menu() = default;

	void draw(sf::RenderWindow &window);
	sf::RectangleShape getscreen() const { return m_modes.at(3); };
	menu_state get_choice(const unsigned int& x, const unsigned int& y) ;

private:
	std::vector<sf::RectangleShape> m_modes;

	std::vector<sf::Texture> m_images_vec;


	int m_h;
	int m_w;
	int m_choice;

	void set_textures();
	void set_menu();

};

