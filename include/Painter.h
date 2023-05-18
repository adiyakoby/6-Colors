#pragma
#include "Graph.h"
#include "Colors.h"


template<class Shape>
class Painter
{
public:
	Painter(sf::RenderWindow& window) : m_window{ window }
																			
	{ ; };
	~Painter() = default;
	Painter& operator=(const Painter& other) {
		if (this != &other) {
			m_graph_start = other.m_graph_start;
			m_window = other.m_window;
		}
		return *this;
	}
	void set_start_it(Graph<Shape>::GraphIterator it_start) { m_graph_start = it_start; };
	void set_end_it(Graph<Shape>::GraphIterator it_end) { m_graph_end = it_end; };
	void draw_graph();

	//sf::Color check_for_color(const float& x, const float& y);

private:
	Graph<Shape>::GraphIterator m_graph_start;
	Graph<Shape>::GraphIterator m_graph_end;
	sf::RenderWindow& m_window;
	//sf::RectangleShape m_rectangle;
	//Colors m_color;
};

template<class Shape>
inline void Painter<Shape>::draw_graph()
{
	//m_color.drawMenu(m_window);
	for (auto it = m_graph_start; it != m_graph_end; it++)
		m_window.draw(it->get_shape());
}

//template<class Shape>
//inline sf::Color Painter<Shape>::check_for_color(const float& x, const float& y)
//{
//	return m_color.check_for_color(x, y);
//}
