#include "Object.hpp"

Object::Object(b2World* map, Shape shape, char type, b2Vec2 size, b2Vec2 pos, sf::Color color, float index)
{
	m_shape = shape;
	m_dColor = color;

	if(type == 'S')
		m_bodyDef.type = b2_staticBody;
	else
		m_bodyDef.type = b2_dynamicBody;

	if (index == 1)
	{
		m_fixtureDef.filter.categoryBits = 0x0002;
		m_fixtureDef.filter.maskBits = 0x0001;
	}
	else if(index == 2)
	{
		m_fixtureDef.filter.categoryBits = 0x0003;
		m_fixtureDef.filter.maskBits = 0x0001;
	}

	if (m_shape == Shape::Rectangle)
	{
		m_rBody.setSize(sf::Vector2f((size.x / 0.01f), (size.y / 0.01f)));
		m_rBody.setOrigin((size.x / 0.01f) / 2.f, (size.y / 0.01f) / 2.f);
		m_rBody.setPosition(pos.x / 0.01f, pos.y / 0.01f);
		m_rBody.setOutlineColor(sf::Color::Green);

		m_rBody.setFillColor(color);

		m_bodyDef.position.Set(pos.x, pos.y);

		m_fix = map->CreateBody(&m_bodyDef);

		m_polygon.SetAsBox(size.x / 2.f, size.y / 2.f);
	

		m_fixtureDef.shape = &m_polygon;
		m_fixtureDef.density = 1.0f;

		m_fix->CreateFixture(&m_fixtureDef);
	}

	else if (m_shape == Shape::Edge)
	{
		m_pShape.push_back(sf::Vertex(sf::Vector2f(size.x / 0.01f, size.y / 0.01f), color));
		m_pShape.push_back(sf::Vertex(sf::Vector2f(pos.x / 0.01f, pos.y / 0.01f), color));

		m_fix = map->CreateBody(&m_bodyDef);

		m_edge.Set(size, pos);

		m_fixtureDef.shape = &m_edge;
		m_fixtureDef.density = 1.0f;

		m_fix->CreateFixture(&m_fixtureDef);
	}

	else if (m_shape == Shape::Circle)
	{
		m_cBody.setRadius(size.x / 0.01f);
		m_cBody.setOrigin(m_cBody.getRadius(), m_cBody.getRadius());
		m_cBody.setPosition(pos.x / 0.01f, pos.y / 0.01f);
		m_cBody.setOutlineColor(sf::Color::Green);

		m_cBody.setFillColor(color);

		m_bodyDef.position.Set(pos.x, pos.y);

		m_fix = map->CreateBody(&m_bodyDef);

		m_circle.m_radius = size.x;

		m_fixtureDef.shape = &m_circle;
		m_fixtureDef.density = 1.0f;

		m_fix->CreateFixture(&m_fixtureDef);
	}
}

Object::~Object()
{

}

void Object::update()
{
	if (m_shape == Shape::Rectangle)
	{
		m_rBody.setPosition(m_fix->GetPosition().x / 0.01f, m_fix->GetPosition().y / 0.01f);
		m_rBody.setRotation(m_fix->GetAngle() / 3.14159265359 * 180.f);

		if (m_fix->GetType() == b2_staticBody)
			m_rBody.setFillColor(sf::Color::Blue);
		else
			m_rBody.setFillColor(m_dColor);

		m_rBody.setOutlineThickness(0.f);
	}
	else if (m_shape == Shape::Circle)
	{
		m_cBody.setPosition(m_fix->GetPosition().x / 0.01f, m_fix->GetPosition().y / 0.01f);
		m_cBody.setRotation(m_fix->GetAngle() / 3.14159265359 * 180.f);

		if (m_fix->GetType() == b2_staticBody)
			m_cBody.setFillColor(sf::Color::Blue);
		else
			m_cBody.setFillColor(m_dColor);

		m_cBody.setOutlineThickness(0.f);
	}
	else if (m_shape == Shape::Edge)
	{
		sf::Vector2f tmp(m_fix->GetPosition().x / 0.01f, m_fix->GetPosition().y / 0.01f);
		m_trans.translate(tmp).rotate(m_fix->GetAngle() / 3.14159265359 * 180.f);
	}
}

bool Object::checkCol(sf::Vector2f pos)
{
	if (m_shape == Shape::Circle)
	{
		float dst = sqrt(pow(m_cBody.getPosition().x - pos.x, 2) + pow(m_cBody.getPosition().y - pos.y, 2));

		if (dst < m_cBody.getRadius())
			return true;
		else
			return false;
	}
	else if (m_shape == Shape::Rectangle)
	{
		if (m_rBody.getGlobalBounds().contains(pos))
			return true;
		else
			return false;
	}
	else
		return false;
}