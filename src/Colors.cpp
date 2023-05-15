
#include "Colors.h"
#include<iostream>
void Colors::setColors() {
	
	m_frame.setFillColor(sf::Color::White);
	m_red.setFillColor( sf::Color::Red) ;
	m_pink.setFillColor( sf::Color::Magenta);
	m_green.setFillColor(sf::Color::Green);
	m_blue.setFillColor(sf::Color::Blue);
	m_yellow.setFillColor(sf::Color::Yellow);
	m_cyan.setFillColor(sf::Color::Cyan);
}

void Colors::setLocation() {

	std::cout << m_width << "\n";
	m_red.setOrigin(m_red.getGlobalBounds().width / 2, m_red.getGlobalBounds().height / 2);
	m_yellow.setOrigin(m_red.getGlobalBounds().width / 2, m_red.getGlobalBounds().height / 2);
	m_blue.setOrigin(m_red.getGlobalBounds().width / 2, m_red.getGlobalBounds().height / 2);
	m_green.setOrigin(m_red.getGlobalBounds().width / 2, m_red.getGlobalBounds().height / 2);
	m_cyan.setOrigin(m_red.getGlobalBounds().width / 2, m_red.getGlobalBounds().height / 2);
	m_pink.setOrigin(m_red.getGlobalBounds().width / 2, m_red.getGlobalBounds().height / 2);

	m_frame.setPosition(0, m_height * 0.8);
	//float x = m_frame.getPosition().x;
	//float y = m_frame.getPosition().y;

	auto x = m_width/2;
	auto y = m_height*0.9;

	m_red.setPosition(sf::Vector2f(x - m_red.getGlobalBounds().width, y));
	m_yellow.setPosition(sf::Vector2f(x - m_red.getGlobalBounds().width*3.f , y));
	m_green.setPosition(sf::Vector2f(x - m_red.getGlobalBounds().width *5.f, y));
	m_blue.setPosition(sf::Vector2f(x + m_red.getGlobalBounds().width * 1.f, y));
	m_cyan.setPosition(sf::Vector2f(x + m_red.getGlobalBounds().width * 3.f, y));
	m_pink.setPosition(sf::Vector2f(x  + m_red.getGlobalBounds().width * 5.f, y));
	std::cout << m_yellow.getPosition().x << " " << m_red.getPosition().x << "\n";
}

void Colors::drawMenu( sf::RenderWindow& w) {

	w.draw(m_frame);
	w.draw(m_red);
	w.draw(m_blue);
	w.draw(m_cyan);
	w.draw(m_green);
	w.draw(m_pink);
	w.draw(m_yellow);
}

void Colors::setSize(){

	m_red.setSize(sf::Vector2f(30.f, 30.f));
	m_blue.setSize(sf::Vector2f(30.f, 30.f));
	m_cyan.setSize(sf::Vector2f(30.f, 30.f));
	m_pink.setSize(sf::Vector2f(30.f, 30.f));
	m_yellow.setSize(sf::Vector2f(30.f, 30.f));
	m_green.setSize(sf::Vector2f(30.f, 30.f));

}