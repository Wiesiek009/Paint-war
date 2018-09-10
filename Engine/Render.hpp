#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include "Object.hpp"

class Render
{
	public:
		Render() = default;
		Render(sf::RenderWindow* window);
		~Render();

		void clear();
		void addObject(Object* object);
		void addObject(std::vector<Object*> objects);
		void addObject(sf::Text* text);
		void draw();

	private:

		sf::RenderWindow*			m_window;
		std::vector<Object*>		m_objects;
		sf::Text*					m_text;
};