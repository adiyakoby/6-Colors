#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include <list>

enum Owner { Natural, Computer, Player };
int COUNTER = 0;

template<class Shape>
class Node
{
public:
	Node(const Shape& shape);
	~Node() = default;


	inline sf::Color get_color() const { return m_shape.getFillColor(); };
	inline sf::Vector2f get_position() const { return m_shape.getPosition(); };
	inline float getX() const { return m_shape.getPosition().x; };
	inline float getY() const { return m_shape.getPosition().y; };
	inline float get_radius() const { return m_shape.getRadius(); };
	inline void draw(sf::RenderWindow& window) const { window.draw(m_shape); };

	inline bool change_owner(Owner type) {
		if (m_owner == Natural)
		{
			m_owner = type;
			return true;
		}
		return false;
	};

	inline void set_color(const sf::Color& color) { m_shape.setFillColor(color); };
	inline void set_position(const sf::Vector2f& pos) { m_shape.setPosition(pos); };
	inline void set_position(const float& f1, const float& f2) { m_shape.setPosition(sf::Vector2f(f1, f2)); };

	void contain(const sf::Vector2f& mouse_loc) {
		if (m_shape.getGlobalBounds().contains(mouse_loc))
		{
			m_owner = Player;
			std::cout << "my color is : " << (m_shape.getFillColor() == sf::Color::Yellow ? "Yellow" : "Else") << std::endl;
			for (auto& ea : m_neighbors)
			{
				std::cout << "my color is : " << (ea->get_color() == sf::Color::Yellow ? "Yellow" : "Else") << std::endl;
				if (ea->get_color() == m_shape.getFillColor() && ea->change_owner(Player))
				{

					std::cout << "inside if " << std::endl;
					ea->set_color(sf::Color::White);
					this->set_color(sf::Color::White);
				}


			}
		}

	};


	inline void set_neghibors(std::list<std::shared_ptr<Node<Shape>>>& neighbors) { m_neighbors = neighbors; };

	inline bool operator==(const Node& other) const { return *this == other; };
	inline bool operator!=(const Node& other) const { return !(*this == other); };

	inline bool operator<(const Node& other) const { return  (m_shape.getPosition().x < other.getPosition().x ? true : false); }

private:
	Shape m_shape;
	std::list<std::shared_ptr<Node<Shape>>> m_neighbors;
	Owner m_owner;
	

	//private funcs:
	sf::Color rand_color() const;

};




template<class Shape>
inline Node<Shape>::Node(const Shape& shape) : m_shape(shape), m_owner{ Natural }
{
	COUNTER++;
	std::cout << COUNTER << std::endl;
	m_shape.setFillColor(rand_color());
	m_shape.setOrigin(m_shape.getRadius(), m_shape.getRadius());
	//std::cout << "coords: x:" << m_shape.getPosition().x << " y: " << m_shape.getPosition().y << std::endl;
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
