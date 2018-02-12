#pragma once
#include "PhysicsObject.h"

class Plane : PhysicsObject
{
public: 
	Plane() = delete;
	Plane(glm::vec2 normal, float distance); 
	~Plane(); 

	virtual void FixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void Debug() {} 
	virtual void MakeGizmo(); 
	virtual void ResetPosition();

	glm::vec2 getNormal() { return m_normal; } 
	float getDistance() { return m_distanceToOrigin; }

protected: 
	glm::vec2 m_normal; 
	float m_distanceToOrigin;
};

