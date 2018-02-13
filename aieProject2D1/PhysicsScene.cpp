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

// function pointer array for doing collisions 
typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

// Array of PhysicsScene functions.
static fn collisionFunctionArray[] = { 
	PhysicsScene::PlaneToPlane, PhysicsScene::PlaneToSphere, PhysicsScene::PlaneToBox,
	PhysicsScene::SphereToPlane, PhysicsScene::SphereToSphere, PhysicsScene::SphereToBox,
	PhysicsScene::BoxToPlane, PhysicsScene::BoxToSphere, PhysicsScene::BoxToBox,
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
	// loop through each actor
	for (auto pActor : m_apActors)
	{
		// delete each actor
		delete pActor;
	}
}

//--------------------------------------------------------------------------------------
// AddActor: Add an object to the scene.
//
// Param:
//		pActor: the object to add to the scene.
//--------------------------------------------------------------------------------------
void PhysicsScene::AddActor(PhysicsObject* actor)
{
	// Add actor to the array.
	m_apActors.push_back(actor);
}

//--------------------------------------------------------------------------------------
// RemoveActor: An Object to remove from the scene.
//
// Param:
//		pActor: the object to remove from the scene.
//--------------------------------------------------------------------------------------
void PhysicsScene::RemoveActor(PhysicsObject* actor)
{
	// Remove actor from thr array.
	std::remove(std::begin(m_apActors), std::end(m_apActors), actor);
}

//--------------------------------------------------------------------------------------
// Update: A function to update objects over time.
//
// Param:
//		deltaTime: Pass in deltaTime. A number that updates per second.
//--------------------------------------------------------------------------------------
void PhysicsScene::Update(float deltaTime)
{
	// update physics at a fixed time step
	static float fAccumulatedTime = 0.0f;

	// update accumulatedTime by deltaTime
	fAccumulatedTime += deltaTime;
	
	// while the accumulated time is greater than the Time step
	while (fAccumulatedTime >= m_fTimeStep)
	{
		// loop through actors array
		for (auto pActor : m_apActors)
		{
			// Update actors
			pActor->FixedUpdate(m_v2Gravity, m_fTimeStep);
		}

		// Check for a collision.
		CheckCollision();

		// update accumulated time by the time step
		fAccumulatedTime -= m_fTimeStep;
	}
}

//--------------------------------------------------------------------------------------
// UpdateGizmos: Update the scene and scene object gizmos.
//--------------------------------------------------------------------------------------
void PhysicsScene::UpdateGizmos()
{
	// loop through the actors
	for (auto pActor : m_apActors) 
	{	
		// Make actor Gizmos
		pActor->MakeGizmo();
	}
}

//--------------------------------------------------------------------------------------
// DebugScene: Debugging function for the scene.
//--------------------------------------------------------------------------------------
void PhysicsScene::DebugScene()
{
	// new int for count
	int nCount = 0;
	
	// loop through each actor
	for (auto pActor : m_apActors) 
	{

		// cout the count value
		std::cout << nCount << " : ";

		// run actor debug
		pActor->Debug();

		// increment count
		nCount++;
	}
}

//--------------------------------------------------------------------------------------
// CheckCollision: Check for a collision between objects.
//--------------------------------------------------------------------------------------
void PhysicsScene::CheckCollision()
{
	// new int value for the actor array size
	int nActorCount = m_apActors.size();
	
	//need to check for collisions against all objects except this one.
	// loop through each actor
	for (int o = 0; o < nActorCount - 1; o++)
	{
		// loop through each actor plus 1
		for (int i = o + 1; i < nActorCount; i++)
		{
			// Check the 2 objects that could be colliding.
			PhysicsObject* object1 = m_apActors[o];
			PhysicsObject* object2 = m_apActors[i];
			
			// get shapeIds of these objects.
			int nShapeId1 = object1->GetShapeID();
			int nShapeId2 = object2->GetShapeID();

			// figure out the shapes that are colliding and which function to run.
			int functionIdx = (nShapeId1 * ESHAPETYPE_COUNT) + nShapeId2;
			fn collisionFunctionPtr = collisionFunctionArray[functionIdx];

			// if the function pointer is valid.
			if (collisionFunctionPtr != nullptr)
			{
				// Check collision of the 2 objects. 
				collisionFunctionPtr(object1, object2);
			}
		}
	}
}










//--------------------------------------------------------------------------------------
// PlaneToPlane: Check a collison between a plane and another plane.
//
// Return:
//		bool: Return true or false for if a collision has happened.
// Param:
//		obj1: Object 1 for the collison check.
//		obj2: Object 2 for the collision check.
//--------------------------------------------------------------------------------------
bool PhysicsScene::PlaneToPlane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// Return to this later and finish. //TODO
	return false;
}










//--------------------------------------------------------------------------------------
// PlaneToSphere: Check a collison between a plane and a sphere.
//
// Return:
//		bool: Return true or false for if a collision has happened.
// Param:
//		obj1: Object 1 for the collison check.
//		obj2: Object 2 for the collision check.
//--------------------------------------------------------------------------------------
bool PhysicsScene::PlaneToSphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// return the result of SphereToPlane but with the objects flipped.
	return (SphereToPlane(obj2, obj1));
}

//--------------------------------------------------------------------------------------
// SphereToPlane: Check a collison between a sphere and a plane.
//
// Return:
//		bool: Return true or false for if a collision has happened.
// Param:
//		obj1: Object 1 for the collison check.
//		obj2: Object 2 for the collision check.
//--------------------------------------------------------------------------------------
bool PhysicsScene::SphereToPlane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// Cast each object to either a sphere or plane.
	Sphere* pSphere = dynamic_cast<Sphere*>(obj1);
	Plane* pPlane = dynamic_cast<Plane*>(obj2);

	// if sphere and plane are valid
	if (pSphere != nullptr && pPlane != nullptr)
	{
		// new vector2 for the collision Normal
		glm::vec2 v2CollisionNormal = pPlane->getNormal();

		// dot product of sphere position and plane normal minus plane distance
		float fSphereToPlane = glm::dot(pSphere->GetPosition(), pPlane->getNormal()) - pPlane->getDistance();

		// dot product value is less then 0
		if (SphereToPlane < 0)
		{
			v2CollisionNormal *= -1;
			fSphereToPlane *= -1;
		}

		// new float for collision intersection. 
		float fIntersection = pSphere->GetRadius() - fSphereToPlane;

		// if intersection is over 0
		if (fIntersection > 0)
		{
			// Set the velocity of the sphere to 0 
			pSphere->SetVelocity(glm::vec2(0, 0)); // TEMP
			
			// there was a collision return true
			return true;
		}
	}

	// else return false
	return false;
}

//--------------------------------------------------------------------------------------
// SphereToSphere: Check a collison between a sphere and another sphere.
//
// Return:
//		bool: Return true or false for if a collision has happened.
// Param:
//		obj1: Object 1 for the collison check.
//		obj2: Object 2 for the collision check.
//--------------------------------------------------------------------------------------
bool PhysicsScene::SphereToSphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// Cast each object to either a sphere or plane.
	Sphere* pSphere1 = dynamic_cast<Sphere*>(obj1);
	Sphere* pSphere2 = dynamic_cast<Sphere*>(obj2);

	// if sphere and sphere2 are valid
	if (pSphere1 != nullptr && pSphere2 != nullptr)
	{
		// new vector2 value for the dsitance between each sphere
		glm::vec2 v2Distance = pSphere1->GetPosition() - pSphere2->GetPosition();

		// new float value for the total radius of both spheres
		float fTotalRad = pSphere1->GetRadius() + pSphere2->GetRadius();

		// if the length of the distance is less then or equal to Total radius
		if (glm::length(v2Distance) <= fTotalRad)
		{
			// Set the velocity of the spheres to 0 
			pSphere1->SetVelocity(glm::vec2(0, 0)); // TEMP
			pSphere2->SetVelocity(glm::vec2(0, 0)); // TEMP

			// there was a collision return true
			return true;
		}
	}

	// else return false
	return false;
}












// UP TO HERE!!!







//--------------------------------------------------------------------------------------
// PlaneToBox: Check a collison between a plane and a box.
//
// Return:
//		bool: Return true or false for if a collision has happened.
// Param:
//		obj1: Object 1 for the collison check.
//		obj2: Object 2 for the collision check.
//--------------------------------------------------------------------------------------
bool PhysicsScene::PlaneToBox(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// Cast each object to either a sphere or plane.
	Plane* pPlane = dynamic_cast<Plane*>(obj1);
	Box* pBox = dynamic_cast<Box*>(obj2);

	// if plane and box are valid
	if (pPlane != nullptr || pBox != nullptr)
	{
		//
		glm::vec2 v2Distance = pBox->GetPosition() - pPlane->getCentre();
		glm::vec2 v2HalfWidth = pBox->GetPosition() + glm::vec2(pBox->getWidth() * 0.5f, pBox->getHeight());
		glm::vec2 v2HalfHeight = pBox->GetPosition() + glm::vec2(pBox->getWidth(), pBox->getHeight() * 0.5f);

		// if the length of the distance is less then the length of the half width OR less then the length of the half height.
		if (glm::length(v2Distance) < glm::length(v2HalfWidth) || glm::length(v2Distance) < glm::length(v2HalfHeight))
		{
			// Set the velocity of the box to 0 
			pBox->SetVelocity(glm::vec2(0, 0));

			// there was a collision return true
			return true;
		}
	}

	// else return false
	return false;
}

//--------------------------------------------------------------------------------------
// SphereToBox: Check a collison between a sphere and a box.
//
// Return:
//		bool: Return true or false for if a collision has happened.
// Param:
//		obj1: Object 1 for the collison check.
//		obj2: Object 2 for the collision check.
//--------------------------------------------------------------------------------------
bool PhysicsScene::SphereToBox(PhysicsObject* obj1, PhysicsObject* obj2)
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

//--------------------------------------------------------------------------------------
// BoxToPlane: Check a collison between a box and a plane.
//
// Return:
//		bool: Return true or false for if a collision has happened.
// Param:
//		obj1: Object 1 for the collison check.
//		obj2: Object 2 for the collision check.
//--------------------------------------------------------------------------------------
bool PhysicsScene::BoxToPlane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// return the result of PlaneToBox but with the objects flipped.
	return (PlaneToBox(obj2, obj1));
}

//--------------------------------------------------------------------------------------
// BoxToSphere: Check a collison between a box and a sphere.
//
// Return:
//		bool: Return true or false for if a collision has happened.
// Param:
//		obj1: Object 1 for the collison check.
//		obj2: Object 2 for the collision check.
//--------------------------------------------------------------------------------------
bool PhysicsScene::BoxToSphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// return the result of SphereToBox but with the objects flipped.
	return (SphereToBox(obj2, obj1));
}

//--------------------------------------------------------------------------------------
// BoxToBox: Check a collison between a box and another box.
//
// Return:
//		bool: Return true or false for if a collision has happened.
// Param:
//		obj1: Object 1 for the collison check.
//		obj2: Object 2 for the collision check.
//--------------------------------------------------------------------------------------
bool PhysicsScene::BoxToBox(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Box* box1 = dynamic_cast<Box*>(obj1);
	Box* box2 = dynamic_cast<Box*>(obj2);

	if (box1 != nullptr && box2 != nullptr)
	{
		glm::vec2 min1 = box1->getMin();
		glm::vec2 max1 = box1->getMax();

		glm::vec2 min2 = box2->getMin();
		glm::vec2 max2 = box2->getMax();

		if (min1.x <= max2.x && 
			min1.y <= max2.y && 
			max1.x >= min2.x && 
			max1.y >= min2.y)
		{
			box1->SetVelocity(glm::vec2(0, 0));
			box2->SetVelocity(glm::vec2(0, 0));

			return true;
		}
	}

	return false;
}