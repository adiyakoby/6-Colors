#pragma once
#include "Enemy.h"

template<class Shape>
class HardMode : public Enemy {

public:

	HardMode(std::shared_ptr<Graph<Shape>>& graph,std::shared_ptr<Node<Shape>> comp) :
		m_comp{ comp }, game_graph{ graph } {
		;
	}
	virtual ~HardMode() = default;

	/*virtual sf::Color action() override {
		return m_comp->findColorHardMode();
	};*/
	virtual sf::Color action() override {
		std::vector<sf::Color> avail_colors{ game_graph->get_avail_color() };
		std::vector <int> color_count(avail_colors.size(), 0);
		sf::Color color;
		int i{}, max{};
		for (const auto& ea : avail_colors)
		{
			m_comp->getHighest(ea, color_count, i);
			if (color_count.at(i) >= max)
				max = color_count.at(i);
			i++;
		}
	
		
		for (int j = 0; j < color_count.size(); j++)
			if (max == color_count[j])
			{
				if(avail_colors[j] == sf::Color::Magenta)
					std::cout << "returns pink\n";
				return avail_colors[j];
			}
		std::cout << "returns black\n";
		return sf::Color::Black;
	};
	

private:
	std::shared_ptr<Node<Shape>> m_comp;
	std::shared_ptr<Graph<Shape>>& game_graph;
};
