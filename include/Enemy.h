#pragma once

#include "Node.h"


class Enemy
{
public:
	Enemy() = default;
	virtual ~Enemy() = default;

	virtual sf::Color action() = 0;
private:

};

