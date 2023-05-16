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
		std::cout << "action" << std::endl;

		
		bool found{ false };

		sf::Color color = m_computer->rand_color();
		found = m_computer->find_Color(color);
		if (!found) return sf::Color::Black;

		return color;
	}
private:
	std::shared_ptr<Node<Shape>> m_computer;
};
