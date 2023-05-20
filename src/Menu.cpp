#include "Menu.h"


Menu::Menu(const int& width, const int& height) : m_modes{}, m_background(sf::Quads, 4) {
	this->init_vertex(width,height);
	this->set_textures();
	this->set_menu(width, height);
}


void Menu::init_vertex(const int& width, const int& height) {
	
	m_background[0].position = sf::Vector2f(0, 0);
	m_background[1].position = sf::Vector2f(width, 0);
	m_background[2].position = sf::Vector2f(width, height);
	m_background[3].position = sf::Vector2f(0, height);

	m_background[0].color = sf::Color::Yellow;
	m_background[1].color = sf::Color::Blue;
	m_background[2].color = sf::Color::Red;
	m_background[3].color = sf::Color::Green;
}

void Menu::set_textures() {
	for (size_t i = 0; i < 3; i++)
	{
		m_images_vec.emplace_back();
		switch (i)
		{
		case 0: { m_images_vec.back().loadFromFile("easy.png");    break; }
		case 1: { m_images_vec.back().loadFromFile("medium.png");    break; }
		case 2: { m_images_vec.back().loadFromFile("hard.png");    break; }
		default: break;
		}
	}

}

void Menu::set_menu(const int& width, const int& height) {

	for (size_t i = 0; i < 3; i++)
	{
		m_modes.emplace_back();
		m_modes.back().setSize(sf::Vector2f(100, 100));
		m_modes.back().setPosition(width * 0.5f, height * 0.4f + i*100);
		m_modes.back().setOrigin(m_modes.back().getSize() * 0.5f);
		m_modes.back().setTexture(&m_images_vec.at(i));
	}	
}



void Menu::draw(sf::RenderWindow& window) {
	window.draw(m_background);
	for (auto& ea : m_modes)
		window.draw(ea);
}


menu_state Menu::get_choice(const sf::Vector2f & pos)
{
	for (size_t i = 0; i < 3; i++)
		if (m_modes.at(i).getGlobalBounds().contains(pos))
			return static_cast<menu_state>(i+1);
		
	return menu_state::NONE;
}

