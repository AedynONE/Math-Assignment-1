#include "Jelly Platforms.h"
#include "Utilities.h"

JellyPlatforms::JellyPlatforms(std::string name)
	: Scene(name)
{
	m_gravity = b2Vec2(1.f, 0.f);
	m_physicsWorld->SetGravity(m_gravity);
}

void JellyPlatforms::InitScene(float windowWidth, float windowHeight)
{
}

void JellyPlatforms::Update()
{
}

void JellyPlatforms::KeyboardHold()
{
}

void JellyPlatforms::KeyboardDown()
{
}

void JellyPlatforms::KeyboardUp()
{
}
