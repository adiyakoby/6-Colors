#pragma

#include "Colors.h"
#include "Menu.h"

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;

template<class Shape>
class Painter
{
public:
	Painter(sf::RenderWindow& window) : m_menu(WINDOW_WIDTH, WINDOW_HEIGHT), m_colors(WINDOW_WIDTH, WINDOW_HEIGHT), m_window{ window }
										
	{
		set_text_vec();
		set_exit(); 
	};
	~Painter() = default;

	void set_start_it(Graph<Shape>::GraphIterator it_start) { m_graph_start = it_start; };
	void set_end_it(Graph<Shape>::GraphIterator it_end) { m_graph_end = it_end; };
	void draw_graph();
	void draw_menu() { m_menu.draw(m_window); }
	void draw_stats();
	void update_stats(const float& player, const float& comp, const float& natural);

	menu_state get_mode(const unsigned int &x, const unsigned int& y) { return m_menu.get_choice(x, y); };

	sf::RectangleShape get_exit() { return m_exit; };

	sf::Color check_for_color(const float& x, const float& y) { return m_colors.check_for_color(x, y); };
	void draw_x(const sf::Color& color, const Owner& type) { m_colors.draw_x(color, type); };
	void set_exit();
	void set_text_vec();
private:
	Graph<Shape>::GraphIterator m_graph_start;
	Graph<Shape>::GraphIterator m_graph_end;

	sf::RenderWindow& m_window;

	Menu m_menu;
	Colors m_colors;
	std::vector<sf::Text> m_text_vec;
	sf::Font m_font;

	sf::RectangleShape m_exit;
	sf::Texture m_exitpng;


};

template<class Shape>
inline void Painter<Shape>::draw_graph()
{
	m_menu.draw_background(m_window);
	for (auto it = m_graph_start; it != m_graph_end; it++)
		m_window.draw(it->get_shape());
	m_colors.draw_colors(m_window);
	draw_stats();


	m_graph_start->un_visit();
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

template<class Shape>
void Painter<Shape>::update_stats(const float &player, const float& comp, const float& natural) {
	float total = player + comp + natural;

	m_text_vec.at(2).setString(std::to_string(comp/total));
	m_text_vec.at(3).setString(std::to_string(player/total));
}

template<class Shape>
void Painter<Shape>::draw_stats()
{
	for (auto& ea : m_text_vec)
		m_window.draw(ea);
}


template<class Shape>
void Painter<Shape>::set_text_vec() {
	m_font.loadFromFile("Asul-Bold.ttf");

	for (size_t i = 0; i < 4 ; i++)
	{
		m_text_vec.emplace_back();
		m_text_vec.back().setFont(m_font);
		m_text_vec.back().setCharacterSize(20);
		m_text_vec.back().setFillColor(sf::Color::White);
		m_text_vec.back().setOrigin(m_text_vec.back().getGlobalBounds().width / 2, m_text_vec.back().getGlobalBounds().height / 2);


		if (i == 0) {
			m_text_vec.back().setString("Computer:");
			m_text_vec.back().setPosition(WINDOW_WIDTH * 0.03f, WINDOW_HEIGHT * 0.9f);
		}
		if(i==1) {
			m_text_vec.back().setString("Player:");
			m_text_vec.back().setPosition(WINDOW_WIDTH * 0.8f, WINDOW_HEIGHT * 0.9f);
		}
		if (i == 2) { // computer
			m_text_vec.back().setString("1");
			m_text_vec.back().setPosition(WINDOW_WIDTH * 0.05f, WINDOW_HEIGHT * 0.95f);
		}
		if (i == 3) { // player
			m_text_vec.back().setString("1");
			m_text_vec.back().setPosition(WINDOW_WIDTH * 0.82f, WINDOW_HEIGHT * 0.95f);
		}

	}

}