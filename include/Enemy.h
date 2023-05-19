#pragma once

//#include "Node.h"
#include "Graph.h"

class Enemy
{
public:
	Enemy() = default;
	virtual ~Enemy() = default;

	virtual sf::Color action(const sf::Color & player_color) = 0;
	virtual sf::Color get_color()  = 0;
private:

};

