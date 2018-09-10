#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include "..\Box2D\Box2D.h"
#include <stdio.h>

#include "Render.hpp"
#include "Object.hpp"
#include "..\Objects\Player.hpp"
#include "Mouse.hpp"

class Game
{
	public:
		Game();
		~Game();

		void mainLoop();

		void events();
		void update();

	private:

		sf::RenderWindow*	m_window;
		Render*				m_render;
		sf::Event			m_event;
		Mouse				m_mouse;

		b2World*			m_map;
		Player				m_player;

		sf::Clock			m_clock;
		float32				m_delta;

		bool				m_pause = 0;
		sf::Vector2i		m_tmp;
		b2Vec2				m_last;

};