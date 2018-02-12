// #includes, using, etc
#include "PhysicsScene.h"
#include "Rigidbody.h"
#include <algorithm>
#include <iostream> 
#include <list>
#include <iostream>
#include "Sphere.h"
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
			sphere2->SetVelocity(glm::vec2(0, 0));

			return true;
		}
	}

	return false;
}


