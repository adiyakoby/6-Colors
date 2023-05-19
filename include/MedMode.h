#pragma once
#include "Enemy.h"

template<class Shape>
class MedMode : public Enemy {

public:
	MedMode(Graph<Shape>::GraphIterator it_start) : m_comp_node{ it_start } { ; };
	virtual ~MedMode() = default;

	virtual sf::Color action(const sf::Color& player_color) override;
	virtual sf::Color get_color()  override { return m_comp_node->get_color(); };

private:
	Graph<Shape>::GraphIterator m_comp_node;
};




template<class Shape>
 sf::Color MedMode<Shape>::action(const sf::Color& player_color)
{
	std::vector<sf::Color> avail_colors{player_color};
	m_comp_node->get_neigh_colors(avail_colors);

	std::erase_if(avail_colors, [&](const auto& c) {return (c == player_color || c == m_comp_node->get_color()); });

	return ( avail_colors.size() > 0 ? avail_colors.at(0) : sf::Color::Black);
}
