#pragma once

#include "Colors.h"
#include "EasyMode.h"
#include "HardMode.h"
#include "MedMode.h"
#include "Painter.h"




std::vector<sf::Vector2f> neighbor_func(const sf::Vector2f& pos, const float &radius) {

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

	return all_neighbors;

};


sf::Vector2f get_new_loc(const sf::CircleShape& shape, const bool& right, const bool& down) {

	sf::Vector2f ret_pos{ shape.getPosition() };
	if (!down)
		ret_pos.x = (ret_pos.x +  shape.getRadius() * std::sqrt(3.f));
	else if (down)
	{
		ret_pos.y = (ret_pos.y + ( shape.getRadius() * 1.5f));
		if (right)
			ret_pos.x = (ret_pos.x + shape.getRadius() * (std::sqrt(3.f) / 2.f));
		else
			ret_pos.x = (ret_pos.x - (shape.getRadius() * (std::sqrt(3.f) / 2.f)));

	}
	return ret_pos;
};


enum class game_state {CONT, WON, LOST, NEW};

template<class Shape>
class Controller
{

public:
	Controller(const Shape& shape) : m_window{ sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SixColors" }, m_rect{ set_rect() }, m_shape{shape},
		m_graph(std::make_unique<Graph<Shape>>(shape, m_rect, neighbor_func, get_new_loc)),
		m_painter{m_window}
	{
		m_painter.set_start_it(m_graph->begin());
		m_painter.set_end_it(m_graph->end());
	};
	~Controller () = default;

	
	void run_game();
	
	
private:
	sf::CircleShape m_shape;
	sf::RenderWindow m_window;
	Painter<Shape> m_painter;
	sf::RectangleShape m_rect;
	//Colors m_color;

	std::unique_ptr<Graph<Shape>> m_graph;
	std::unique_ptr<Enemy> m_enemy;

	//private functions
	sf::RectangleShape set_rect();
	sf::Color color_choosed(const unsigned int& x, const unsigned int& y);
	game_state get_stats();
	void Game_turns(const unsigned int& x, const unsigned int& y);
	bool check_mode(const menu_state& state);

	game_state get_game_state(const sf::Vector2f& pos);
	void re_init_game();
	
};



template<class Shape>
 sf::RectangleShape Controller<Shape>::set_rect()
{
	sf::RectangleShape rectangle(sf::Vector2f( WINDOW_WIDTH * 0.7f, WINDOW_HEIGHT * 0.7f));
	rectangle.setOrigin(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f);
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setOutlineThickness(2.f);
	rectangle.setPosition(rectangle.getSize());
	return rectangle;
}

 template<class Shape>
 sf::Color Controller<Shape>::color_choosed(const unsigned int& x, const unsigned int& y)
 {
	 sf::Color color_clicked = m_painter.check_for_color(x, y);
		
	 if (color_clicked != sf::Color::Transparent)
	 {
		 m_painter.draw_x(color_clicked, Owner::Player);
		 m_graph->attach_nodes(color_clicked, Owner::Player);
	 }
		 
	 return color_clicked;
 }
 
 template<class Shape>
 game_state Controller<Shape>::get_stats() {
	 float player{}, comp{}, natural{};
	 for (auto it = m_graph->begin() ; it != m_graph->end() ; it++)
	 {
		 if (it->get_owner() == Owner::Player)
			 player++;
		 else if (it->get_owner() == Owner::Computer)
			 comp++;
		 else if (it->get_owner() == Owner::Natural)
			 natural++;
	 }

	 m_painter.update_stats(player, comp, natural);
	 if (player >= 0.5f)
		 return game_state::WON;
	 else if (comp >= 0.5f)
		 return game_state::LOST;
	 else return game_state::CONT;
 }

 template<class Shape>
 bool Controller<Shape>::check_mode(const menu_state& state)
 {
	if(state == menu_state::EASY)
		m_enemy = std::make_unique<EasyMode<Shape>>(m_graph->computer_begin());

	else if (state == menu_state::MEDIUM )
		m_enemy = std::make_unique<MedMode<Shape>>(m_graph->computer_begin());

	else if ( state ==  menu_state::HARD) 
		m_enemy = std::make_unique<HardMode<Shape>>(m_graph->computer_begin());
	 
	return !(state != menu_state::NONE ? true : false);
 }

 template<class Shape>
 inline void Controller<Shape>::run_game()
 {
	std::srand(time(NULL));
	bool menu{ true };

	while (m_window.isOpen()) {

		 m_window.clear();

		 if (menu) m_painter.draw_menu();
		 else m_painter.draw_graph();
		 
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
				 if (menu) 
					 menu = check_mode(m_painter.get_mode(m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y })));
				 
				 else
				 {
					 Game_turns(event.mouseButton.x, event.mouseButton.y);

					 game_state state{ get_game_state(m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y })) };
					 switch (state)
					 {
					 case game_state::CONT: {  break; }
					 case game_state::WON: {  break; }
					 case game_state::LOST: {  break; }
					 case game_state::NEW: { menu = true; re_init_game(); break; }
					 default: break;
					 }
				 }
				 
				 //get_stats(); 
				 break;
				 
			 }
		 }
	 }
 }
 template<class Shape>
 game_state Controller<Shape>::get_game_state(const sf::Vector2f& pos)
 {
	 game_state state{ get_stats() };
	 bool new_game{ m_painter.is_new(pos) };

	 return (new_game ? game_state::NEW : state);
 };


 template<class Shape>
 inline void Controller<Shape>::Game_turns(const unsigned int &x, const unsigned int& y)
 {
	 //player turn
	 sf::Color player_choice = color_choosed(x, y);
	 
	 //computer turn
	 sf::Color comp_choice;
	 if (player_choice != sf::Color::Transparent) {
		 do 
		 {
			 comp_choice = m_enemy->action(player_choice);
			 m_graph->unvisit_nodes();
		 } while (comp_choice == sf::Color::Black);
		 m_painter.draw_x(comp_choice, Owner::Computer);
		 m_graph->attach_nodes(comp_choice, Owner::Computer);		
	 }	 
 }


 template<class Shape>
 inline void Controller<Shape>::re_init_game()
 {
	 m_graph = Graph();
	 m_graph->reset_graph(m_shape, m_rect);
 }
