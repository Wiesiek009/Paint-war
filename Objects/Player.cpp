#include "Player.hpp"

Player::Player(b2World* map, Render* render)
{
	m_head = new Object(map, Shape::Circle, 'D', b2Vec2(0.125f, 1.f), b2Vec2(1.5f, 0.05f), sf::Color::Black, 2);
	m_body = new Object(map, Shape::Rectangle, 'D', b2Vec2(0.075f, 0.75f), b2Vec2(1.5f, 0.5f), sf::Color::Black, 2);

	b2RevoluteJointDef jointDef;
	jointDef.Initialize(m_head->m_fix, m_body->m_fix, b2Vec2(1.5f, 0.15f));
	b2RevoluteJoint* joint = (b2RevoluteJoint*)map->CreateJoint(&jointDef);
	m_joints.push_back(joint);

	// -------------------------------------------------------------------------------------------------------------------------------------------

	m_lArm = new Object(map, Shape::Rectangle, 'D', b2Vec2(0.075f, 0.5f), b2Vec2(1.38f, 0.38f), sf::Color::Black, 1);
	m_lArm->m_fix->SetTransform(m_lArm->m_fix->GetPosition(), 22.5f * b2_pi / 180.f);

	jointDef.Initialize(m_lArm->m_fix, m_body->m_fix, b2Vec2(1.46f, 0.16f));
	joint = (b2RevoluteJoint*)map->CreateJoint(&jointDef);
	m_joints.push_back(joint);

	// -------------------------------------------------------------------------------------------------------------------------------------------

	m_lHand = new Object(map, Shape::Rectangle, 'D', b2Vec2(0.075f, 0.5f), b2Vec2(1.29f, 0.85f), sf::Color::Black, 2);

	jointDef.Initialize(m_lHand->m_fix, m_lArm->m_fix, b2Vec2(1.29f, 0.6f));
	joint = (b2RevoluteJoint*)map->CreateJoint(&jointDef);
	m_joints.push_back(joint);

	// -------------------------------------------------------------------------------------------------------------------------------------------

	m_rArm = new Object(map, Shape::Rectangle, 'D', b2Vec2(0.075f, 0.5f), b2Vec2(1.62f, 0.38f), sf::Color::Black, 1);
	m_rArm->m_fix->SetTransform(m_rArm->m_fix->GetPosition(), -22.5f * b2_pi / 180.f);

	jointDef.Initialize(m_rArm->m_fix, m_body->m_fix, b2Vec2(1.54f, 0.16f));
	joint = (b2RevoluteJoint*)map->CreateJoint(&jointDef);
	m_joints.push_back(joint);

	// -------------------------------------------------------------------------------------------------------------------------------------------

	m_rHand = new Object(map, Shape::Rectangle, 'D', b2Vec2(0.075f, 0.5f), b2Vec2(1.71f, 0.85f), sf::Color::Black, 2);

	jointDef.Initialize(m_rHand->m_fix, m_rArm->m_fix, b2Vec2(1.71f, 0.6f));
	joint = (b2RevoluteJoint*)map->CreateJoint(&jointDef);
	m_joints.push_back(joint);

	// -------------------------------------------------------------------------------------------------------------------------------------------

	m_lThigh = new Object(map, Shape::Rectangle, 'D', b2Vec2(0.075f, 0.5f), b2Vec2(1.38f, 1.08f), sf::Color::Black, 1);
	m_lThigh->m_fix->SetTransform(m_lThigh->m_fix->GetPosition(), 22.5f * b2_pi / 180.f);

	jointDef.Initialize(m_lThigh->m_fix, m_body->m_fix, b2Vec2(1.46f, 0.86f));
	joint = (b2RevoluteJoint*)map->CreateJoint(&jointDef);
	m_joints.push_back(joint);

	// -------------------------------------------------------------------------------------------------------------------------------------------

	m_lLeg = new Object(map, Shape::Rectangle, 'D', b2Vec2(0.075f, 0.5f), b2Vec2(1.29f, 1.55f), sf::Color::Black, 2);

	jointDef.Initialize(m_lLeg->m_fix, m_lThigh->m_fix, b2Vec2(1.29f, 1.27f));
	joint = (b2RevoluteJoint*)map->CreateJoint(&jointDef);
	m_joints.push_back(joint);

	// -------------------------------------------------------------------------------------------------------------------------------------------

	m_rThigh = new Object(map, Shape::Rectangle, 'D', b2Vec2(0.075f, 0.5f), b2Vec2(1.62f, 1.08f), sf::Color::Black, 1);
	m_rThigh->m_fix->SetTransform(m_rThigh->m_fix->GetPosition(), -22.5f * b2_pi / 180.f);

	jointDef.Initialize(m_rThigh->m_fix, m_body->m_fix, b2Vec2(1.54f, 0.86f));
	joint = (b2RevoluteJoint*)map->CreateJoint(&jointDef);
	m_joints.push_back(joint);

	// -------------------------------------------------------------------------------------------------------------------------------------------

	m_rLeg = new Object(map, Shape::Rectangle, 'D', b2Vec2(0.075f, 0.5f), b2Vec2(1.71f, 1.55f), sf::Color::Black, 2);

	jointDef.Initialize(m_rLeg->m_fix, m_rThigh->m_fix, b2Vec2(1.71f, 1.27f));
	joint = (b2RevoluteJoint*)map->CreateJoint(&jointDef);
	m_joints.push_back(joint);

	 render->addObject(m_lLeg);
	 render->addObject(m_rLeg);
	 render->addObject(m_lHand);
	 render->addObject(m_rHand);
	 render->addObject(m_lArm);
	 render->addObject(m_rArm);
	 render->addObject(m_lThigh);
	 render->addObject(m_rThigh);
	 render->addObject(m_body);
	 render->addObject(m_head);
	 
}

Player::~Player()
{


}
void Player::update(float delta)
{
	//m_joints[0]->SetMotorSpeed(1000.f);
}