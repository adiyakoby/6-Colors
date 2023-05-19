#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include <list>
#include <algorithm>



enum class Owner { Natural, Computer, Player };

template<class Shape>
class Node
{
public:
	Node(const Shape& shape);
	~Node() = default;


	//getters
	sf::Color rand_color() const;
	inline sf::Color get_color() const { return m_shape.getFillColor(); };
	inline sf::Vector2f get_position() const { return m_shape.getPosition(); };
	inline float getX() const { return m_shape.getPosition().x; };
	inline float getY() const { return m_shape.getPosition().y; };
	inline float get_radius() const { return m_shape.getRadius(); };
	inline void draw(sf::RenderWindow& window) const { window.draw(m_shape); };
	inline bool is_visited() const { return m_visited; };
	inline Owner get_owner() const { return m_owner; };
	bool find_Color(const sf::Color &color);
	void get_neigh_colors(std::vector<sf::Color>& vec);
	void count_neigh_colors(std::vector<int>& vec);
	Shape& get_shape() { return m_shape; };
	float get_ownership(const Owner& owner_type);


	// setters
	void set_color(const sf::Color& color) { m_shape.setFillColor(color); };
	inline void set_position(const sf::Vector2f& pos) { m_shape.setPosition(pos); };
	inline void set_position(const float& f1, const float& f2) { m_shape.setPosition(sf::Vector2f(f1, f2)); };
	inline void un_visit();
	bool set_owner(const Owner& type);
	inline void set_neighbors(std::list<std::shared_ptr<Node<Shape>>>& neighbors) { m_neighbors = neighbors; };

	//players func
	void find_nodes(const sf::Color& color ,const Owner& owner_type);

	int get_size() { return m_neighbors.size(); };
	//operator overloading
	inline bool operator==(const Node& other) const { return *this == other; };
	inline bool operator!=(const Node& other) const { return !(*this == other); };
	inline bool operator<(const Node& other) const { return  (m_shape.getPosition().x < other.getPosition().x ? true : false); }

private:
	Shape m_shape;
	std::list<std::shared_ptr<Node<Shape>>> m_neighbors;
	Owner m_owner;
	bool m_visited;
	
	//private funcs:

};




template<class Shape>
inline Node<Shape>::Node(const Shape& shape) : m_shape(shape), m_owner(Owner::Natural), m_visited{false}
{
	m_shape.setFillColor(rand_color());
	m_shape.setOrigin(m_shape.getGlobalBounds().width/2, m_shape.getGlobalBounds().height/2);
	std::cout << m_shape.getPosition().x << "  " << m_shape.getPosition().y << std::endl;
}


template<class Shape>
inline bool Node<Shape>::set_owner(const Owner& type)
{
	if (m_owner == type) return true;

	if (m_owner == Owner::Natural) {
		m_owner = type;
		return true;
	}

	return false;
}

template<class Shape>
inline void Node<Shape>::find_nodes(const sf::Color& color, const Owner &owner_type)
{
	std::cout << "in find nodes\n";
	m_visited = true;
	if (m_owner == Owner::Natural)
		return;

	for (auto& ea : m_neighbors)
		if (!ea->is_visited() && ((ea->get_owner() == owner_type && ea->get_color() == this->get_color()) || (ea->get_color() == color && ea->set_owner(owner_type))))
			ea->find_nodes(color, owner_type);
			
	this->set_color(color);
}



template<class Shape>
sf::Color Node<Shape>::rand_color() const {
	int color = rand() % 6;

	if (color == 0) return sf::Color::Blue;
	else if (color == 1) return sf::Color::Green;
	else if (color == 2) return sf::Color::Red;
	else if (color == 3) return sf::Color::Yellow;
	else if (color == 4) return sf::Color::Cyan;
	else return sf::Color::Magenta;
};


template<class Shape>
bool Node<Shape>::find_Color(const sf::Color& color) {
	m_visited = true;

	for (auto& ea : m_neighbors)
		if (ea->get_owner() == Owner::Natural && ea->get_color() == color)
			return true;
	
	for (auto& ea : m_neighbors)
		if (ea->get_owner() == Owner::Computer && !ea->is_visited())
			if (ea->find_Color(color))
				return true;

	return false;
}


template<class Shape>
void Node<Shape>::get_neigh_colors(std::vector<sf::Color>& vec) {

	m_visited = true;

	for (auto& ea : m_neighbors) 
		if (ea->get_owner() == Owner::Natural)
			if (std::find(vec.begin(), vec.end(), ea->get_color()) == vec.end())
				vec.push_back(ea->get_color());

	for (auto& ea : m_neighbors)
		if (ea->get_owner() == Owner::Computer && !ea->is_visited())
			ea->get_neigh_colors(vec);
}

template<class Shape>
void Node<Shape>::count_neigh_colors(std::vector<int>& vec) {

	m_visited = true;

	//sf::Color::Red, sf::Color::Magenta, sf::Color::Green,
	//sf::Color::Blue, sf::Color::Yellow, sf::Color::Cyan

	for (auto& ea : m_neighbors)
	{
		if (ea->get_owner() == Owner::Natural) {
			sf::Color color= ea->get_color();

			if (color == sf::Color::Red)
				vec.at(0) += 1;
			else if (color == sf::Color::Magenta)
				vec.at(1) += 1;
			else if (color == sf::Color::Green)
				vec.at(2) += 1;
			else if (color == sf::Color::Blue)
				vec.at(3) += 1;
			else if (color == sf::Color::Yellow)
				vec.at(4) += 1;
			else if (color == sf::Color::Cyan)
				vec.at(5) += 1;
		}
		else if (ea->get_owner() == Owner::Computer && !ea->is_visited())
			ea->count_neigh_colors(vec);
	}
}

template<class Shape>
float Node<Shape>::get_ownership(const Owner& owner_type) {
	m_visited = true;
	float count{};

	for (auto& ea : m_neighbors) 
		if(ea->is_visited() == false)
			count += ea->get_ownership(owner_type) ;

	return (m_owner == owner_type ? count + 1 : count);		

}

template<class Shape>
void Node<Shape>::un_visit() {
	m_visited = false;

	for (auto& ea : m_neighbors)
		if (ea->is_visited() == true)
			ea->un_visit();
}