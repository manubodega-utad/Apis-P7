#include "OrbitalLight.h"

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
	float angle = static_cast<float>(timeStep * speed);
	float theta = std::atan2(pos.z - center.z, pos.x - center.x);

	theta += angle;

	pos.x = center.x + radius * cos(theta);
	pos.z = center.z + radius * sin(theta);

	computeModelMatrix();
}
