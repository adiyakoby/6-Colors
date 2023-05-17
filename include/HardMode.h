#pragma once
#include "Enemy.h"

template<class Shape>
class HardMode : public Enemy {

public:

	HardMode(std::shared_ptr<Node<Shape>> comp) :
		m_comp{ comp } {
		;
	}
	virtual ~HardMode() = default;

	virtual sf::Color action() override {
		return m_comp->findColorHardMode();
	};

	

private:
	std::shared_ptr<Node<Shape>> m_comp;
};
