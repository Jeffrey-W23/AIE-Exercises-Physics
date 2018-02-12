// #includes, using, etc
#include "PhysicsScene.h"
#include "Rigidbody.h"
#include <algorithm>
#include <iostream> 
#include <list>
#include <iostream>
#include "Sphere.h"
#include "Plane.h"
#include "Box.h"
#include <glm\ext.hpp>
#include <glm\glm.hpp>

// function pointer array for doing our collisions 
typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFunctionArray[] = { 
	PhysicsScene::plane2Plane, PhysicsScene::plane2Sphere, PhysicsScene::plane2Box, 
	PhysicsScene::sphere2Sphere, PhysicsScene::sphere2Plane, PhysicsScene::sphere2Box, 
	PhysicsScene::box2Plane, PhysicsScene::box2Sphere, PhysicsScene::box2Box,
}; 

//--------------------------------------------------------------------------------------
// Default Constructor.
//--------------------------------------------------------------------------------------
PhysicsScene::PhysicsScene()
{
	// set defalut for timestep
	m_fTimeStep = 0.01f;
}

//--------------------------------------------------------------------------------------
// Default Destructor
//--------------------------------------------------------------------------------------
PhysicsScene::~PhysicsScene()
{
	for (auto pActor : m_apActors)
	{
		delete pActor;
	}
}

//--------------------------------------------------------------------------------------
// AddActor: 
//
// Param:
//		pActor:
//--------------------------------------------------------------------------------------
void PhysicsScene::AddActor(PhysicsObject* actor)
{
	// Add actor to the array.
	m_apActors.push_back(actor);
}

//--------------------------------------------------------------------------------------
// RemoveActor: 
//
// Param:
//		pActor:
//--------------------------------------------------------------------------------------
void PhysicsScene::RemoveActor(PhysicsObject* actor)
{
	// Remove actor from thr array.
	std::remove(std::begin(m_apActors), std::end(m_apActors), actor);
}

//--------------------------------------------------------------------------------------
// Update: 
//
// Param:
//		deltaTime:
//--------------------------------------------------------------------------------------
void PhysicsScene::Update(float dt)
{



	static std::list<PhysicsObject*> dirty;






	// update physics at a fixed time step
	static float fAccumulatedTime = 0.0f;

	// update accumulatedTim by deltaTime
	fAccumulatedTime += dt;
	
	// while the accumulated time is greater than the Time step
	while (fAccumulatedTime >= m_fTimeStep)
	{
		// loop through actors array
		for (auto pActor : m_apActors)
		{
			// Update actor
			pActor->FixedUpdate(m_v2Gravity, m_fTimeStep);
		}

		checkForCollision();

		// update accumulated time by the time step
		fAccumulatedTime -= m_fTimeStep;






		// check for collisions (ideally you'd want to have some sort of
		// scene management in place)
		/*for (auto pActor : m_apActors) 
		{
			for (auto pOther : m_apActors)
			{
				if (pActor == pOther)
					continue;

				if (std::find(dirty.begin(), dirty.end(), pActor) != dirty.end() &&
					std::find(dirty.begin(), dirty.end(), pOther) != dirty.end())
					continue;

				Rigidbody* pRigid = dynamic_cast<Rigidbody*>(pActor);
				
				if (pRigid->CheckCollision(pOther) == true) 
				{
					pRigid->ApplyForceToActor(dynamic_cast<Rigidbody*>(pOther),
					pRigid->GetVelocity() * pRigid->GetMass());
					dirty.push_back(pRigid);
					dirty.push_back(pOther);
				}
			}
		}

		dirty.clear();*/
	
	
	
	
	}
}

//--------------------------------------------------------------------------------------
// UpdateGizmos: 
//--------------------------------------------------------------------------------------
void PhysicsScene::UpdateGizmos()
{
	// loop through the actors
	for (auto pActor : m_apActors) 
	{	
		// Make actor Gizmo
		pActor->MakeGizmo();
	}

}

//--------------------------------------------------------------------------------------
// UpdateGizmos: 
//--------------------------------------------------------------------------------------
void PhysicsScene::DebugScene()
{
	int count = 0;
	
	for (auto pActor : m_apActors) 
	{
		std::cout << count << " : ";
		pActor->Debug();
		count++;
	}
}

void PhysicsScene::checkForCollision()
{
	int actorCount = m_apActors.size();
	//need to check for collisions against all objects except this one. 
	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* object1 = m_apActors[outer];
			PhysicsObject* object2 = m_apActors[inner];
			int shapeId1 = object1->GetShapeID();
			int shapeId2 = object2->GetShapeID();

			// using function pointers 
			int functionIdx = (shapeId1 * ESHAPETYPE_COUNT) + shapeId2;
			fn collisionFunctionPtr = collisionFunctionArray[functionIdx];

			if (collisionFunctionPtr != nullptr)
			{
				// did a collision occur? 
				collisionFunctionPtr(object1, object2);
			}
		}
	}
}

bool PhysicsScene::sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	//try to cast objects to sphere and sphere 
	Sphere* sphere1 = dynamic_cast<Sphere*>(obj1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(obj2);

	//if we are successful then test for collision 
	if (sphere1 != nullptr && sphere2 != nullptr)
	{
		glm::vec2 distance = sphere1->GetPosition() - sphere2->GetPosition();

		float TotalRad = sphere1->GetRadius() + sphere2->GetRadius();

		if (glm::length(distance) <= TotalRad)
		{
			sphere1->SetVelocity(glm::vec2(0,0));
			sphere2->SetVelocity(glm::vec2(0,0));

			return true;
		}
	}

	return false;
}

bool PhysicsScene::plane2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// Return to this later and finish.
	return false;
}

bool PhysicsScene::plane2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return (sphere2Plane(obj2, obj1));
}

bool PhysicsScene::sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Sphere* sphere = dynamic_cast<Sphere*>(obj1);
	Plane* plane = dynamic_cast<Plane*>(obj2);

	if (sphere != nullptr && plane != nullptr)
	{
		glm::vec2 collisionNormal = plane->getNormal();
		float sphereToPlane = glm::dot(sphere->GetPosition(), plane->getNormal()) - plane->getDistance();

		if (sphereToPlane < 0)
		{
			collisionNormal *= -1;
			sphereToPlane *= -1;
		}

		float intersection = sphere->GetRadius() - sphereToPlane;

		if (intersection > 0)
		{
			sphere->SetVelocity(glm::vec2(0, 0));
			
			return true;
		}
	}

	return false;
}

bool PhysicsScene::plane2Box(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Plane* plane = dynamic_cast<Plane*>(obj1);
	Box* box = dynamic_cast<Box*>(obj2);

	if (plane != nullptr || box != nullptr)
	{
		glm::vec2 v = box->GetPosition() - plane->getCentre();
		glm::vec2 halfWidth = box->GetPosition() + glm::vec2(box->getWidth() * 0.5f, box->getHeight());
		glm::vec2 halfHeight = box->GetPosition() + glm::vec2(box->getWidth(), box->getHeight() * 0.5f);

		if (glm::length(v) < glm::length(halfWidth) || glm::length(v) < glm::length(halfHeight))
		{
			box->SetVelocity(glm::vec2(0, 0));

			return true;
		}
	}

	return false;
}

bool PhysicsScene::sphere2Box(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Sphere* sphere = dynamic_cast<Sphere*>(obj1);
	Box* box = dynamic_cast<Box*>(obj2);

	if (sphere != nullptr && box != nullptr)
	{
		glm::vec2 a = glm::clamp(sphere->GetPosition(), box->getMin(), box->getMax());
		glm::vec2 v = a - sphere->GetPosition();

		if (glm::length(v) <= sphere->GetRadius())
		{
			sphere->SetVelocity(glm::vec2(0, 0));
			box->SetVelocity(glm::vec2(0, 0));

			return true;
		}
	}

	return false;
}

bool PhysicsScene::box2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return (plane2Box(obj2, obj1));
}

bool PhysicsScene::box2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return (sphere2Box(obj2, obj1));
}

bool PhysicsScene::box2Box(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Box* box1 = dynamic_cast<Box*>(obj1);
	Box* box2 = dynamic_cast<Box*>(obj2);

	if (box1 != nullptr && box2 != nullptr)
	{
		glm::vec2 min1 = box1->getMin();
		glm::vec2 max1 = box1->getMax();

		glm::vec2 min2 = box2->getMin();
		glm::vec2 max2 = box2->getMax();

		if (max1.x < min2.x || max2.x < min1.x || max1.y < min2.y || max2.y < min1.y)
		{
			return false;
		}
		else
		{
			box1->SetVelocity(glm::vec2(0, 0));
			box2->SetVelocity(glm::vec2(0, 0));

			return true;
		}
	}

	return false;
}