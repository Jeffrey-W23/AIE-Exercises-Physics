#pragma once
#include "Rigidbody.h"
#include <glm\vec2.hpp>
#include <glm\vec4.hpp>

class Sphere : public Rigidbody
{
public:
	Sphere(glm::vec2 v2Position, glm::vec2 v2Velocity, float fMass, float fRadius, glm::vec4 v4Color);
	~Sphere();

	virtual void MakeGizmo();
	virtual bool CheckCollision(PhysicsObject* pOther);
	void Debug() {}
	float GetRadius() { return m_fRadius; }
	glm::vec4 GetColour() { return m_v4Color; }

protected:

	float m_fRadius;
	glm::vec4 m_v4Color;
};

