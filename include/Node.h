#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include <list>
#include <algorithm>
#include <stack>
enum Owner { Natural, Computer, Player };

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
	sf::Color findColorHardMode();
	void getHighest(const sf::Color& color, std::vector<int>& color_count,int i);
	
	// setters
	void set_color(const sf::Color& color) { m_shape.setFillColor(color); };
	inline void set_position(const sf::Vector2f& pos) { m_shape.setPosition(pos); };
	inline void set_position(const float& f1, const float& f2) { m_shape.setPosition(sf::Vector2f(f1, f2)); };
	inline void un_visit() { m_visited = false; };
	bool set_owner(const Owner& type);
	inline void set_neighbors(std::list<std::shared_ptr<Node<Shape>>>& neighbors) { m_neighbors = neighbors; };

	//players func
	void find_nodes(const sf::Color& color ,const Owner& owner_type);

	
	inline bool is_comp_attached() {
		for (auto& ea : m_neighbors)
		{
			if (ea->get_owner() == Computer)
				return true;
		}
		return false;
	}


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
inline Node<Shape>::Node(const Shape& shape) : m_shape(shape), m_owner(Natural), m_visited{false}
{
	m_shape.setFillColor(rand_color());
	m_shape.setOrigin(m_shape.getGlobalBounds().width/2, m_shape.getGlobalBounds().height/2);
	
}


template<class Shape>
inline bool Node<Shape>::set_owner(const Owner& type)
{
	if (m_owner == type) return true;
	if (m_owner == Natural) {
		m_owner = type;
		return true;
	}
	return false;
}

template<class Shape>
inline void Node<Shape>::find_nodes(const sf::Color& color, const Owner &owner_type)
{
	//std::cout << "find_nodes" << std::endl;
	m_visited = true;
	if (m_owner == owner_type)
	{
		for (auto& ea : m_neighbors)
			if (!ea->is_visited() && ((ea->get_owner() == owner_type && ea->get_color() == this->get_color()) || (ea->get_color() == color && ea->set_owner(owner_type))))
				ea->find_nodes(color, owner_type);
		
		this->set_color(color);
	}
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
	//std::cout << "find_Color" << std::endl;

	m_visited = true;
	//bool ret_val{ false };
	
	for (auto& ea : m_neighbors)
	{
		if (ea->get_owner() == Natural && ea->get_color() == color)
		{
			m_visited = false;
			return true;
		}
			
	}
	//auto it = std::next(m_neighbors.begin(), rand() % m_neighbors.size());
	//if (it->get()->get_owner() == Natural && it->get()->get_color() == color)
		//return true;

	//if (it->get()->get_owner() == Natural)
	//	return false;

	for (auto& ea : m_neighbors)
	{
		if (ea->get_owner() == Computer && !ea->is_visited())
			if (ea->find_Color(color))
			{
				m_visited = false;
				return true;
			}
				
	}

	//if (ret_val) return true;
	//else {
	//	it = std::next(m_neighbors.begin(), rand() % m_neighbors.size());
	//	ret_val = it->get()->find_Color(color);
	//}
	m_visited = false;
	return false;
}



template<class Shape>
sf::Color Node<Shape>::findColorHardMode() {
	std::cout << "hardest\n";
	std::vector <int> color_count(m_neighbors.size(),0);
	int i{};
	bool found_color{ false };
	
	m_visited = true;
	for (auto& ea : m_neighbors) {
		if (ea->get_owner() == Natural && !ea->is_visited()) {
			ea->m_visited = true;
			color_count[i]++;
			ea->getHighest(ea->get_color(), color_count, i);
			found_color = true;
		}
		i++;
	}

	if (found_color) {
		auto max = max_element(color_count.begin(), color_count.end());
		auto it = m_neighbors.begin();
		for (auto& ea : color_count) {
			if (ea == *max)
				return it->get()->get_color();
			it++;
		}

	}
	for (auto& ea : m_neighbors) {
		ea->m_visited = true;
		sf::Color color = ea->findColorHardMode();
		if (color != sf::Color::Black) {
			return color;
		}
	}
	// No usable color found, return an appropriate default color
	return sf::Color::Black; // or any other default color value

}







template<class Shape>
void  Node<Shape>::getHighest (const sf::Color& color, std::vector<int>& color_count, int fill) {
	
	m_visited = true;

	if (m_owner == Player)
		return;

	
	for (auto& ea : m_neighbors){
		if (ea->get_owner() == Natural && (!ea->is_visited()) && ea->get_color() == color){
			//ea->m_visited = true;
			color_count[fill]++;
			ea->getHighest(color, color_count, fill);	
		}
		//ea -> m_visited = false;
	}
	//m_visited = false;
	//m_visited = false;
}