#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "..\Box2D\Box2D.h"

enum Shape
{
	Edge,
	Rectangle,
	Circle,
	Polygon
};

class Object
{
	public:
		Object() = default;
		Object(b2World* map, Shape shape, char type, b2Vec2 size, b2Vec2 pos, sf::Color color, float index = 0);
		~Object();

		bool checkCol(sf::Vector2f pos);
		void update();


		std::vector<sf::Vertex>		m_pShape;
		sf::RectangleShape			m_rBody;
		sf::CircleShape				m_cBody;
		sf::Transform				m_trans;
		char						m_type;
		sf::Color					m_dColor;

		b2Body*				m_fix;
		b2PolygonShape		m_polygon;
		b2CircleShape		m_circle;
		b2EdgeShape			m_edge;
		b2BodyDef			m_bodyDef;
		b2FixtureDef		m_fixtureDef;

		Shape				m_shape;
};