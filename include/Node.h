#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include <list>

enum Owner { Natural, Computer, Player };

template<class Shape>
class Node
{
public:
	Node(const Shape& shape);
	~Node() = default;


	//getters
	inline sf::Color get_color() const { return m_shape.getFillColor(); };
	inline sf::Vector2f get_position() const { return m_shape.getPosition(); };
	inline float getX() const { return m_shape.getPosition().x; };
	inline float getY() const { return m_shape.getPosition().y; };
	inline float get_radius() const { return m_shape.getRadius(); };
	inline void draw(sf::RenderWindow& window) const { window.draw(m_shape); };
	inline bool is_visited() const { return m_visited; };
	inline Owner get_owner() const { return m_owner; };

	
	
	// setters
	void set_color(const sf::Color& color) { m_shape.setFillColor(color); };
	inline void set_position(const sf::Vector2f& pos) { m_shape.setPosition(pos); };
	inline void set_position(const float& f1, const float& f2) { m_shape.setPosition(sf::Vector2f(f1, f2)); };
	inline void un_visit() { m_visited = false; };
	bool set_owner(const Owner& type);
	inline void set_neighbors(std::list<std::shared_ptr<Node<Shape>>>& neighbors) { m_neighbors = neighbors; };

	//players func
	void player_move(const sf::Color& color);
	void EnemeyEasyModeMove(const sf::Color& color);
	
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
	sf::Color rand_color() const;

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
inline void Node<Shape>::player_move(const sf::Color& color)
{
	m_visited = true;
	if (m_owner == Player)
	{
		for (auto& ea : m_neighbors)
			if (!ea->is_visited() && ((ea->get_owner() == Player && ea->get_color() == this->get_color()) || (ea->get_color() == color && ea->set_owner(Player))))
				ea->player_move(color);
		
		this->set_color(color);
	}
}
template<class Shape>
inline void Node<Shape>::EnemeyEasyModeMove(const sf::Color& color)
{
	m_visited = true;
	if (m_owner == Computer)
	{
		for (auto& ea : m_neighbors)
			if (!ea->is_visited() && ((ea->get_owner() == Computer && ea->get_color() == this->get_color()) || (ea->get_color() == color && ea->set_owner(Computer))))
				ea->player_move(color);

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
