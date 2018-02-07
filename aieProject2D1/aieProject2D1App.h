// #includes, using, etc
#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"

class aieProject2D1App : public aie::Application {
public:

	// Constructor / Destructor
	aieProject2D1App();
	virtual ~aieProject2D1App();

	// starup / shutdown
	virtual bool startup();
	virtual void shutdown();

	// Update
	virtual void update(float deltaTime);
	
	// Draw
	virtual void draw();

protected:

	// Renderer2D pointer
	aie::Renderer2D*	m_2dRenderer;

	// Font poniter
	aie::Font*			m_font;

	// Physics Scene pointer
	PhysicsScene* m_physicsScene;


	glm::vec4 m_v4ClearColor;
};