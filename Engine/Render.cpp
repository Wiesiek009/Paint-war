#include "Render.hpp"

Render::Render(sf::RenderWindow* window)
{
	m_window = window;
}

Render::~Render()
{

}

void Render::clear()
{

}

void Render::addObject(Object* object)
{
	m_objects.push_back(object);
}

void Render::addObject(sf::Text* text)
{
	m_text = text;
}

void Render::addObject(std::vector<Object*> objects)
{
	m_objects.insert(m_objects.end(), objects.begin(), objects.end());
}

void Render::draw()
{
	m_window->clear(sf::Color(50, 50, 50));

	//m_window->draw(*m_text);

	for (int i = 0; i < m_objects.size(); i++)
	{
		m_objects[i]->update();

		if(m_objects[i]->m_shape == Shape::Rectangle)
			m_window->draw(m_objects[i]->m_rBody);

		else if (m_objects[i]->m_shape == Shape::Edge)
		{
			m_window->draw(&m_objects[i]->m_pShape[0], m_objects[i]->m_pShape.size(), sf::Lines, m_objects[i]->m_trans);
		}

		else if (m_objects[i]->m_shape == Shape::Circle)
		{
			m_window->draw(m_objects[i]->m_cBody);
		}
	}

	m_window->display();
}