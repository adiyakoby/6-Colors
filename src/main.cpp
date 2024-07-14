#include <iostream>
#include "Controller.h"

int main()
{
	using Shape_type = sf::CircleShape;
	Shape_type my_shape(10.f, 6);
	Controller<Shape_type> control(my_shape);
	control.run_game();

};
