#pragma once
#include "Enemy.h"

template<class Shape>
class MedMode : public Enemy {

public:
	MedMode(Graph<Shape>::GraphIterator it_start) : m_comp_node{ it_start } { ; };
	virtual ~MedMode() = default;

	virtual sf::Color action() override;

private:
	Graph<Shape>::GraphIterator m_comp_node;
};




template<class Shape>
 sf::Color MedMode<Shape>::action()
{
	std::vector<sf::Color> avail_colors{};
	m_comp_node->get_neigh_colors(avail_colors);

	return ( !avail_colors.empty() ? avail_colors.at(0) : sf::Color::Black);
}
