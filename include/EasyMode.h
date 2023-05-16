#pragma once
#include "Enemy.h"

template<class Shape>
class EasyMode : public Enemy {

public:

	EasyMode(std::shared_ptr<Node<Shape>>  ptr_computer) :
		m_computer{ ptr_computer } {
		;
	}
	virtual ~EasyMode() = default;

	virtual sf::Color action() override {

		sf::Color color;
	/*	bool found{ false };
		while (!found)
		{
			color = m_computer->rand_color();
			found = m_computer->find_Color(color);
		}		*/

		return color;
	}
private:
	std::shared_ptr<Node<Shape>> m_computer;
};
