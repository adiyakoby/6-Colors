#pragma once


#include "Node.h" // has iostream, sfml graphic, memory, list
#include <functional>
#include <map>


template<class Shape>
class Graph
{
public:
	Graph(const Shape& shape, sf::RenderWindow& window, const sf::RectangleShape& rectangle,
		std::function <std::vector<sf::Vector2f>(sf::Vector2f, float)> neighbors_func) : m_ref_window{ window },
	{
		this->make_Graph(shape, rectangle);
		this->connect_nodes(neighbors_func);
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

	inline bool validation(const Shape& shape, const sf::RectangleShape& rectangle);
	void make_Graph(const Shape& shape, const sf::RectangleShape& rectangle);
	void connect_nodes(std::function <std::vector<sf::Vector2f>(sf::Vector2f, float)> neighbors_func);
	std::list<std::shared_ptr<Node<Shape>>> match_neighbors(std::vector <sf::Vector2f>& loc);
};


template<class Shape>
inline bool Graph<Shape>::validation(const Shape& shape, const sf::RectangleShape& rectangle)
{
	//return rectangle.getGlobalBounds().contains(shape.getPosition());	
	if (shape.getPosition().x < rectangle.getGlobalBounds().left + rectangle.getGlobalBounds().width
		&& shape.getPosition().y > rectangle.getGlobalBounds().top 
		&& shape.getPosition().y < rectangle.getGlobalBounds().top + rectangle.getGlobalBounds().height)
		return true;
	return false;
}

template<class Shape>
void Graph<Shape>::make_Graph(const Shape& shape, const sf::RectangleShape& rectangle)
{
	Shape temp(shape);
	temp.setOrigin(temp.getGlobalBounds().width, temp.getGlobalBounds().height);
	temp.setPosition(rectangle.getGlobalBounds().left, rectangle.getGlobalBounds().top - shape.getGlobalBounds().height);
	Shape prev_line(temp);

	bool left = false; // for positioning start of next line correctly.

	float h{ temp.getGlobalBounds().height + rectangle.getGlobalBounds().top + rectangle.getGlobalBounds().height }, w{ temp.getGlobalBounds().width + rectangle.getGlobalBounds().width };
	std::cout << "w is :" << w << "  h is : " << h << std::endl;
	std::cout << "top is is :" << rectangle.getGlobalBounds().top << "  height  is : " << rectangle.getGlobalBounds().height << std::endl;

	while (w > 0 && h >0 )
	{	
		std::cout << "x is :" << temp.getPosition().x << "  y is : " << temp.getPosition().y << std::endl;

		if (validation(temp, rectangle))
		{
			std::shared_ptr<Node<Shape>> ptr = std::make_shared<Node<Shape>>(temp);
			m_board.push_back(ptr);
			m_map.emplace(std::make_pair(std::round(ptr->getX()), std::round(ptr->getY())), ptr);
		}
		w -= temp.getGlobalBounds().width;//shape.getRadius() * 2.f;
		
		if (w <= 0)
		{
			w = temp.getGlobalBounds().width + rectangle.getGlobalBounds().width;//shape.getRadius() * 2.f;
			h -= temp.getGlobalBounds().height;  //shape.getRadius() * 2.f;
			float x = (left == true ? prev_line.getPosition().x - prev_line.getRadius() * (std::sqrt(3.f) / 2.f) : prev_line.getPosition().x + prev_line.getRadius() * (std::sqrt(3.f) / 2.f));
			temp.setPosition(x, prev_line.getPosition().y + (2.f * prev_line.getRadius()) * 3.f / 4.f);
			prev_line = temp;
			left = !left;
		}
		else
			temp.setPosition(temp.getPosition().x + 2.f * temp.getRadius() * (std::sqrt(3.f) / 2.f), temp.getPosition().y);

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



