// #includes, using, etc
#include "Rigidbody.h"

//--------------------------------------------------------------------------------------
// Default Constructor.
//
// Param:
//		eShapeID: the shapeID of the rigidbody.
//		v2Position: the position of the rigidbody.
//		v2Velocity: the velocity of the rigidbody. 
//		fRotation: the rotation of the rigidbody.
//		fMass: the mass of the rigidbody.
//--------------------------------------------------------------------------------------
Rigidbody::Rigidbody(EShapeType eShapeID, glm::vec2 v2Position, glm::vec2 v2Velocity, float fRotation, float fMass) : PhysicsObject(eShapeID)
{
	// set defaults
	m_v2Position = v2Position;
	m_v2Velocity = v2Velocity;
	m_fMass = fMass;
	m_fRotation = fRotation;
}

//--------------------------------------------------------------------------------------
// Default Destructor
//--------------------------------------------------------------------------------------
Rigidbody::~Rigidbody()
{

}

//--------------------------------------------------------------------------------------
// FixedUpdate: A function to update objects over time.
//
// Param:
//		v2Gravity: vector2 gravity to apply to the update function.
//		fTimeStep: float value for the time time step of the update.
//--------------------------------------------------------------------------------------
void Rigidbody::FixedUpdate(glm::vec2 v2Gravity, float fTimeStep)
{
	ApplyForce(v2Gravity * m_fMass * fTimeStep);
	m_v2Position += m_v2Velocity * fTimeStep;

}

//--------------------------------------------------------------------------------------
// ApplyForce: Apply force to this rigid body.
//
// Param:
//		v2Force: a vector2 of the force to be applied.
//--------------------------------------------------------------------------------------
void Rigidbody::ApplyForce(glm::vec2 v2Force)
{
	m_v2Velocity += v2Force / m_fMass;
}

//--------------------------------------------------------------------------------------
// ApplyForceToActor: Apply force to another rigidbody while applying negative 
// force to this object.
//
// Param:
//		pActor: Rigidbody pointer to apply force to.
//		v2Force: a vector2 of the force to be applied.
//--------------------------------------------------------------------------------------
void Rigidbody::ApplyForceToActor(Rigidbody* pActor, glm::vec2 v2Force)
{
	pActor->ApplyForce(v2Force);
	this->ApplyForce(-v2Force);
}