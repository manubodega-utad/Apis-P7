#include "Light.h"

Light::Light()
	: color(1.0f),
	direction(0.0f, 1.0f, -1.0f, 0.0f),
	type(Type::DIRECTIONAL),
	linearAttenuation(0.0f),
	enabled(true)
{}

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

bool Light::getEnable() const {
	return enabled;
}
void Light::setEnable(bool e) {
	enabled = e;
}
