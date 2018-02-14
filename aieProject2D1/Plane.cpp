// #includes, using, etc
#include "Plane.h"
#include <Gizmos.h>
#include "PhysicsObject.h"

//--------------------------------------------------------------------------------------
// Constructor.
//
// Param:
//		v2Normal: a vector2 for the normal of the plane.
//		fDistance: a float value for the distance of the plane. 
//--------------------------------------------------------------------------------------
Plane::Plane(glm::vec2 v2Normal, float fDistance) : PhysicsObject(ESHAPETYPE_PLANE)
{
	// set defaults
	m_fDistanceToOrigin = 0;
	m_v2Normal = glm::vec2(0,1);
	m_v2CentrePoint = m_v2Normal * m_fDistanceToOrigin;
}

//--------------------------------------------------------------------------------------
// Default Destructor
//--------------------------------------------------------------------------------------
Plane::~Plane()
{
}

//--------------------------------------------------------------------------------------
// MakeGizmo: Create the plane gizmo.
//--------------------------------------------------------------------------------------
void Plane::MakeGizmo() 
{
	// make the plane object
	float fLineSegmentLength = 300; 
	glm::vec2 v2CenterPoint = m_v2Normal * m_fDistanceToOrigin;
	glm::vec2 v2Parallel(m_v2Normal.y, -m_v2Normal.x);
	glm::vec4 v4Colour(1, 1, 1, 1); 
	glm::vec2 v2Start = v2CenterPoint + (v2Parallel * fLineSegmentLength);
	glm::vec2 v2End = v2CenterPoint - (v2Parallel * fLineSegmentLength);
	aie::Gizmos::add2DLine(v2Start, v2End, v4Colour);
}

//--------------------------------------------------------------------------------------
// FixedUpdate: A function to update objects over time.
//
// Param:
//		v2Gravity: vector2 gravity to apply to the update function.
//		fTimeStep: float value for the time time step of the update.
//--------------------------------------------------------------------------------------
void Plane::FixedUpdate(glm::vec2 gravity, float timeStep)
{
}

//--------------------------------------------------------------------------------------
// ResetPosition: Reset the postion of the plane.
//--------------------------------------------------------------------------------------
void Plane::ResetPosition()
{
}