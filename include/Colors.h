#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


const int NUM_OF_COLORS = 6;

class Colors
{
public:
	Colors(const unsigned width, const unsigned height) : m_buttons{},
		m_width{ width }, m_height{height} {
		this->create_vec();
		this->setColors();
			
	}
	~Colors() = default;


	void drawMenu(sf::RenderWindow& w);

	sf::Color check_for_color(const float& x, const float& y);

	

private:
	std::vector<sf::RectangleShape> m_buttons;
	sf::RectangleShape m_frame;

	unsigned int m_width;
	unsigned int m_height;

	//private funcs
	void create_vec();
	void setColors();
	

};

