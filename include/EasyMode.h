#pragma once
#include "Enemy.h"

template<class Shape>
class EasyMode : public Enemy {

public:

	EasyMode(Graph<Shape>::GraphIterator it_start) : m_comp_node(it_start) { ; };
	virtual ~EasyMode() = default;

	virtual sf::Color action() override;

	std::vector<sf::Color> get_avail_color();

	sf::Color rand_color() const;

private:
	Graph<Shape>::GraphIterator const m_comp_node;

};

template<class Shape>
inline sf::Color EasyMode<Shape>::action()
{
	bool found{ false };
	std::vector<sf::Color> avail_colors{ get_avail_color() };

	sf::Color color = rand_color();
	for (auto& c : avail_colors)
		if (c == color)
			return color;

	return (avail_colors.size() > 0 ? avail_colors[0] : color);
	
}

template<class Shape>
inline std::vector<sf::Color> EasyMode<Shape>::get_avail_color()
{
	std::vector<sf::Color> ret_vec{};
	//DO BFS

	for (auto& ea : m_map)
		if (ea.second->get_owner() == Natural && ea.second->is_comp_attached())
			if (std::find(ret_vec.begin(), ret_vec.end(), ea.second->get_color()) == ret_vec.end())
				ret_vec.push_back(ea.second->get_color());

	return ret_vec;
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