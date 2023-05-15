#pragma once
#include <SFML/Graphics.hpp>
class Colors
{


public:
	Colors(sf::RectangleShape rect, const unsigned width, const unsigned height) : 
		m_width{ width }, m_height{height}, m_frame { rect } {
		this->setSize();
		this->setLocation();
		this->setColors();
		
		
	}
	~Colors() = default;

	void setSize();
	void setColors();
	void setLocation();
	void drawMenu( sf::RenderWindow &w);
private:
	sf::RectangleShape m_frame;
	sf::RectangleShape m_blue;
	sf::RectangleShape m_red;
	sf::RectangleShape m_green;
	sf::RectangleShape m_pink;
	sf::RectangleShape m_yellow;
	sf::RectangleShape m_cyan;
	unsigned int m_width;
	unsigned int m_height;

};

