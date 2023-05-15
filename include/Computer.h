#pragma once

#include "Node.h"

template<class Shape>
class Computer
{
public:
	Computer() { ; };
	virtual ~Computer() = default;

	virtual void action() = 0;
private:

};


template<class Shape>
class CompEasy : public Computer<Shape>{
public:
	CompEasy(std::shared_ptr<Node<Shape>>  ptr_computer) :
		Computer<Shape>(), m_computer{ptr_computer} {
		;
	}
	virtual ~CompEasy() { ; };

	virtual void action() override {
		;
	}
private:
	std::shared_ptr<Node<Shape>> m_computer;
};


