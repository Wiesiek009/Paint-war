#pragma once

#include <SFML\Graphics.hpp>
#include "..\Box2D\Box2D.h"

#include "Render.hpp"
#include "Object.hpp"

class Mouse
{
	public:
		Mouse() = default;
		Mouse(b2World* map, Render* render, sf::RenderWindow* window);
		~Mouse();

		void update();
		void info();
		void events(sf::Event& event);
		void createBox();
		void createCircle();

	private:

		b2World*			m_map;
		Render*				m_render;
		sf::RenderWindow*	m_window;

		sf::Text*			m_text;
		sf::Font			m_font;
		sf::RectangleShape	m_ghostR;
		sf::CircleShape		m_ghostC;

		bool				m_show = 1;
};