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
	if (m_operation == Operation::softMove)
	{
		std::cout << "soft" << std::endl;
		if(m_hold)
			softMove();
	}
	else if (m_operation == Operation::hardMove)
	{
		std::cout << "hard" << std::endl;
		if (m_hold)
			hardMove();
	}
	else if (m_operation == Operation::spawn)
	{
		std::cout << "spawn" << std::endl;
	}

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
		if (Operation::softMove == m_operation)
		{
			sf::Vector2f tmp = sf::Vector2f(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y);
			for (int i = 0; i < m_render->m_objects.size(); i++)
			{
				if (m_render->m_objects[i]->checkCol(tmp))
				{
					m_holdingObj = m_render->m_objects[i];
					m_hold = 1;
				}
			}
		}
		else if (m_operation == Operation::spawn)
			spawn();
	}
	else if (sf::Event::MouseButtonPressed == event.type && event.mouseButton.button == sf::Mouse::Right)
		freeze();
	else if (sf::Event::MouseButtonReleased == event.type && event.mouseButton.button == sf::Mouse::Left)
		m_hold = 0;

	else if (sf::Event::KeyPressed == event.type && event.key.code == sf::Keyboard::F2)
	{
		if (m_operation == Operation::softMove)
			m_operation = Operation::hardMove;
		else if (m_operation == Operation::hardMove)
			m_operation = Operation::spawn;
		else if (m_operation == Operation::spawn)
			m_operation = Operation::softMove;
	}

	else if (event.type == sf::Event::MouseWheelScrolled and event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
		m_operation = Operation::softMove;
	else if (event.type == sf::Event::MouseWheelScrolled and event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
		m_operation = Operation::spawn;
}

void Mouse::softMove()
{
	sf::Vector2f tmp = sf::Vector2f(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y);
	tmp.x *= 0.01f;		tmp.y *= 0.01f;
	float dst = sqrt(pow(tmp.x - m_holdingObj->m_fix->GetPosition().x, 2) + pow(tmp.y - m_holdingObj->m_fix->GetPosition().y, 2));

	b2Vec2 shit;

	shit.x = (tmp.x - m_holdingObj->m_fix->GetPosition().x) / dst;
	shit.y = (tmp.y - m_holdingObj->m_fix->GetPosition().y) / dst;

	shit *= (dst * 10);

	m_holdingObj->m_fix->ApplyForce(shit, m_holdingObj->m_fix->GetPosition(), 1);
}
void Mouse::hardMove()
{
	sf::Vector2f tmp = sf::Vector2f(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y);

	m_holdingObj->m_fix->SetTransform(b2Vec2(tmp.x * 0.01f, tmp.y * 0.01f), m_holdingObj->m_fix->GetAngle());

}
void Mouse::freeze()
{
	if(m_holdingObj->m_fix->GetType() == b2_dynamicBody)
		m_holdingObj->m_fix->SetType(b2_staticBody);
	else if (m_holdingObj->m_fix->GetType() == b2_staticBody)
		m_holdingObj->m_fix->SetType(b2_dynamicBody);
}

void Mouse::spawn()
{
	sf::Vector2f tmp = sf::Vector2f(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y);

	m_render->addObject(new Object(m_map, Shape::Rectangle, 'D', b2Vec2(0.1f, 0.1f), b2Vec2(tmp.x * 0.01f, tmp.y * 0.01f), sf::Color::Green));
}
