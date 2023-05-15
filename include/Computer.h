#pragma once

#include "Node.h"

template<class Shape>
class Computer
{
public:
	Computer();
	virtual ~Computer();

	virtual void action() = 0;
private:

};


