#include "Mouse.hpp"

Mouse::Mouse(b2World* map, Render* render, sf::RenderWindow* window)
{
	m_map = map;
	m_render = render;
	m_window = window;

	m_font.loadFromFile("font.ttf");
	m_text = new sf::Text("Kupa", m_font);

	m_render->addObject(m_text);
}
Mouse::~Mouse()
{

}

void Mouse::update()
{


	info();
}

void Mouse::info()
{
	if (m_show)
	{
		sf::Vector2i* tmp1 = new sf::Vector2i(sf::Mouse::getPosition(*m_window));
		//m_text->setString("Kupa \n Inna kupa");
	}
	//else
	//	m_text->setString("");
}

void Mouse::events(sf::Event& event)
{
	if (sf::Event::MouseButtonPressed == event.type && event.mouseButton.button == sf::Mouse::Left)
	{
		
	}

	else if (sf::Event::KeyPressed == event.type && event.key.code == sf::Keyboard::F2)
	{
		if (m_show)
			m_show = 0;
		else
			m_show = 1;
	}

}


void Mouse::createBox()
{

}
void Mouse::createCircle()
{

}