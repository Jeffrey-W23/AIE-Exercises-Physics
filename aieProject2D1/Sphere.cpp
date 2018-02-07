#include "Sphere.h"
#include "Rigidbody.h"
#include "glm/glm.hpp"
#include <Gizmos.h>

Sphere::Sphere(glm::vec2 v2Position, glm::vec2 v2Velocity, float fMass, float fRadius, glm::vec4 v4Color) : Rigidbody(ESHAPETYPE_SPHERE, v2Position, v2Velocity, 0, fMass)
{
	m_fRadius = fRadius;
	m_v4Color = v4Color;

}

Sphere::~Sphere()
{


}

void Sphere::MakeGizmo()
{
	aie::Gizmos::add2DCircle(m_v2Position, m_fRadius, 12, m_v4Color);
}

bool Sphere::CheckCollision(PhysicsObject* pOther)
{
	Sphere* pSphere = dynamic_cast<Sphere*>(pOther);

	if (pSphere)
	{
		return ((pSphere->m_fRadius + this->m_fRadius) > glm::distance(pSphere->m_v2Position, this->m_v2Position));

	}

	return false;
}
