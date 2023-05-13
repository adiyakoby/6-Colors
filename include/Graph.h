#pragma once


#include "Node.h" // has iostream, sfml graphic, memory, list
#include <functional>
#include <map>


struct Vector2fComparator
{
	bool operator()(const sf::Vector2f& lhs, const sf::Vector2f& rhs) const
	{
		if (lhs.x < rhs.x)
			return true;
		else if (lhs.x > rhs.x)
			return false;
		else
			return lhs.y < rhs.y;
	}
};




template<class Shape>
class Graph
{
public:
	Graph(const Shape& shape, sf::RenderWindow& window, sf::RectangleShape& rectangle,
		std::function <std::vector<sf::Vector2f>(sf::Vector2f, float)> func) : m_ref_window{ window },
		m_width{ (window.getSize().x * 0.75f) },
		m_height{ (window.getSize().y * 0.75f) },
		m_neighborFunc{ func }
	{
		this->make_Graph(shape, rectangle);
	};
	~Graph() = default;


	inline void draw() const { std::ranges::for_each(m_board.begin(), m_board.end(), [&](const auto& ea) {ea->draw(m_ref_window); }); };

	void paint(const sf::Vector2f& mouse_location) {
		std::ranges::for_each(m_board.begin(), m_board.end(), [&](const auto& ea) {ea->contain(mouse_location); });
	};


private:

	sf::RenderWindow& m_ref_window;
	std::vector<std::shared_ptr<Node<Shape>>> m_board;
	std::map < std::pair<float, float>, std::shared_ptr<Node<Shape>>> m_map;

	float m_width;
	float m_height;
	void make_Graph(const Shape& shape, sf::RectangleShape& rectangle);
	void connect_nodes();
	std::list<std::shared_ptr<Node<Shape>>> match_neighbors(std::vector <sf::Vector2f>& loc);
	std::function < std::vector<sf::Vector2f>(sf::Vector2f, float) > m_neighborFunc;
};


//function<int(int,int)> arithmeticFcn

template<class Shape>
inline void Graph<Shape>::make_Graph(const Shape& shape, sf::RectangleShape& rectangle)
{
	Shape temp(shape);
	temp.setPosition(rectangle.getPosition().x * 0.5f, rectangle.getPosition().y * 0.5f);
	Shape prev_line(temp);
	bool left = false;

	float h{ 0 }, w{ 0 };
	while (w < rectangle.getPosition().x * 2.f && h < rectangle.getPosition().y * 2.f)
	{

		std::shared_ptr<Node<Shape>> ptr = std::make_shared<Node<Shape>>(temp);
		if (rectangle.getGlobalBounds().intersects(temp.getGlobalBounds()))
		{
			m_board.push_back(ptr);
			m_map.emplace(std::make_pair(std::round(ptr->getX()), std::round(ptr->getY())), ptr);
		}
		w += shape.getRadius() * 2.f;
		if (w >= m_width)
		{
			w = shape.getRadius() * 2.f;
			h += shape.getRadius() * 2.f;
			float x = (left == true ? prev_line.getPosition().x - prev_line.getRadius() * (std::sqrt(3.f) / 2.f) : prev_line.getPosition().x + prev_line.getRadius() * (std::sqrt(3.f) / 2.f));
			temp.setPosition(x, prev_line.getPosition().y + (2.f * prev_line.getRadius()) * 3.f / 4.f);
			prev_line = temp;
			left = !left;
		}
		else
			temp.setPosition(temp.getPosition().x + 2.f * temp.getRadius() * (std::sqrt(3.f) / 2.f), temp.getPosition().y);

	}

	this->connect_nodes();
}

template<class Shape>
inline void Graph<Shape>::connect_nodes()
{
	for (int i = 0; i < m_board.size(); i++)
	{
		std::vector<sf::Vector2f> neighb_location = m_neighborFunc(m_board.at(i)->get_position(), m_board.at(i)->get_radius()); // get possible neighbors
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




/*auto func = [*this](const sf::Vector2f& pos) {

	std::vector<sf::Vector2f> all_neighbors;
	//left and right
	all_neighbors.push_back(sf::Vector2f(pos.x +  m_board[0]->get_radius() * std::sqrt(3.f), pos.y));
	all_neighbors.push_back(sf::Vector2f(pos.x -  m_board[0]->get_radius() * std::sqrt(3.f), pos.y));
	//below
	all_neighbors.push_back(sf::Vector2f(pos.x + m_board[0]->get_radius() * (std::sqrt(3.f) / 2.f), pos.y + m_board[0]->get_radius() * 1.5f));
	all_neighbors.push_back(sf::Vector2f(pos.x - m_board[0]->get_radius() * (std::sqrt(3.f) / 2.f), pos.y + m_board[0]->get_radius() * 1.5f));
	//above
	all_neighbors.push_back(sf::Vector2f(pos.x + m_board[0]->get_radius() * (std::sqrt(3.f) / 2.f), pos.y - m_board[0]->get_radius() * 1.5f));
	all_neighbors.push_back(sf::Vector2f(pos.x - m_board[0]->get_radius() * (std::sqrt(3.f) / 2.f), pos.y - m_board[0]->get_radius() * 1.5f));

	for (auto& ea : all_neighbors) {
		ea.x = std::round(ea.x);
		ea.y = std::round(ea.y);
	}

	return all_neighbors;

};*/