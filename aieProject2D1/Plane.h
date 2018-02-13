#pragma once
#include "PhysicsObject.h"

class Plane : public PhysicsObject
{
public: 
	Plane() = delete;
	Plane(glm::vec2 normal, float distance); 
	~Plane(); 

	virtual void FixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void Debug() {} 
	virtual void MakeGizmo(); 
	virtual void ResetPosition();

	glm::vec2 getCentre() { return m_centrePoint; }
	glm::vec2 getNormal() { return m_normal; } 
	float getDistance() { return m_distanceToOrigin; }

protected: 
	glm::vec2 m_normal;
	glm::vec2 m_centrePoint;
	float m_distanceToOrigin;
};

