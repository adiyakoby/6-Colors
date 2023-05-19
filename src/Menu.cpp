#include "Menu.h"


Menu::Menu(int h, int w) :m_h{ h }, m_w{ w }, m_choice{ 0 } {
	set_menu();
}
Menu::~Menu()  {
	;
}

void Menu::set_menu() {
	if (!m_easy.loadFromFile("easy.png")) {
		;	// Error handling if the image fails to load
	}
	m_easyrect.setTexture(&m_easy);

	if (!m_medium.loadFromFile("medium.png")) {
		;	// Error handling if the image fails to load
	}
	m_mediumrect.setTexture(&m_medium);
	if (!m_hard.loadFromFile("hard.png")) {
		;	// Error handling if the image fails to load
	}
	m_hardrect.setTexture(&m_hard);
	
	if (!m_screen.loadFromFile("screen.png")) {
		;	// Error handling if the image fails to load
	}
	m_screenrect.setTexture(&m_screen);



	m_easyrect.setSize(sf::Vector2f(100, 100));
	m_mediumrect.setSize(sf::Vector2f(100, 100));
	m_hardrect.setSize(sf::Vector2f(100, 100));
	m_screenrect.setSize(sf::Vector2f(m_w, m_h));
	m_easyrect.setPosition(0, 0);

	m_easyrect.setPosition(m_w/2, m_h/3 );
	m_mediumrect.setPosition(m_w / 2, m_easyrect.getPosition().y + 100);
	m_hardrect.setPosition(m_w / 2, m_easyrect.getPosition().y + 200);

	m_easyrect.setOrigin(m_easyrect.getSize() / 2.0f);
	m_mediumrect.setOrigin(m_mediumrect.getSize() / 2.0f);
	m_hardrect.setOrigin(m_hardrect.getSize() / 2.0f);

	

}

void Menu::draw(sf::RenderWindow& w, bool& menu) {


	while (w.isOpen()) {
		w.clear();


		if (auto event = sf::Event{}; w.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed: {
				w.close();
				break;
			}

			case sf::Event::MouseButtonPressed:
				sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
					if (m_easyrect.getGlobalBounds().contains(mousePos))
					{
						m_choice = 1;
						menu = false;
						return;

					}
					else if (m_mediumrect.getGlobalBounds().contains(mousePos))
					{
						m_choice = 2;
						menu = false;
						return;

					}
					else if (m_hardrect.getGlobalBounds().contains(mousePos))
					{
						m_choice = 3;
						menu = false;
						return;
					}
					break;
				}
			}
			w.draw(m_screenrect);
			w.draw(m_easyrect);
			w.draw(m_mediumrect);
			w.draw(m_hardrect);
			w.display();
		}
	}
	
}


