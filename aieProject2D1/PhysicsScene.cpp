// #includes, using, etc
#include "PhysicsScene.h"
#include "Rigidbody.h"
#include <algorithm>
#include <iostream> 
#include <list>
#include <iostream>

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

		// update accumulated time by the time step
		fAccumulatedTime -= m_fTimeStep;






		// check for collisions (ideally you'd want to have some sort of
		// scene management in place)
		for (auto pActor : m_apActors) 
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

		dirty.clear();
	
	
	
	
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
