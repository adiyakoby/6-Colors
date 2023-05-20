#pragma once


#include "Node.h" // has iostream, sfml graphic, memory, list
#include <functional>
#include <unordered_map>
#include <set>
#include <iterator>


// using std::hash in order to hash the std::pair for key in un_map
struct pairhash {
public:
	template <typename T1, typename T2>
	std::size_t operator()(const std::pair<T1, T2>& x) const
	{
		return std::hash<T1>()(x.first) ^ std::hash<T2>()(x.second);
	};
};



template<class Shape>
class Graph
{
public:
	Graph(const Shape& shape, sf::RenderWindow& window, const sf::RectangleShape& rectangle,
		std::function <std::vector<sf::Vector2f>(sf::Vector2f, float)> neighbors_func,
		std::function <sf::Vector2f(Shape, bool, bool)> dist_func);

	~Graph() = default;

	//using
	using graph_ds = std::unordered_map <std::pair<float, float>, std::shared_ptr<Node<Shape>>, pairhash>;

	void unvisit_nodes();
	inline std::shared_ptr<Node<Shape>>get_comp_node() { return m_computer_start; };
	void attach_nodes(const sf::Color& color, const Owner& owner);



	/* Custom iterator for the graph. */
	class GraphIterator {
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = Node<Shape>;
		using pointer = Node<Shape>*;  // or also value_type*
		using reference = Node<Shape> &;  // or also value_type&

		GraphIterator() : m_ptr() { ; };
		GraphIterator(graph_ds::iterator ptr) : m_ptr(ptr) { ; };
		GraphIterator(const GraphIterator& other) : m_ptr(other.m_ptr) { ; };
		GraphIterator& operator=(const GraphIterator& other) {
			if (this != &other) {
				m_ptr = other.m_ptr;
			}
			return *this;
		}
		reference operator*() const { return *(m_ptr->second); }; // double derfrence for iterator and shared_ptr
		pointer operator->() { return m_ptr->second.get(); }

		// Prefix increment
		GraphIterator& operator++() { m_ptr++; return *this; };

		// Postfix increment
		GraphIterator operator++(int) { GraphIterator tmp = *this; ++(*this); return tmp; };

		bool operator== (const GraphIterator& rhs) { return m_ptr == rhs.m_ptr; };
		bool operator!= (const GraphIterator& rhs) { return !(m_ptr == rhs.m_ptr); };

	private:
		graph_ds::iterator m_ptr;
	};
	/* End of custom iterator */

	GraphIterator computer_begin() { return GraphIterator(m_map.find( {m_computer_start->getX(), m_computer_start->getY() })); };
	GraphIterator begin() { return GraphIterator(m_map.begin()); };
	GraphIterator end() { return GraphIterator(m_map.end()); };

private:

	sf::RenderWindow& m_ref_window;
	graph_ds m_map; // our graph of nodes

	//players start nodes.
	std::shared_ptr<Node<Shape>> m_player_start;
	std::shared_ptr<Node<Shape>> m_computer_start;
	

	//funcs
	inline bool validation(const Shape& shape, const sf::RectangleShape& rectangle);
	void make_Graph(const Shape& shape, const sf::RectangleShape& rectangle, std::function <sf::Vector2f(Shape, bool, bool)> dist_func);
	void connect_nodes(std::function <std::vector<sf::Vector2f>(sf::Vector2f, float)> neighbors_func);
	std::list<std::shared_ptr<Node<Shape>>> match_neighbors(std::vector <sf::Vector2f>& loc);

};


template<class Shape>
inline Graph<Shape>::Graph(const Shape& shape, sf::RenderWindow& window, const sf::RectangleShape& rectangle, 
							std::function<std::vector<sf::Vector2f>(sf::Vector2f, float)> neighbors_func, 
							std::function<sf::Vector2f(Shape, bool, bool)> dist_func) : m_ref_window{ window },
																						m_player_start{ nullptr }, 
																						m_computer_start{ nullptr }
{
	this->make_Graph(shape, rectangle, dist_func);
	this->connect_nodes(neighbors_func);

	m_player_start->set_owner(Owner::Player);
	m_computer_start->set_owner(Owner::Computer);
};

template<class Shape>
inline void Graph<Shape>::unvisit_nodes()
{
	m_computer_start->un_visit();
	m_player_start->un_visit();
};




template<class Shape>
inline void Graph<Shape>::attach_nodes(const sf::Color& color, const Owner& owner)
{
	if (owner == Owner::Player)
		m_player_start->find_nodes(color, owner);
	else if (owner == Owner::Computer)
		m_computer_start->find_nodes(color, owner);

	m_computer_start->un_visit();
	m_player_start->un_visit();
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

	std::shared_ptr<Node<Shape>> ptr{nullptr};
	while (board_height > 0 )
	{	
		if (validation(temp, rectangle))
		{
			ptr = std::make_shared<Node<Shape>>(temp);
			m_map.emplace(std::make_pair((ptr->getX()), (ptr->getY())), ptr);
			if (m_map.size() > 0 && (m_computer_start.get() == nullptr || ptr->getY() > m_player_start->getY()))
				m_player_start = ptr;	
		}
		
		board_width -= temp.getGlobalBounds().width;


		if (board_width <= 0)
		{
			if (m_map.size() > 0 && m_computer_start.get() == nullptr) m_computer_start = ptr;

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
	for (auto& ea : m_map)
	{
		std::vector<sf::Vector2f> neighb_location = neighbors_func(ea.second->get_position(), ea.second->get_radius()); // get possible neighbors
		std::list<std::shared_ptr<Node<Shape>>> obj_negibors = match_neighbors(neighb_location); // get list of neigbors
		ea.second->set_neighbors(obj_negibors); // connect neighbors
	}
}


template<class Shape>
inline std::list<std::shared_ptr<Node<Shape>>> Graph<Shape>::match_neighbors(std::vector <sf::Vector2f>& loc)
{
	std::list<std::shared_ptr<Node<Shape>>> lst;
	for (const auto& ea : loc) {
		auto it = m_map.find(std::make_pair((ea.x), (ea.y)));
		if (it != m_map.end())
			lst.push_back(it->second);
	}

	return lst;
};
