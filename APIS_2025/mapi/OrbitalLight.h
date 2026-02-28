#pragma once
#include "Light.h"

class OrbitalLight : public Light {
private:
    glm::vec4 center;
    float radius;
    float speed;
    float currentAngle;

public:
    OrbitalLight(const glm::vec4& c = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), float r = 10.0f, float s = 1.0f);

    void setCenter(const glm::vec4& newCenter);
    glm::vec4 getCenter() const;

    void setRadius(float newRadius);
    float getRadius() const;

    void setSpeed(float newSpeed);
    float getSpeed() const;

    virtual void step(float timeStep) override;
};