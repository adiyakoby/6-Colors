#pragma once

#include "Node.h"


class Enemy
{
public:
	Enemy() = default;
	virtual ~Enemy() = default;

	virtual void action() = 0;
private:

};

template<class Shape>
class EasyMode : public Enemy {

public:

	EasyMode(std::shared_ptr<Node<Shape>>  ptr_computer) :
		m_computer{ ptr_computer } {
		;
	}
	virtual ~EasyMode() = default;

	virtual void action() override {
		;
	}
private:
	std::shared_ptr<Node<Shape>> m_computer;
};


