#pragma once
#include "Enemy.h"

template<class Shape>
class EasyMode : public Enemy {

public:

	EasyMode(Graph<Shape>::GraphIterator it_start) : m_comp_node(it_start) { ; };
	virtual ~EasyMode() = default;

	virtual sf::Color action() override;
	
private:
	Graph<Shape>::GraphIterator m_comp_node;
	sf::Color rand_color() const;

};

template<class Shape>
inline sf::Color EasyMode<Shape>::action()
{
	std::vector<sf::Color> avail_colors{};
	
	m_comp_node->get_neigh_colors(avail_colors);
	std::cout << avail_colors.size() << std::endl;

	return (avail_colors.size() > 0 ? avail_colors[rand() % avail_colors.size()] : sf::Color::Black);
}







template<class Shape>
sf::Color EasyMode<Shape>::rand_color() const {
	int color = rand() % 6;

	if (color == 0) return sf::Color::Blue;
	else if (color == 1) return sf::Color::Green;
	else if (color == 2) return sf::Color::Red;
	else if (color == 3) return sf::Color::Yellow;
	else if (color == 4) return sf::Color::Cyan;
	else return sf::Color::Magenta;
};