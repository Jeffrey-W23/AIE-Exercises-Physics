// #includes, using, etc
#include "Sphere.h"
#include "Rigidbody.h"
#include "glm/glm.hpp"
#include <Gizmos.h>

//--------------------------------------------------------------------------------------
// Default Constructor.
//
// Param:
//		v2Position: a vector2 for sphere postion.
//		v2Velocity: a vector2 for sphere velocity.
//		fMass: a float value for sphere mass.
//		fRadius: a float value for sphere radius.
//		v4Color: a vector4 for sphere color.
//--------------------------------------------------------------------------------------
Sphere::Sphere(glm::vec2 v2Position, glm::vec2 v2Velocity, float fMass, float fRadius, glm::vec4 v4Color) : Rigidbody(ESHAPETYPE_SPHERE, v2Position, v2Velocity, 0, fMass)
{
	// set sphere radius
	m_fRadius = fRadius;
	
	// set sphere color.
	m_v4Color = v4Color;
}

//--------------------------------------------------------------------------------------
// Default Destructor
//--------------------------------------------------------------------------------------
Sphere::~Sphere()
{
}

//--------------------------------------------------------------------------------------
// MakeGizmo: Virtual function to make gizmo.
//--------------------------------------------------------------------------------------
void Sphere::MakeGizmo()
{
	// Add a 2d circe gizmo.
	aie::Gizmos::add2DCircle(m_v2Position, m_fRadius, 12, m_v4Color);
}

//--------------------------------------------------------------------------------------
// CheckCollision: Vitrual functon to check if the sphere is colliding with a passed in 
// pointer.
//
// Param:
//		pOther: pointer to a PhysicObject.
//--------------------------------------------------------------------------------------
bool Sphere::CheckCollision(PhysicsObject* pOther)
{
	// cast pOther to a sphere.
	Sphere* pSphere = dynamic_cast<Sphere*>(pOther);

	// if valid sphere
	if (pSphere)
	{
		// Return true if colliding.
		return ((pSphere->m_fRadius + this->m_fRadius) > glm::distance(pSphere->m_v2Position, this->m_v2Position));
	}

	// else return false.
	return false;
}
