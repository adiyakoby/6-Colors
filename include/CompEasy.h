#pragma once

#include "Computer.h"


template<class Shape>
class CompEasy : public Computer
{
public:
	CompEasy(std::shared_ptr<Node<Shape>>  ptr_computer) :m_computer{ptr_computer} {

	}
	virtual ~CompEasy();

	virtual void action() {
		;
	}
private:
	std::shared_ptr<Node<Shape>> m_computer;
};

