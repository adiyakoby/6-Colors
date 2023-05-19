#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum ttpe { one, two };

const int NUM_OF_COLORS = 6;

class Colors
{
public:
	Colors(const unsigned width, const unsigned height) : m_buttons{},
		m_width{ width }, m_height{height}, m_lines(sf::Lines, 8)
	{
		this->create_vec();
		this->setColors();
			
	}
	~Colors() = default;

	void setColors();
	void draw_colors(sf::RenderWindow& w);
	void draw_x(const sf::Color& color, const ttpe& type);
	sf::Color check_for_color(const float& x, const float& y);

	

private:
	std::vector<sf::RectangleShape> m_buttons;
	sf::RectangleShape m_frame;
	sf::VertexArray m_lines;

	unsigned int m_width;
	unsigned int m_height;

	//private funcs
	void create_vec();
	
	

};

