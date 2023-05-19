#pragma once

#include "Graph.h"
#include "Colors.h"
#include "EasyMode.h"
#include "HardMode.h"
#include "MedMode.h"
#include "Painter.h"


const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;

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
		ea.x = ea.x;
		ea.y = ea.y;
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
	Controller(const Shape& shape) : m_window{ sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SixColors" }, m_rect{ set_rect() },
		m_color(WINDOW_WIDTH, WINDOW_HEIGHT),
		m_graph(std::make_shared<Graph<Shape>>(shape, m_window, m_rect, neighbor_func, get_new_loc)),
		m_enemy{ std::make_unique<EasyMode<Shape>>(m_graph->computer_begin()) },
		m_painter{ m_window }
		
	{
		m_painter.set_start_it(m_graph->begin());
		m_painter.set_end_it(m_graph->end());
	};
	~Controller () = default;

	
	void run_game();

	void Game_turns(const unsigned int& x, const unsigned int& y);
	
private:
	sf::RenderWindow m_window;
	Painter<Shape> m_painter;
	sf::RectangleShape m_rect;
	Colors m_color;

	std::shared_ptr<Graph<Shape>> m_graph;
	std::unique_ptr<Enemy> m_enemy;

	//private functions
	sf::RectangleShape set_rect();
	sf::Color color_choosed(const unsigned int& x, const unsigned int& y);
	
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
 sf::Color Controller<Shape>::color_choosed(const unsigned int& x, const unsigned int& y)
 {
	 sf::Color color_clicked = m_color.check_for_color(x, y);
	 
	 if (color_clicked != sf::Color::Black && color_clicked != sf::Color::Transparent)
	 {
		 m_color.draw_x(color_clicked, one);
		 m_graph->attach_nodes(color_clicked, Player);
	 }
		 
	 return color_clicked;
 }

 template<class Shape>
 inline void Controller<Shape>::run_game()
 {
	 //std::srand(26665656);
	 bool menu{ false };

	 while (m_window.isOpen()) {
		 m_window.clear();

		 if (menu);
		 else {
			 //m_window.draw(m_rect); // only for debugging
			 m_painter.draw_graph();
			 m_color.drawMenu(m_window);
		 }
		 m_window.display();
		 

		 if (auto event = sf::Event{}; m_window.waitEvent(event))
		 {
			 switch (event.type)
			 {
			 case sf::Event::Closed: {
				 m_window.close();
				 break;
			 }
			 case sf::Event::Resized:
			 {
				// m_window.getViewport(m_window.getView());
				 break;
			 }

			 case sf::Event::MouseButtonPressed:
				 Game_turns(event.mouseButton.x, event.mouseButton.y);
				 break;
			 }
		 }
	 }
 }

 template<class Shape>
 inline void Controller<Shape>::Game_turns(const unsigned int &x, const unsigned int& y)
 {
	 m_color.setColors();
	 //player turn
	 sf::Color player_choice = color_choosed(x, y);

	 //computer turn
	 sf::Color comp_choice;
	 if (player_choice != sf::Color::Black) {
		 do
		 {
			 comp_choice = m_enemy->action(player_choice);
			 m_graph->unvisit_nodes();
		 } while (comp_choice == sf::Color::Black);
		 m_color.draw_x(comp_choice, two);
		 m_graph->attach_nodes(comp_choice, Computer);
	 }
 }
