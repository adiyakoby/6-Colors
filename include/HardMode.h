#pragma once
#include "Enemy.h"

template<class Shape>
class HardMode : public Enemy {

public:

	HardMode(std::shared_ptr<Graph<Shape>>& graph, std::shared_ptr<Node<Shape>> comp) : m_comp{ comp }, game_graph{ graph } { ; };

	virtual ~HardMode() = default;

	virtual sf::Color action() override ;
	

private:
	std::shared_ptr<Node<Shape>> m_comp;
	std::shared_ptr<Graph<Shape>>& game_graph;
};



//template<class Shape>
//inline sf::Color HardMode<Shape>::action()
//{
//	std::vector<sf::Color> avail_colors{ game_graph->get_avail_color() };
//	std::vector <int> color_count(avail_colors.size(), 0);
//	sf::Color color;
//	int i{}, max{};
//
//	for (const auto& ea : avail_colors){
//		m_comp->getHighest(ea, color_count, i);
//		if (color_count.at(i) > max && avail_colors[i] != m_comp->get_color())
//			max = color_count.at(i);
//		game_graph->unvisit_nodes();
//		i++;
//	}
//
//
//	for (int j = 0; j < color_count.size(); j++)
//		if (max == color_count[j])
//				return avail_colors[j];
//		return sf::Color::Black;
//};

template<class Shape>
inline sf::Color HardMode<Shape>::action()
{
	std::vector<sf::Color> avail_colors{ game_graph->get_avail_color() };
	std::vector <int> color_count(avail_colors.size(), 0);
	sf::Color color;
	int i{}, max{};


	for (int i = 0; i < avail_colors.size(); ++i) {
		color_count[i] = m_comp->getHighest(avail_colors.at(i));
		if (color_count.at(i) > max && avail_colors[i] != m_comp->get_color())
			max = color_count.at(i);
		game_graph->unvisit_nodes();
	}
	
	for (int j = 0; j < color_count.size(); j++)
		if (max == color_count[j])
			return avail_colors[j];
	return sf::Color::Black;
};