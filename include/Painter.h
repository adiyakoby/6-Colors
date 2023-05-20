#pragma

#include "Colors.h"
#include "Menu.h"

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;

enum class game_state { CONT, WON, LOST, NEW };


template<class Shape>
class Painter
{
public:
	Painter(sf::RenderWindow& window) : m_menu(WINDOW_WIDTH, WINDOW_HEIGHT), m_colors(std::make_unique<Colors>(WINDOW_WIDTH, WINDOW_HEIGHT)), m_window{ window }								
	{
		set_text_vec();
	};
	~Painter() = default;


	bool is_new(const sf::Vector2f& pos);
	void reset_game();

	void set_start_it(Graph<Shape>::GraphIterator it_start) { m_graph_start = it_start; };
	void set_end_it(Graph<Shape>::GraphIterator it_end) { m_graph_end = it_end; };
	void draw_graph(const game_state& state);
	void draw_menu() { m_menu.draw(m_window); }
	void draw_stats();
	void update_stats(const float& player, const float& comp, const float& natural);

	menu_state get_mode(const sf::Vector2f & pos) { return m_menu.get_choice(pos); };
	sf::Color check_for_color(const float& x, const float& y);

	void draw_x(const sf::Color& color, const Owner& type) { m_colors->draw_x(color, type); };
	void print_victorious(const game_state & state);

private:

	Graph<Shape>::GraphIterator m_graph_start;
	Graph<Shape>::GraphIterator m_graph_end;

	sf::RenderWindow& m_window;

	Menu m_menu;
	std::unique_ptr<Colors> m_colors;

	std::vector<sf::Text> m_text_vec;
	sf::Font m_font;

	//private funcs
	void set_text_vec();

};

template<class Shape>
inline void Painter<Shape>::reset_game()
{
	m_colors = std::make_unique<Colors>(WINDOW_WIDTH, WINDOW_HEIGHT);
}

template<class Shape>
inline void Painter<Shape>::print_victorious(const game_state& state)
{
	std::string who_won{};
	if (state == game_state::WON) who_won = "Player Won !";
	else if (state == game_state::LOST) who_won = "Computer Won !";
	m_text_vec.at(5).setString(who_won);

	m_window.draw(m_text_vec.at(5));

}
template<class Shape>
inline void Painter<Shape>::draw_graph(const game_state& state)
{
	m_menu.draw_background(m_window);
	for (auto it = m_graph_start; it != m_graph_end; it++)
		m_window.draw(it->get_shape());

	m_colors->draw_colors(m_window);
	draw_stats();

	if (state != game_state::CONT)
		print_victorious(state);

	m_graph_start->un_visit();
}
template<class Shape>
bool Painter<Shape>::is_new(const sf::Vector2f& pos) 
{ 
	if (m_text_vec.at(4).getGlobalBounds().contains(pos)) 
		return true; 
	return false; 
};

template<class Shape>
sf::Color Painter<Shape>::check_for_color(const float& x, const float& y) {
	return m_colors->check_for_color(x, y); 
};


template<class Shape>
void Painter<Shape>::update_stats(const float &player, const float& comp, const float& natural) {
	float total = player + comp + natural;

	m_text_vec.at(2).setString(std::to_string(player/total));
	m_text_vec.at(3).setString(std::to_string(comp/total));
}

template<class Shape>
void Painter<Shape>::draw_stats()
{
	for (size_t i = 0; i < m_text_vec.size()-1; i++)
		m_window.draw(m_text_vec.at(i));		
}


template<class Shape>
void Painter<Shape>::set_text_vec() {
	m_font.loadFromFile("Asul-Bold.ttf");

	for (size_t i = 0; i < 6 ; i++)
	{
		m_text_vec.emplace_back();
		m_text_vec.back().setFont(m_font);
		m_text_vec.back().setCharacterSize(20);
		m_text_vec.back().setFillColor(sf::Color::White);
		m_text_vec.back().setOrigin(m_text_vec.back().getGlobalBounds().width *0.5f , m_text_vec.back().getGlobalBounds().height * 0.5f);


		if (i == 0) {
			m_text_vec.back().setString("Player:");
			m_text_vec.back().setPosition(WINDOW_WIDTH * 0.03f, WINDOW_HEIGHT * 0.9f);
		}
		if(i==1) {
			m_text_vec.back().setString("Computer:");
			m_text_vec.back().setPosition(WINDOW_WIDTH * 0.8f, WINDOW_HEIGHT * 0.9f);
		}
		if (i == 2) { // player
			m_text_vec.back().setString("0");
			m_text_vec.back().setPosition(WINDOW_WIDTH * 0.05f, WINDOW_HEIGHT * 0.95f);
		}
		if (i == 3) { // Computer
			m_text_vec.back().setString("0");
			m_text_vec.back().setPosition(WINDOW_WIDTH * 0.82f, WINDOW_HEIGHT * 0.95f);
		}
		if (i == 4) {
			m_text_vec.back().setString("New Game");
			m_text_vec.back().setPosition(WINDOW_WIDTH *0.45f, WINDOW_HEIGHT * 0.05f);
		}
		if (i == 5) {
			m_text_vec.back().setCharacterSize(50);
			m_text_vec.back().setString(" ");
			m_text_vec.back().setPosition(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f);
		}

	}

}