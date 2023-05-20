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
	void draw_background(sf::RenderWindow& window) { window.draw(m_background); };

	menu_state get_choice(const sf::Vector2f& pos) const ;

private:
	std::vector<sf::RectangleShape> m_modes;
	std::vector<sf::Texture> m_images_vec;
	sf::VertexArray m_background;

	//private funcs
	void init_vertex(const int& width, const int& height);
	void set_textures();
	void set_menu(const int& width, const int& hight);

};

