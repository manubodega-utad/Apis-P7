#include "OrbitalLight.h"

OrbitalLight::OrbitalLight(const glm::vec4& c, float r, float s)
	: Light(Type::POINT, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f), glm::vec3(c.x + r, c.y, c.z), true, 0.2f),
	center(c), radius(r), speed(s), currentAngle(0.0f)
{
}

glm::vec4 OrbitalLight::getCenter() const
{
	return center;
}

float OrbitalLight::getRadius() const
{
	return radius;
}

float OrbitalLight::getSpeed() const
{
	return speed;
}

void OrbitalLight::setCenter(const glm::vec4& newCenter)
{
	center = newCenter;
}

void OrbitalLight::setRadius(float newRadius)
{
	radius = newRadius;
}

void OrbitalLight::setSpeed(float newSpeed)
{
	speed = newSpeed;
}

void OrbitalLight::step(float timeStep)
{
	currentAngle += static_cast<float>(timeStep * speed);

	// 2. Calculamos la nueva posición X y Z orbitando sobre el centro
	glm::vec4 currentPos = getPosition();
	currentPos.x = center.x + radius * std::cos(currentAngle);
	currentPos.z = center.z + radius * std::sin(currentAngle);

	// 3. Aplicamos la posición a la Entidad
	setPosition(currentPos);
	computeModelMatrix();
}
