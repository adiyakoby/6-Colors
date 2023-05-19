#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum class menu_state { NONE, EASY, MEDIUM, HARD };

class Menu
{
public:
	Menu(const int &width,const int &hight);
	~Menu() = default;

	void draw(sf::RenderWindow &window);
	sf::RectangleShape getscreen() const { return m_modes.at(0); };
	menu_state get_choice(const unsigned int& x, const unsigned int& y) ;

private:
	std::vector<sf::RectangleShape> m_modes;
	std::vector<sf::Texture> m_images_vec;
	sf::VertexArray m_background;


	void init_vertex(const int& width, const int& height);
	void set_textures();
	void set_menu(const int& width, const int& hight);

};

