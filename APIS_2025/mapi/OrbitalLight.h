#pragma once
#include "Light.h"

class OrbitalLight : public Light {
private:
    glm::vec4 center;
    float radius;
    float speed;

public:
    OrbitalLight(const glm::vec4& c = glm::vec4(0, 0, 0, 1), float r = 10.0f, float s = 1.0f)
        : center(c), radius(r), speed(s) {}

    void setCenter(const glm::vec4& newCenter);
    glm::vec4 getCenter() const;

    void setRadius(float newRadius);
    float getRadius() const;

    void setSpeed(float newSpeed);
    float getSpeed() const;

    virtual void step(float timeStep) override;
};