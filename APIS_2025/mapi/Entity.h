#pragma once
#include "vertex.h"

using namespace std;

class Entity
{
protected:
	glm::vec4 pos, rot, scale;
	glm::mat4 model;
public:
	//Constructor
	Entity();

	// Getters
	glm::vec4 getPosition() const;
	glm::vec4 getRotation() const;
	glm::vec4 getScale() const;
	const glm::mat4& getModel() const;

	// Setters
	void setPosition(glm::vec4 pos);
	void setRotation(glm::vec4 rot);
	void setScale(glm::vec4 scale);
	void computeModelMatrix();

	// Métodos
	virtual void step(float deltaTime) = 0;
};
