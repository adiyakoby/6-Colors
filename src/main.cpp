#include <iostream>
#include "Graph.h"


#define TEST 2




std::vector<sf::Vector2f> neighbor_func(const sf::Vector2f& pos, const float radius) {

	std::vector<sf::Vector2f> all_neighbors;
	//left and right
	all_neighbors.push_back(sf::Vector2f(pos.x + radius * std::sqrt(3.f), pos.y));
	all_neighbors.push_back(sf::Vector2f(pos.x - radius * std::sqrt(3.f), pos.y));
	//below
	all_neighbors.push_back(sf::Vector2f(pos.x + radius * (std::sqrt(3.f) / 2.f), pos.y + radius * 1.5f));
	all_neighbors.push_back(sf::Vector2f(pos.x - radius * (std::sqrt(3.f) / 2.f), pos.y + radius * 1.5f));
	//above
	all_neighbors.push_back(sf::Vector2f(pos.x + radius * (std::sqrt(3.f) / 2.f), pos.y - radius * 1.5f));
	all_neighbors.push_back(sf::Vector2f(pos.x - radius * (std::sqrt(3.f) / 2.f), pos.y - radius * 1.5f));

	for (auto& ea : all_neighbors) {
		ea.x = std::round(ea.x);
		ea.y = std::round(ea.y);
	}

	return all_neighbors;

};

#if TEST == 0

int main()
{
	/*
	sf::CircleShape t(8, 123);
	sf::CircleShape t4(t);
	t4.setPosition(t.getPosition().x + 2 * t.getRadius() * (std::sqrt(3.f) / 2), t.getPosition().y);

	sf::CircleShape t5( (t.getPosition().x - t4.getPosition().x), (t.getPosition().y - t4.getPosition().y));

	std::cout << t.getRadius() << std::endl;
	std::cout << t4.getRadius() << std::endl;
	std::cout << t5.getRadius() << std::endl;

	sf::Vector2f center1 = t.getPosition() + sf::Vector2f(t.getRadius(), t.getRadius());
	sf::Vector2f center2 = t4.getPosition() + sf::Vector2f(t4.getRadius(), t4.getRadius());

	float distance = std::sqrt(std::pow(center1.x - center2.x, 2) + std::pow(center1.y - center2.y, 2));
	float radiusSum = t.getRadius() + t4.getRadius();

	if (distance <= radiusSum * 2) {
		std::cout << " yes \n";
	}
	//Graph(const Shape& shape, sf::RenderWindow& window, sf::RectangleShape& rectangle) : m_ref_window{ window },
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML Window");
	sf::RectangleShape rect(sf::Vector2f(500, 500));
	rect.setPosition(0, 0);
	sf::CircleShape c(6);
	c.setPosition(0, 0);

	Graph a(c, window, rect);*/


}

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
	srand(20);
	sf::RenderWindow window(sf::VideoMode(800, 800), "TITLE");

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

	/*	std::cout << temp.getPoint(0).x << std::endl;
		std::cout << temp.getPoint(1).x << std::endl;
		std::cout << temp.getPoint(2).x << std::endl;
		std::cout << temp.getPoint(3).x << std::endl;
		std::cout << temp.getPoint(4).x << std::endl;
		std::cout << temp.getPoint(5).x << std::endl;*/

	sf::Vector2f circleSize(temp.getRadius() * 2, temp.getRadius() * 2);
	temp.setOrigin(circleSize / 2.f);
	Graph<sf::CircleShape> my_graph(temp, window, rectangle, neighbor_func);



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
