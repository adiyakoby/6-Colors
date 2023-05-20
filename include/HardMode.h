#pragma once
#include "Enemy.h"
#include <array>

template<class Shape>
class HardMode : public Enemy {

public:

	HardMode(Graph<Shape>::GraphIterator it_start) : m_comp_node{ it_start } { ; };
	virtual ~HardMode() = default;

	virtual sf::Color action(const sf::Color& player_color) override ;
	virtual sf::Color get_color()  override { return m_comp_node->get_color(); };
private:
	Graph<Shape>::GraphIterator m_comp_node;
};


template<class Shape>
 sf::Color HardMode<Shape>::action(const sf::Color& player_color)
{
	std::vector<sf::Color> colors{ sf::Color::Red, sf::Color::Magenta, sf::Color::Green,
								   sf::Color::Blue, sf::Color::Yellow, sf::Color::Cyan };
	std::vector<int> colors_count{0,0,0,0,0,0};

	m_comp_node->count_neigh_colors(colors_count);

	for (size_t i = 0; i < colors.size(); i++)
		if (colors.at(i) == m_comp_node->get_color() || colors.at(i) == player_color)
			colors_count.at(i) = 0;

	return colors.at(std::distance(colors_count.begin(), std::max_element(colors_count.begin(), colors_count.end())));
}


