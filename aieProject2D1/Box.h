#pragma once
#include "Rigidbody.h"

class Box : public Rigidbody
{
public:
	Box() = delete;
	Box(glm::vec2 position, glm::vec2 velocity, float mass, float width, float height, glm::vec4 colour);
	~Box();

	virtual void MakeGizmo();
	float getWidth() { return m_width; }
	float getHeight() { return m_height; }
	glm::vec2 getDimensions() { return m_dimensions; }
	glm::vec2 getMin() { return glm::vec2(m_v2Position.x - (m_width ), m_v2Position.y - (m_height )); }
	glm::vec2 getMax() { return glm::vec2(m_v2Position.x + (m_width), m_v2Position.y + (m_height )); }
	glm::vec4 getColour() { return m_colour; }

protected:
	float m_width;
	float m_height;
	glm::vec2 m_dimensions;
	glm::vec2 m_min;
	glm::vec2 m_max;
	glm::vec4 m_colour;
};