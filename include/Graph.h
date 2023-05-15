#pragma once


#include "Node.h" // has iostream, sfml graphic, memory, list
#include <functional>
#include <map>
//#include "Computer.h"
template<class Shape>
class Graph
{
public:
	Graph(const Shape& shape, sf::RenderWindow& window, const sf::RectangleShape& rectangle,
		std::function <std::vector<sf::Vector2f>(sf::Vector2f, float)> neighbors_func,
		std::function <sf::Vector2f(Shape, bool, bool)> dist_func) : m_ref_window{ window },
		m_player_start{nullptr}, m_computer_start{nullptr}
	{
		this->make_Graph(shape, rectangle, dist_func);
		this->connect_nodes(neighbors_func);
		//m_player_start->set_color(sf::Color::White);
		m_computer_start->set_color(sf::Color::White);

	};
	~Graph() = default;


	inline void draw() const { std::ranges::for_each(m_board.begin(), m_board.end(), [&](const auto& ea) {ea->draw(m_ref_window); }); };

	void paint(const sf::Color& color) {
		std::ranges::for_each(m_board.begin(), m_board.end(), [&](const auto& ea) {; });
	};


private:

	sf::RenderWindow& m_ref_window;
	std::vector<std::shared_ptr<Node<Shape>>> m_board;
	std::map < std::pair<float, float>, std::shared_ptr<Node<Shape>>> m_map;

	std::shared_ptr<Node<Shape>> m_player_start;
	std::shared_ptr<Node<Shape>> m_computer_start;

	//funcs
	inline bool validation(const Shape& shape, const sf::RectangleShape& rectangle);
	void make_Graph(const Shape& shape, const sf::RectangleShape& rectangle, std::function <sf::Vector2f(Shape, bool, bool)> dist_func);
	void connect_nodes(std::function <std::vector<sf::Vector2f>(sf::Vector2f, float)> neighbors_func);
	std::list<std::shared_ptr<Node<Shape>>> match_neighbors(std::vector <sf::Vector2f>& loc);

};


template<class Shape>
inline bool Graph<Shape>::validation(const Shape& shape, const sf::RectangleShape& rectangle)
{
	if (shape.getPosition().x <= rectangle.getGlobalBounds().left + rectangle.getGlobalBounds().width 
		&& shape.getPosition().y >= rectangle.getGlobalBounds().top 
		&& shape.getPosition().y <= rectangle.getGlobalBounds().top + rectangle.getGlobalBounds().height)
		return true;
	return false;
}

template<class Shape>
void Graph<Shape>::make_Graph(const Shape& shape, const sf::RectangleShape& rectangle, std::function <sf::Vector2f(Shape, bool, bool)> dist_func)
{
	Shape temp(shape);
	temp.setPosition(rectangle.getGlobalBounds().left, rectangle.getGlobalBounds().top );
	temp.setOutlineColor(sf::Color::Black);
	temp.setOutlineThickness(1.f);

	Shape prev_line(temp);

	bool right = true; // for positioning start of next line correctly.
	float board_height{ temp.getGlobalBounds().height + rectangle.getGlobalBounds().top + rectangle.getGlobalBounds().height },
		  board_width{ temp.getGlobalBounds().width + rectangle.getGlobalBounds().width };

	while (board_height > 0 )
	{	
		if (validation(temp, rectangle))
		{
			std::shared_ptr<Node<Shape>> ptr = std::make_shared<Node<Shape>>(temp);
			m_board.push_back(ptr);
			m_map.emplace(std::make_pair(std::round(ptr->getX()), std::round(ptr->getY())), ptr);
			m_player_start = ptr;
			//m_computer_start = ptr;
			
				
		}
		board_width -= temp.getGlobalBounds().width;
		
		if (board_width <= 0)
		{
			if (m_board.size() > 0 && m_computer_start.get() == nullptr) m_computer_start = m_board.back() ;
			board_width = temp.getGlobalBounds().width  + rectangle.getGlobalBounds().width;
			board_height -= temp.getGlobalBounds().height;
			temp.setPosition(dist_func(prev_line, right, true));
			prev_line = temp;
			right = !right;
		}
		else
			temp.setPosition(dist_func(temp, true, false));
	}
	
}

template<class Shape>
inline void Graph<Shape>::connect_nodes(std::function <std::vector<sf::Vector2f>(sf::Vector2f, float)> neighbors_func)
{
	for (int i = 0; i < m_board.size(); i++)
	{
		std::vector<sf::Vector2f> neighb_location = neighbors_func(m_board.at(i)->get_position(), m_board.at(i)->get_radius()); // get possible neighbors
		std::list<std::shared_ptr<Node<Shape>>> obj_negibors = match_neighbors(neighb_location); // get list of neigbors
		m_board.at(i)->set_neghibors(obj_negibors); // connect neighbors
	}
}


template<class Shape>
inline std::list<std::shared_ptr<Node<Shape>>> Graph<Shape>::match_neighbors(std::vector <sf::Vector2f>& loc)
{
	std::list<std::shared_ptr<Node<Shape>>> lst;
	for (const auto& ea : loc) {
		auto it = m_map.find(std::make_pair(std::round(ea.x), std::round(ea.y)));
		if (it != m_map.end())
			lst.push_back(it->second);
	}

	return lst;
}


