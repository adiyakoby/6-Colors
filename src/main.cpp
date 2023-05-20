#include <iostream>
#include "Controller.h"

#define TEST 0




#if TEST == 0

int main()
{
	using Shape_type = sf::CircleShape;
	Shape_type my_shape(20.f, 6);
	Controller<Shape_type> control(my_shape);
	control.run_game();

};

#endif // TEST == 0




#if TEST == 1
int main()
{



	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(800, 800), "TITLE");
	//sf::View window_view(sf::Vector2f{0.f, 0.f }, sf::Vector2f(window.getSize().x *1.f, window.getSize().y * 1.f));
	//std::cout << window_view.getCenter().x << " " << window_view.getCenter().y << std::endl;
	//std::cout << window_view.getSize().x << " " << window_view.getSize().y << std::endl;
	//window.setView(window_view);

	sf::RectangleShape rectangle(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f));
	rectangle.setOrigin(rectangle.getSize() / 2.f);
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineColor(sf::Color::Black);
	rectangle.setOutlineThickness(10.f);
	rectangle.setPosition(rectangle.getSize());


	std::cout << "coords: x:" << rectangle.getPosition().x << " y: " << rectangle.getPosition().y << std::endl;

	sf::CircleShape temp(15.f, 6);
	temp.setOutlineColor(sf::Color::Black);
	temp.setOutlineThickness(1.f);
	temp.setPosition(100, 100);
	Graph<sf::CircleShape> my_graph(temp, window, rectangle);
	//rectangle.getGlobalBounds().intersects(temp.getGlobalBounds());

	sf::View window_full_view({ 0.f, 0.f }, sf::Vector2f(window.getSize().x * 1.f, window.getSize().y * 1.f));
	window_full_view.setViewport({ 0.f, 0.f, 1.f, 1.f });
	window_full_view.setCenter(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f));
	//window.setView(window_full_view);



	while (window.isOpen()) {
		window.clear();

		//drawing
		my_graph.draw();

		window.draw(rectangle);

		window.display();

		if (auto event = sf::Event{}; window.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
	}

}
#endif // TEST == 1

//TEST == 2
#if TEST == 2

int main()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(800, 800), "TITLE");

	sf::RectangleShape rectangle(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f));
	rectangle.setOrigin(rectangle.getSize() / 2.f);
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setOutlineThickness(10.f);
	rectangle.setPosition(rectangle.getSize());
	//rectangle.setFillColor(sf::Color::White);

	std::cout << "coords: x:" << rectangle.getPosition().x << " y: " << rectangle.getPosition().y << std::endl;

	sf::CircleShape temp(10.f, 6);
	temp.setOutlineColor(sf::Color::Black);
	temp.setOutlineThickness(1.f);
	temp.setPosition(100, 100);
	//temp.getOrigin()
	//temp.setOrigin(temp.getRadius() / 2.f, temp.getRadius() / 2.f);
	//temp.getGlobalBounds().width();
	//temp.getGlobalBounds().height();
	//rectangle.getGlobalBounds().top
	
	



	Graph<sf::CircleShape> my_graph(temp, window, rectangle, neighbor_func, get_new_loc);



	while (window.isOpen()) {
		window.clear();

		//drawing
		my_graph.draw();

		window.draw(rectangle);

		window.display();

		if (auto event = sf::Event{}; window.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed: {
				window.close();
				break;
			}
			case sf::Event::MouseButtonReleased:
				auto x = event.mouseButton.x;
				auto y = event.mouseButton.y;
				my_graph.paint(window.mapPixelToCoords({ x,y }));


			}
		}
	}

}


#endif



//sf::RenderWindow window(sf::VideoMode(1000, 1000), "TITLE");

//sf::CircleShape circle(30.f, 6);
//circle.setOrigin(circle.getRadius() , circle.getRadius() );
//circle.setPosition(0, 0);

//sf::CircleShape circle2(30.f, 6);
//circle2.setOrigin(circle2.getRadius() , circle2.getRadius() );
//circle2.setPosition(circle.getPosition().x + 2*circle.getRadius()*(std::sqrt(3.f)/2), circle.getPosition().y);
//circle2.setFillColor(sf::Color::Blue);

//sf::CircleShape circle3(30.f, 6);
//circle3.setOrigin(circle3.getRadius(), circle3.getRadius());
//circle3.setPosition(circle.getPosition().x + circle.getRadius() * (std::sqrt(3.f) / 2), circle.getPosition().y + (2*circle.getRadius())*3/4);
//circle3.setFillColor(sf::Color::Red);

//// circ3_Height = cicrcle1_Height + circle1_Radius*3/4
//// Radius below 
//sf::View board_view(sf::Vector2f{0,0} , sf::Vector2f(window.getSize().x, window.getSize().y ));
////board_view.setViewport({ 0.f, 0.f, 1.f, 1.f });
//
//
