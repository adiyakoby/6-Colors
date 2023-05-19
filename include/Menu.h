#pragma once
#include <SFML/Graphics.hpp>

class Menu
{
public:
	Menu(int h,int w);
	~Menu();
	void draw(sf::RenderWindow &w, bool &menu);
	sf::RectangleShape getscreen() { return m_screenrect; };
	int get_choice() { return m_choice; };
private:
	sf::RectangleShape m_easyrect;
	sf::RectangleShape m_mediumrect;
	sf::RectangleShape m_hardrect;
	sf::RectangleShape m_screenrect;

	sf::Texture m_easy;
	sf::Texture m_medium;
	sf::Texture m_hard;
	sf::Texture m_screen;

	int m_h;
	int m_w;
	int m_choice;
	void set_menu();

};

