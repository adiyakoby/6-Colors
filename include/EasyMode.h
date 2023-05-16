#pragma once
#include "Enemy.h"

template<class Shape>
class EasyMode : public Enemy {

public:

	EasyMode(std::shared_ptr<Graph<Shape>> & graph) :
		game_graph{ graph } {
		;
	}
	virtual ~EasyMode() = default;

	virtual sf::Color action() override {
		std::cout << "action" << std::endl;


		bool found{ false };
		std::vector<sf::Color> avail_colors{ game_graph->get_avail_color() };

		sf::Color color = rand_color();
		for (auto& c : avail_colors)
		{
			if (c == color)
				return color;
		}
		//found = m_computer->find_Color(color);
		return (avail_colors.size() > 0 ? avail_colors[0] : color);


	};

	sf::Color rand_color() const;

private:
	std::shared_ptr<Graph<Shape>> & game_graph;
};

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