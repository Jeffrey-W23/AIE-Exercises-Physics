#pragma once
#include "PhysicsObject.h"

class Rigidbody : public PhysicsObject 
{
public:
	
	Rigidbody(EShapeType eShapeID, glm::vec2 v2Position, glm::vec2 v2Velocity, float fRotation, float fMass);
	~Rigidbody();

	virtual void FixedUpdate(glm::vec2 v2Gravity, float fTimeStep);
	virtual void Debug() {}
	void ApplyForce(glm::vec2 v2Force);
	void ApplyForceToActor(Rigidbody* pActor, glm::vec2 v2Force);
	
	glm::vec2 GetPosition() { return m_v2Position; }
	float GetRotation() { return m_fRotation; }
	glm::vec2 GetVelocity() { return m_v2Velocity; }
	void SetVelocity(glm::vec2 v2Value) { m_v2Velocity = v2Value; }
	float GetMass() { return m_fMass; }

protected:
	
	glm::vec2 m_v2Position;
	glm::vec2 m_v2Velocity;
	float m_fMass;
	float m_fRotation;
};