#include "Object.hpp"

Object::Object(b2World* map, Shape shape, char type, b2Vec2 size, b2Vec2 pos, sf::Color color, float index)
{
	m_shape = shape;

	if(type == 'S')
		m_bodyDef.type = b2_staticBody;
	else
		m_bodyDef.type = b2_dynamicBody;

	if (index)
	{
		m_fixtureDef.filter.categoryBits = 0x0004;
		m_fixtureDef.filter.maskBits = 0x0006;
	}

	if (m_shape == Shape::Rectangle)
	{
		m_rBody.setSize(sf::Vector2f((size.x / 0.01f), (size.y / 0.01f)));
		m_rBody.setOrigin((size.x / 0.01f) / 2.f, (size.y / 0.01f) / 2.f);
		m_rBody.setPosition(pos.x / 0.01f, pos.y / 0.01f);

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
	}
	else if (m_shape == Shape::Circle)
	{
		m_cBody.setPosition(m_fix->GetPosition().x / 0.01f, m_fix->GetPosition().y / 0.01f);
		m_cBody.setRotation(m_fix->GetAngle() / 3.14159265359 * 180.f);
	}
	else if (m_shape == Shape::Edge)
	{
		sf::Vector2f tmp(m_fix->GetPosition().x / 0.01f, m_fix->GetPosition().y / 0.01f);
		m_trans.translate(tmp).rotate(m_fix->GetAngle() / 3.14159265359 * 180.f);
	}
}