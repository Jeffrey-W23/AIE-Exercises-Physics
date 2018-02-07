// #includes, using, etc
#include "aieProject2D1App.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Gizmos.h>
#include <glm\ext.hpp>
#include <glm\vec2.hpp>
#include <glm\vec4.hpp>
#include "Sphere.h"

aieProject2D1App::aieProject2D1App() 
{

}

aieProject2D1App::~aieProject2D1App() 
{

}

bool aieProject2D1App::startup() 
{
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);
	
	// increase the 2d line count to maximize the number of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->SetGravity(glm::vec2(0, 0));
	m_physicsScene->SetTimeStep(0.01f);

	// Newtons first and second law.  // make sure gravity is off
	/*Sphere* ball1 = new Sphere(glm::vec2(-40, 0), glm::vec2(10, 30), 3.0f, 1, glm::vec4(1, 0, 0, 1));
	m_physicsScene->AddActor(ball1);*/

	// Newtons second law. // make sure gravity is off
	/*Sphere* ball2 = new Sphere(glm::vec2(-4, 0), glm::vec2(0, 0), 4.0f, 4, glm::vec4(1, 0, 0, 1));
	Sphere* ball3 = new Sphere(glm::vec2(4, 0), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0, 1, 0, 1));
	m_physicsScene->AddActor(ball2);
	m_physicsScene->AddActor(ball3);
	ball2->ApplyForceToActor(ball3, glm::vec2(2, 0));*/

	// Simulating a Collision. // make sure gravity is off
	/*m_physicsScene->SetGravity(glm::vec2(0, 0));
	Sphere* ball4 = new Sphere(glm::vec2(-20, 0), glm::vec2(0, 0), 4.0f, 4, glm::vec4(1, 0, 0, 1));
	Sphere* ball5 = new Sphere(glm::vec2(10, 0), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0, 1, 0, 1));
	m_physicsScene->AddActor(ball4);
	m_physicsScene->AddActor(ball5);
	ball4->ApplyForce(glm::vec2(30, 0));
	ball5->ApplyForce(glm::vec2(-15, 0));*/

	// return
	return true;
}

void aieProject2D1App::shutdown() 
{
	// delete font
	delete m_font;

	// delete renderer
	delete m_2dRenderer;
}

void aieProject2D1App::update(float deltaTime) 
{
	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();
	m_physicsScene->Update(deltaTime);
	m_physicsScene->UpdateGizmos();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void aieProject2D1App::draw() 
{
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16 / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100,
		-100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}