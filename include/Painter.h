#pragma
#include "Graph.h"
#include "Colors.h"
#include "Menu.h"

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;

template<class Shape>
class Painter
{
public:
	Painter(sf::RenderWindow& window) : m_window{ window }, m_menu(WINDOW_WIDTH, WINDOW_HEIGHT)
										, m_colors(WINDOW_WIDTH, WINDOW_HEIGHT)
	{
			
		set_exit(); 
	};
	~Painter() = default;

	void set_start_it(Graph<Shape>::GraphIterator it_start) { m_graph_start = it_start; };
	void set_end_it(Graph<Shape>::GraphIterator it_end) { m_graph_end = it_end; };
	void draw_graph();
	void draw_menu() { m_menu.draw(m_window); }

	menu_state get_mode(const unsigned int &x, const unsigned int& y) { return m_menu.get_choice(x, y); };

	sf::RectangleShape getscreen() { return m_menu.getscreen(); };
	sf::RectangleShape get_exit() { return m_exit; };

	sf::Color check_for_color(const float& x, const float& y) { return m_colors.check_for_color(x, y); };
	void draw_x(const sf::Color& color, const ttpe& type) { m_colors.draw_x(color, type); };
	void set_exit();

private:
	Graph<Shape>::GraphIterator m_graph_start;
	Graph<Shape>::GraphIterator m_graph_end;

	sf::RenderWindow& m_window;

	Menu m_menu;
	Colors m_colors;

	sf::RectangleShape m_exit;
	sf::Texture m_exitpng;


};

template<class Shape>
inline void Painter<Shape>::draw_graph()
{
	for (auto it = m_graph_start; it != m_graph_end; it++)
		m_window.draw(it->get_shape());
	m_colors.draw_colors(m_window);

	//m_window.draw(m_exit);
}

template<class Shape>
void Painter<Shape> ::set_exit() {
	if (!m_exitpng.loadFromFile("exit.png")) {
		;	// Error handling if the image fails to load
	}
	m_exit.setTexture(&m_exitpng);

	m_exit.setSize(sf::Vector2f(WINDOW_WIDTH*0.1, WINDOW_HEIGHT *0.1));
	m_exit.setPosition(0, 0);



}
//template<class Shape>
//inline sf::Color Painter<Shape>::check_for_color(const float& x, const float& y)
//{
//	return m_color.check_for_color(x, y);
//}
