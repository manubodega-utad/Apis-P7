#include "Light.h"

Light::Light(Type type, glm::vec4 color, glm::vec4 direction, glm::vec3 position, bool enable, float linearAttenuation, float cutOffAngle)
	: Entity(), type(type), color(color), direction(direction), enabled(enable), linearAttenuation(linearAttenuation)
{
	setPosition(glm::vec4(position, 1.0f));
	setCutOff(cutOffAngle);
}

Light::Type Light::getType() const {
	return type;
}
void Light::setType(Type t) {
	type = t;
}

const glm::vec4& Light::getColor() const {
	return color;
}
void Light::setColor(const glm::vec4& c) {
	color = c;
}

const glm::vec4& Light::getDirection() const {
	return direction;
}
void Light::setDirection(const glm::vec4& d) {
	direction = d;
}

float Light::getLinearAttenuation() const {
	return linearAttenuation;
}
void Light::setLinearAttenuation(float att) {
	linearAttenuation = att;
}

float Light::getCutOff() const {
	return cutOff;
}

void Light::setCutOff(float angle) { 
	cutOff = glm::cos(glm::radians(angle)); 
}

bool Light::getEnable() const {
	return enabled;
}
void Light::setEnable(bool e) {
	enabled = e;
}
