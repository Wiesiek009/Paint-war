#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include "..\Box2d\Box2D.h"

#include "..\Engine\Object.hpp"
#include "..\Engine\Render.hpp"

class Player
{
	public:
		Player() = default;
		Player(b2World* map, Render* render);
		~Player();

		void update(float delta);

	private:

		std::vector<b2RevoluteJoint*>				m_joints;

		Object*			m_head;
		Object*			m_body;

		Object*			m_lArm;
		Object*			m_lHand;
		Object*			m_rArm;
		Object*			m_rHand;

		Object*			m_lThigh;
		Object*			m_lLeg;
		Object*			m_rThigh;
		Object*			m_rLeg;
};