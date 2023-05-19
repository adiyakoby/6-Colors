
#include "Colors.h"
void Colors::setColors() {

	m_frame.setFillColor(sf::Color::White);

	sf::Color arr[6] = { sf::Color::Red, sf::Color::Magenta, sf::Color::Green, 
						 sf::Color::Blue, sf::Color::Yellow, sf::Color::Cyan };

	for (size_t i = 0; i < NUM_OF_COLORS; i++)
		m_buttons.at(i).setFillColor(arr[i]);
}

void Colors::draw_x(const sf::Color& color, const ttpe &type)
{

	int index{};
	if (type == two)
		index += 4;
	
	
	for (auto& c : m_buttons)
	{
		if (c.getFillColor() == color)
		{
			c.setFillColor(sf::Color::Transparent);
			m_lines[index].position = sf::Vector2f(c.getPosition().x - c.getGlobalBounds().width/2, c.getPosition().y - c.getGlobalBounds().height/2);
			m_lines[index+1].position = sf::Vector2f(c.getPosition().x + c.getGlobalBounds().width / 2, c.getPosition().y + c.getGlobalBounds().height / 2);
			m_lines[index+2].position = sf::Vector2f(c.getPosition().x + c.getGlobalBounds().width / 2, c.getPosition().y - c.getGlobalBounds().height / 2);
			m_lines[index+3].position = sf::Vector2f(c.getPosition().x - c.getGlobalBounds().width / 2, c.getPosition().y + c.getGlobalBounds().height / 2);
		}
	}
}

void Colors::drawMenu( sf::RenderWindow& window) {
	for (auto& ea : m_buttons)
		window.draw(ea);
	window.draw(m_lines);
	
}

sf::Color Colors::check_for_color(const float& x, const float& y)
{
	for (auto& ea : m_buttons)
		if (ea.getGlobalBounds().contains(x, y))
			return ea.getFillColor();
	return sf::Color::Black;
}

void Colors::create_vec()
{
	auto x = m_width / 2;
	auto y = m_height * 0.9;
	m_buttons.reserve(NUM_OF_COLORS);
	float delta{ 1.f };

	for (size_t i = 0; i < NUM_OF_COLORS/2; i++)
	{
		if (i == 1) delta = 3.f;
		if (i == 2) delta = 5.f;

		sf::RectangleShape temp(sf::Vector2f(30.f, 30.f));
		temp.setOrigin(temp.getGlobalBounds().width / 2, temp.getGlobalBounds().height / 2);
		temp.setPosition(sf::Vector2f(x - temp.getGlobalBounds().width * delta, y));
		m_buttons.push_back(temp);
		temp.setPosition(sf::Vector2f(x + temp.getGlobalBounds().width * delta, y));
		m_buttons.push_back(temp);
	}
}

