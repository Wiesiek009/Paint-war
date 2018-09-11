#pragma once

#include <SFML\Graphics.hpp>
#include "..\Box2D\Box2D.h"

#include "Render.hpp"
#include "Object.hpp"

enum Operation
{
	softMove,
	hardMove,
	freeze,
	spawn
};

class Mouse
{
	public:
		Mouse() = default;
		Mouse(b2World* map, Render* render, sf::RenderWindow* window);
		~Mouse();

		void update();
		void info();
		void events(sf::Event& event);
		void softMove();
		void hardMove();
		void freeze();
		void spawn();

	private:

		b2World*			m_map;
		Render*				m_render;
		sf::RenderWindow*	m_window;

		sf::Text*			m_text;
		sf::Font			m_font;
		sf::RectangleShape	m_ghostR;
		sf::CircleShape		m_ghostC;

		bool				m_show = 1;
		bool				m_hold = 0;
		Object*				m_holdingObj = nullptr;
		Operation			m_operation = Operation::softMove;
};