// #includes, using, etc
#include "aieProject2D1App.h"
#include "Texture.h"
#include "Input.h"
#include "Sphere.h"
#include "Box.h"
#include "Plane.h"
#include <Gizmos.h>
#include <glm\ext.hpp>

//--------------------------------------------------------------------------------------
// Default Constructor.
//--------------------------------------------------------------------------------------
aieProject2D1App::aieProject2D1App() 
{
	//m_v4ClearColor = glm::vec4(1,1,1,1);
}

//--------------------------------------------------------------------------------------
// Default Destructor
//--------------------------------------------------------------------------------------
aieProject2D1App::~aieProject2D1App() 
{
}

//--------------------------------------------------------------------------------------
// startup: Initialize the game.
//
// Returns:
//		bool: Returns a true or false for if the startup is sucessful.
//--------------------------------------------------------------------------------------
bool aieProject2D1App::startup() 
{
	// Create a new instance of the Renderer2D.
	m_2dRenderer = new aie::Renderer2D();
	
	// increase the 2d line count to maximize the number of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	// Set up the physics scene
	m_pPhysicsScene = new PhysicsScene();
	m_pPhysicsScene->SetGravity(glm::vec2(0, -10));
	m_pPhysicsScene->SetTimeStep(0.003f);








	Sphere* ball1 = new Sphere(glm::vec2(-16, 0), glm::vec2(0, 0), 3.0f, 1.0f, glm::vec4(1, 0, 0, 1));
	Sphere* ball2 = new Sphere(glm::vec2(16, 0), glm::vec2(0, 0), 3.0f, 1.0f, glm::vec4(0, 1, 0, 1));
	Sphere* ball3 = new Sphere(glm::vec2(32, 16), glm::vec2(0, 0), 3.0f, 1.0f, glm::vec4(0.75f, 0.75f, 0.75f, 1));
	Sphere* ball4 = new Sphere(glm::vec2(-16, 16), glm::vec2(0, 0), 3.0f, 1.0f, glm::vec4(1, 0.5f, 0, 1));

	Box* box1 = new Box(glm::vec2(-16, 32), glm::vec2(0, 0), 3.0f, 1.0f, 1.0f, glm::vec4(0, 0, 1, 1));
	Box* box2 = new Box(glm::vec2(16, 32), glm::vec2(0, 0), 3.0f, 1.0f, 1.0f, glm::vec4(1, 1, 0, 1));
	Box* box3 = new Box(glm::vec2(-32, 16), glm::vec2(0, 0), 3.0f, 1.0f, 1.0f, glm::vec4(1, 0.5f, 0.76f, 1));
	Box* box4 = new Box(glm::vec2(16, 16), glm::vec2(0, 0), 3.0f, 1.0f, 1.0f, glm::vec4(0.5f, 0, 0.7f, 1));

	Plane* plane1 = new Plane(glm::normalize(glm::vec2(-1, 10)), -30);
	Plane* plane2 = new Plane(glm::normalize(glm::vec2(-10, 10)), -30);
	Plane* plane3 = new Plane(glm::normalize(glm::vec2(10, 0)), -50);

	m_pPhysicsScene->AddActor(ball1);
	m_pPhysicsScene->AddActor(ball2);
	m_pPhysicsScene->AddActor(ball3);
	m_pPhysicsScene->AddActor(ball4);
					 
	m_pPhysicsScene->AddActor(box1);
	m_pPhysicsScene->AddActor(box2);
	m_pPhysicsScene->AddActor(box3);
	m_pPhysicsScene->AddActor(box4);

	m_pPhysicsScene->AddActor(plane1);
	m_pPhysicsScene->AddActor(plane2);
	m_pPhysicsScene->AddActor(plane3);

	ball1->ApplyForce(glm::vec2(50, 0));
	ball2->ApplyForce(glm::vec2(-50, 0));
	ball3->ApplyForce(glm::vec2(0, -25));
	ball4->ApplyForce(glm::vec2(50, 0));

	box1->ApplyForce(glm::vec2(50, 0));
	box2->ApplyForce(glm::vec2(-50, 0));
	box3->ApplyForce(glm::vec2(0, -25));
	box4->ApplyForce(glm::vec2(-50, 0));










	// return
	return true;
}

//--------------------------------------------------------------------------------------
// shutdown: Called on application shutdown and does all the cleaning up (eg. Deleteing pointers.)
//--------------------------------------------------------------------------------------
void aieProject2D1App::shutdown() 
{
	// delete renderer
	delete m_2dRenderer;

	// delete gizmos
	aie::Gizmos::destroy();

	// delete scene
	delete m_pPhysicsScene;
}

//--------------------------------------------------------------------------------------
// Update: A virtual function to update objects.
//
// Param:
//		deltaTime: Pass in deltaTime. A number that updates per second.
//--------------------------------------------------------------------------------------
void aieProject2D1App::update(float deltaTime) 
{







	//ImGui::ColorEdit3("clear colour", glm::value_ptr(m_v4ClearColor));

	// clear the OpenGL backbuffer in preparation for rendering
	//glClearColor(m_v4ClearColor.r, m_v4ClearColor.g, m_v4ClearColor.b, 1);





	
	// clear gizmos
	aie::Gizmos::clear();
	
	// Update scene
	m_pPhysicsScene->Update(deltaTime);
	m_pPhysicsScene->UpdateGizmos();

	// get input instance
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

//--------------------------------------------------------------------------------------
// Draw: A virtual function to render (or "draw") objects to the screen.
//--------------------------------------------------------------------------------------
void aieProject2D1App::draw() 
{
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16 / 9.0f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));

	// done drawing sprites
	m_2dRenderer->end();
}