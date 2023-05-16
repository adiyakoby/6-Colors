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
		return color;
	}
private:
	std::shared_ptr<Node<Shape>> m_computer;
};
