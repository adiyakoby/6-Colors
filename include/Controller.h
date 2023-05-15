#pragma once
#include "Graph.h"
#include "Colors.h"
const int WIDTH = 10;
const int HEIGHT = 10;

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



template<class Shape>
class Controller
{

public:
	Controller(const Shape& shape) : m_window{ sf::VideoMode(800, 800), "SixColors" } , m_rect{set_rect()},
		m_color(sf::RectangleShape(sf::Vector2f(800.f,200.f)),m_window.getSize().x, m_window.getSize().y),
		m_graph(shape, m_window,m_rect , neighbor_func) {
		
	}
	~Controller () = default;
	void run_game();
	
private:
	sf::RenderWindow m_window;
	sf::RectangleShape m_rect;
	Colors m_color;
	Graph<Shape> m_graph;
	
	
	//private functions
	sf::RectangleShape set_rect();
	
};



template<class Shape>
 sf::RectangleShape Controller<Shape>::set_rect()
{
	sf::RectangleShape rectangle(sf::Vector2f(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f));
	rectangle.setOrigin(rectangle.getSize() / 2.f);
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineColor(sf::Color::Black);
	rectangle.setOutlineThickness(10.f);
	rectangle.setPosition(rectangle.getSize());
	return rectangle;
}

 template<class Shape>
 inline void Controller<Shape>::run_game()
 {
	 std::cout << "rungame\n";
	 while (m_window.isOpen()) {
		 m_window.clear();

		 //drawing
		 m_graph.draw();
		 m_window.draw(m_rect);
		 m_color.drawMenu(m_window);
		 m_window.display();

		 if (auto event = sf::Event{}; m_window.waitEvent(event))
		 {
			 switch (event.type)
			 {
			 case sf::Event::Closed: {
				 m_window.close();
				 break;
			 }
			 case sf::Event::MouseButtonReleased:
				 auto x = event.mouseButton.x;
				 auto y = event.mouseButton.y;
				 m_graph.paint(m_window.mapPixelToCoords({ x,y }));


			 }
		 }
	 }
 }
