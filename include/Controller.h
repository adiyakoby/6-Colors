#pragma once
#include "Graph.h"
#include "Colors.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

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

sf::Vector2f get_new_loc(const sf::CircleShape& shape, const bool& right, const bool& down) {

	sf::Vector2f ret_pos{ shape.getPosition() };
	if (!down)
		ret_pos.x = ret_pos.x + 2.f * shape.getRadius() * (std::sqrt(3.f) / 2.f);
	else if (down)
	{
		ret_pos.y = ret_pos.y + (2.f * shape.getRadius()) * 3.f / 4.f;
		if (right)
			ret_pos.x = ret_pos.x + shape.getRadius() * (std::sqrt(3.f) / 2.f);
		else
			ret_pos.x = ret_pos.x - (shape.getRadius() * (std::sqrt(3.f) / 2.f));

	}
	return ret_pos;

};



template<class Shape>
class Controller
{

public:
	Controller(const Shape& shape) : m_window{ sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SixColors" } , m_rect{set_rect()},
		m_color(WINDOW_WIDTH, WINDOW_HEIGHT),
		m_graph(shape, m_window, m_rect , neighbor_func, get_new_loc) {
		
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
	sf::RectangleShape rectangle(sf::Vector2f( WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f));
	rectangle.setOrigin(rectangle.getSize() / 2.f);
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setOutlineThickness(2.f);
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
		 m_window.draw(m_rect); // only for us
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

			 case sf::Event::MouseButtonPressed:
				 auto x = event.mouseButton.x;
				 auto y = event.mouseButton.y;
				 m_graph.paint(m_color.check_for_color(x, y));
				 break;
			 }
		 }
	 }
 }
