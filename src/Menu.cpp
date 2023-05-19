#include "Menu.h"


Menu::Menu(int h, int w) : m_h{ h }, m_w{ w }, m_choice{ 0 }, m_modes{} {
	this->set_textures();
	this->set_menu();
}
void Menu::set_textures() {
	for (size_t i = 0; i < 4; i++)
	{
		m_images_vec.emplace_back();
		switch (i)
		{
		case 0: { m_images_vec.back().loadFromFile("screen.png");    break; }
		case 1: { m_images_vec.back().loadFromFile("easy.png");    break; }
		case 2: { m_images_vec.back().loadFromFile("medium.png");    break; }
		case 3: { m_images_vec.back().loadFromFile("hard.png");    break; }
		default: break;
		}
	}

}

void Menu::set_menu() {

	for (size_t i = 0; i < 4; i++)
	{
		m_modes.emplace_back();
		if (i == 0) m_modes.back().setSize(sf::Vector2f(m_w, m_h));
		else {

			m_modes.back().setSize(sf::Vector2f(100, 100));
			m_modes.back().setPosition(m_w / 2, (m_h / 3) + (i*100));
			m_modes.back().setOrigin(m_modes.back().getSize() / 2.0f);
		}
		
		m_modes.back().setTexture(&m_images_vec.at(i));
	}
}



void Menu::draw(sf::RenderWindow& window) {
	for (auto& ea : m_modes)
		window.draw(ea);
}


menu_state Menu::get_choice(const unsigned int& x, const unsigned int& y)
{
	for (size_t i = 1; i < 4; i++)
		if (m_modes.at(i).getGlobalBounds().contains(x, y))
			return static_cast<menu_state>(i);

	return menu_state::NONE;
}

