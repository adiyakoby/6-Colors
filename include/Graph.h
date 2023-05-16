#pragma once


#include "Node.h" // has iostream, sfml graphic, memory, list
#include <functional>
#include <unordered_map>
#include <set>


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
		std::function <sf::Vector2f(Shape, bool, bool)> dist_func) : m_ref_window{ window },
		m_player_start{nullptr}, m_computer_start{nullptr}
	{
		std::srand(time(NULL));

		this->make_Graph(shape, rectangle, dist_func);
		this->connect_nodes(neighbors_func);

		m_player_start->set_owner(Player);
		m_computer_start->set_owner(Computer);
		
		
		//m_player_start->set_color(sf::Color::White);
		//m_computer_start->set_color(sf::Color::White);

	};
	~Graph() = default;

	void unvisit_nodes() { std::ranges::for_each(m_map.begin(), m_map.end(), [&](const auto& ea) {ea.second->un_visit(); }); };

	inline void draw() const { std::ranges::for_each(m_map.begin(), m_map.end(), [&](const auto& ea) {ea.second->draw(m_ref_window); }); };

	constexpr inline std::shared_ptr<Node<Shape>>get_comp_node() { return m_computer_start; };


	std::vector<sf::Color> get_avail_color() 
	{
		std::vector<sf::Color> ret_set{};
		for (auto& ea : m_map)
		{
			if (ea.second->get_owner() == Natural && ea.second->is_comp_attached())
				ret_set.push_back(ea.second->get_color());
		}
		return ret_set;
	};



	void attach_nodes(const sf::Color& color, const Owner &owner) {
		std::cout << "attach_nodes" << std::endl;
		if(owner == Player)
			m_player_start->find_nodes(color, owner);
		else if(owner == Computer)
			m_computer_start->find_nodes(color, owner);

		std::ranges::for_each(m_map.begin(), m_map.end(), [&](const auto& ea) {ea.second->un_visit(); });
	};


private:

	sf::RenderWindow& m_ref_window;
	std::unordered_map <std::pair<float, float>, std::shared_ptr<Node<Shape>>, pairhash> m_map; // our graph of nodes

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
			m_map.emplace(std::make_pair(std::round(ptr->getX()), std::round(ptr->getY())), ptr);
			if (m_map.size() > 0 && (m_computer_start.get() == nullptr || ptr->getY() > m_player_start->getY()))
				m_player_start = ptr;		
		}

		board_width -= temp.getGlobalBounds().width;
		//if(m_map.size() > 0 && m_computer_start.get() == nullptr)
			//m_player_start = ptr;

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
		auto it = m_map.find(std::make_pair(std::round(ea.x), std::round(ea.y)));
		if (it != m_map.end())
			lst.push_back(it->second);

	}

	return lst;
};
