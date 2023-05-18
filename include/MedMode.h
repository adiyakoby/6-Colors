#pragma once
#include "Enemy.h"

template<class Shape>
class MedMode : public Enemy {

public:
	MedMode(std::shared_ptr<Graph<Shape>>& graph) :
		game_graph{ graph } {
		;
	}
	virtual ~MedMode() = default;
	virtual sf::Color action() override;

private:
	std::shared_ptr<Graph<Shape>>& game_graph;
};


template<class Shape>
inline sf::Color MedMode<Shape>::action()
{
	std::vector<sf::Color> avail_colors{ game_graph->get_avail_color() };
	if (!avail_colors.empty())
		return avail_colors.at(0);

	return sf::Color::Black;

}

