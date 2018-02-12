#include "Rigidbody.h"

Rigidbody::Rigidbody(EShapeType eShapeID, glm::vec2 v2Position, glm::vec2 v2Velocity, float fRotation, float fMass) : PhysicsObject(eShapeID)
{
	m_v2Position = v2Position;
	m_v2Velocity = v2Velocity;
	m_fMass = fMass;
	m_fRotation = fRotation;
}

Rigidbody::~Rigidbody()
{

}

void Rigidbody::FixedUpdate(glm::vec2 v2Gravity, float fTimeStep)
{
	ApplyForce(v2Gravity * m_fMass * fTimeStep);
	m_v2Position += m_v2Velocity * fTimeStep;

}

void Rigidbody::ApplyForce(glm::vec2 v2Force)
{
	m_v2Velocity += v2Force / m_fMass;
}

void Rigidbody::ApplyForceToActor(Rigidbody* pActor, glm::vec2 v2Force)
{
	pActor->ApplyForce(v2Force);
	this->ApplyForce(-v2Force);
}