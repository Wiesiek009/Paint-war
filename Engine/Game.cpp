#include "Game.hpp"

Game::Game()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	m_window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Paint war", sf::Style::Close, settings);

	m_map = new b2World(b2Vec2(0.f, 10.f));

	m_render = new Render(m_window);

	m_mouse = Mouse(m_map, m_render, m_window);

	//for (float i = 0; i < 5; i += 0.7f)
	//	for (float j = 1; j < 3; j += 0.7f)
	//		m_render.addObject(new Object(m_map, Shape::Circle, 'D', b2Vec2(0.12f, 0.2f), b2Vec2(i, j)));

	//m_render.addObject(new Object(m_map, Shape::Edge, 'D', b2Vec2(1.f, 1.f), b2Vec2(2.f, 2.f)));
	//m_render.addObject(new Object(m_map, Shape::Circle, 'D', b2Vec2(0.5f, 1.5f), b2Vec2(1.5f, 1.5f)));

	m_render->addObject(new Object(m_map, Shape::Edge, 'S', b2Vec2(0.f, 5.f), b2Vec2(5.f, 5.f), sf::Color::White));
	m_render->addObject(new Object(m_map, Shape::Edge, 'S', b2Vec2(0.f, 0.f), b2Vec2(0.f, 5.f), sf::Color::White));
	m_render->addObject(new Object(m_map, Shape::Edge, 'S', b2Vec2(10.f, 2.5f), b2Vec2(5.f, 5.f), sf::Color::White));
	m_player = Player(m_map, m_render);

	//m_render.addObject(new Object(m_map, Shape::Edge, 'S', b2Vec2(0.f, 0.f), b2Vec2(0.f, 8.1f)));
	//m_render.addObject(new Object(m_map, Shape::Edge, 'S', b2Vec2(15.f, 1.f), b2Vec2(9.f, 9.f)));
	//m_render.addObject(new Object(m_map, Shape::Edge, 'S', b2Vec2(0.f, 0.f), b2Vec2(15.f, 1.f)));
	//m_render.addObject(new Object(m_map, Shape::Rectangle, 'D', b2Vec2(1.f, 1.f), b2Vec2(4.f, 4.f)));
}

Game::~Game()
{

}

void Game::mainLoop()
{
	while (m_window->isOpen())
	{
		events();

		if (m_pause)
		{
			m_player.update(m_delta);
			update();
		}

		m_mouse.update();

		m_render->draw();

		m_delta = m_clock.restart().asSeconds();
		if (m_delta > 1.f)
			m_delta = 1.f;
	}
}

void Game::events()
{
	while (m_window->pollEvent(m_event))
	{
		if (sf::Event::Closed == m_event.type)
			m_window->close();

		else if (sf::Event::KeyPressed == m_event.type && m_event.key.code == sf::Keyboard::Space)
		{
			if (m_pause)
				m_pause = 0;
			else
				m_pause = 1;
		}

		m_mouse.events(m_event);
	}
}

void Game::update()
{
	m_map->Step(m_delta, 8, 3);
}
